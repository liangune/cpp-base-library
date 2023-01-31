package main

import (
	"archive/tar"
	"archive/zip"
	"compress/gzip"
	"fmt"
	"io"
	"io/ioutil"
	"os"
	"path/filepath"
	"strings"
	"time"
)

const numSeverity = 7

var empty = struct{}{}

const (
	// linux
	CompressMethodGzip = 1
	// windows
	CompressMethodZip = 2
)

const (
	compressSuffixGzip                  = ".tar.gz"
	compressSuffixZip                   = ".zip"
	logfileSuffix                       = ".log"
	defaultCompressMethod               = CompressMethodZip
	defaultCompressFileMode os.FileMode = 0440
)

const FileNameSplitLessLength = 3

// LogCleaner define the log cleaner options:
//
//     path     - Log files will be clean to this directory
//     interval - Log files clean scanning interval
//     reserve  - Log files reserve time
//	   compress - Compress determines if the rotated log files should be compressed using gzip. The default is not to perform compression.
//	   compressMethod -压缩方法
type LogCleaner struct {
	path             string        // 路径
	interval         time.Duration // 间隔
	reserve          uint32        // 保留天数
	compress         bool          // 是否压缩
	compressMethod   int8          // 压缩方式
	symlinks         map[string]struct{}
	compressFileMode os.FileMode // 归档文件权限
}

// InitOption define the glog cleaner init options for GlogCleaner:
//
//     Path     - Log files will be clean to this directory
//     Interval - Log files clean scanning interval
//     Reserve  - Log files reserve time
//     Compress - Log files check whether compress
//     CompressMethod - Log files compress method
type InitOption struct {
	Path             string
	Interval         time.Duration
	Reserve          uint32
	Compress         bool
	CompressMethod   int8
	CompressFileMode os.FileMode
}

// NewGlogCleaner create a cleaner in a goroutine and do instantiation GlogCleaner by given
// init options.
func NewLogCleaner(option InitOption) *LogCleaner {
	c := new(LogCleaner)
	c.path = option.Path
	c.interval = option.Interval
	c.reserve = option.Reserve
	c.compress = option.Compress
	c.compressMethod = option.CompressMethod
	c.compressFileMode = option.CompressFileMode
	if c.compressMethod <= 0 {
		c.compressMethod = defaultCompressMethod
	}
	c.symlinks = make(map[string]struct{}, numSeverity)

	go c.cleaner()
	return c
}

// clean provides function to check path exists by given log files path.
func (c *LogCleaner) clean() {
	exists, err := c.exists(c.path)
	if err != nil {
		fmt.Printf("%v \n", err)
		return
	}
	if !exists {
		return
	}

	files, err := ioutil.ReadDir(c.path)
	if err != nil {
		fmt.Printf("%v \n", err)
		return
	}
	c.check(files)
}

// exists returns whether the given file or directory exists or not
func (c *LogCleaner) exists(path string) (bool, error) {
	_, err := os.Stat(path)
	if err == nil {
		return true, nil
	}
	if os.IsNotExist(err) {
		return false, nil
	}
	return true, err
}

// check provides function to check log files name whether the deletion and compression
// condition is satisfied.
func (c *LogCleaner) check(files []os.FileInfo) {
	excludes := make(map[string]struct{}, numSeverity)
	for _, f := range files {
		// skip the destination of symlink files
		if _, ok := c.symlinks[f.Name()]; ok && f.Mode()&os.ModeSymlink != 0 {
			if dst, err := os.Readlink(c.path + f.Name()); err == nil {
				excludes[dst] = empty
			}
		}
	}
	var remove []os.FileInfo
	mapCompress := map[string][]os.FileInfo{}
	for _, f := range files {
		if _, ok := excludes[f.Name()]; ok {
			continue
		}
		str := strings.Split(f.Name(), `.`)
		suffixGzip := strings.HasSuffix(f.Name(), compressSuffixGzip)
		suffixZip := strings.HasSuffix(f.Name(), compressSuffixZip)
		if len(str) < FileNameSplitLessLength {
			continue
		}
		var fileTime string
		if suffixGzip || suffixZip {
			fileTime = str[0]
		} else {
			fileTime = f.ModTime().Format("2006-01-02")
		}
		if c.isRemove(fileTime) {
			remove = append(remove, f)
			continue
		}

		suffix := strings.HasSuffix(f.Name(), logfileSuffix)
		if suffix {
			if c.isCompress(f, fileTime) {
				if fslice, ok := mapCompress[fileTime]; ok {
					fslice = append(fslice, f)
					mapCompress[fileTime] = fslice
				} else {
					fslice = make([]os.FileInfo, 0)
					fslice = append(fslice, f)
					mapCompress[fileTime] = fslice
				}
			}
		}
	}

	for _, f := range remove {
		err := c.remove(f)
		if err != nil {
			fmt.Printf("failed to drop log file, %v \n", err)
		}
	}
	for k, v := range mapCompress {
		if c.compressMethod == CompressMethodGzip {
			dest := filepath.Join(c.path, k+logfileSuffix+compressSuffixGzip)
			err := c.compressFilesGzip(v, dest)
			if err != nil {
				fmt.Printf("failed to compress log file, %v \n", err)
			}
		} else if c.compressMethod == CompressMethodZip {
			dest := filepath.Join(c.path, k+logfileSuffix+compressSuffixZip)
			err := c.compressFilesZip(v, dest)
			if err != nil {
				fmt.Printf("failed to compress log file, %v \n", err)
			}
		}
	}
}

// isRemove check the log file creation time if the conditions are met.
func (c *LogCleaner) isRemove(timestr string) bool {
	if c.reserve <= 0 {
		return false
	}
	diff := time.Duration(int64(24*time.Hour) * int64(c.reserve))
	cutoff := time.Now().Add(-1 * diff)
	fileTime, err := time.Parse("2006-01-02 15:04:05", fmt.Sprintf("%s 00:00:00", timestr))
	if err != nil {
		return false
	}
	return fileTime.Before(cutoff)
}

// remove delete the file
func (c *LogCleaner) remove(f os.FileInfo) error {
	err := os.Remove(filepath.Join(c.path, f.Name()))
	if err != nil {
		return err
	}
	return nil
}

// cleaner provides regular cleaning function by given log files clean
// scanning interval.
func (c *LogCleaner) cleaner() {
	for {
		c.clean()
		time.Sleep(c.interval)
	}
}

func (c *LogCleaner) isCompress(f os.FileInfo, timestr string) bool {
	curTimeStr := time.Now().Format("2006-01-02")
	var compressSuffix string
	if c.compressMethod == CompressMethodZip {
		compressSuffix = compressSuffixZip
	} else {
		compressSuffix = compressSuffixGzip
	}

	if c.compress {
		if !strings.HasSuffix(f.Name(), compressSuffix) && curTimeStr != timestr {
			return true
		}
	}
	return false
}

func (c *LogCleaner) compressFileGzip(file *os.File, prefix string, tw *tar.Writer) error {
	info, err := file.Stat()
	if err != nil {
		return err
	}

	header, err := tar.FileInfoHeader(info, "")
	header.Name = prefix + "/" + header.Name
	if err != nil {
		return err
	}
	err = tw.WriteHeader(header)
	if err != nil {
		return err
	}

	_, err = io.Copy(tw, file)
	file.Close()
	if err != nil {
		return err
	}
	return nil
}

func (c *LogCleaner) compressFileZip(file *os.File, prefix string, zw *zip.Writer) error {
	info, err := file.Stat()
	if err != nil {
		return err
	}

	header, err := zip.FileInfoHeader(info)
	header.Name = prefix + "/" + header.Name
	header.Method = zip.Deflate
	if err != nil {
		return err
	}
	writer, err := zw.CreateHeader(header)
	if err != nil {
		return err
	}
	_, err = io.Copy(writer, file)
	file.Close()
	if err != nil {
		return err
	}
	return nil
}

/*
	@brief 压缩文件
	@files 文件数组
	@src  源文件文件夹
	@dest 压缩文件存放地址
*/
func (c *LogCleaner) compressFilesGzip(files []os.FileInfo, dest string) error {
	gzfile, err := c.Create(dest)
	if err != nil {
		return fmt.Errorf("failed to open compressed log file: %v", err)
	}
	defer gzfile.Close()

	gw := gzip.NewWriter(gzfile)
	defer gw.Close()

	tw := tar.NewWriter(gw)
	defer tw.Close()

	for _, fileinfo := range files {
		fn := filepath.Join(c.path, fileinfo.Name())
		file, err := os.Open(fn)
		if err != nil {
			return err
		}
		err = c.compressFileGzip(file, "", tw)
		if err != nil {
			return err
		}

		if err := os.Remove(fn); err != nil {
			return err
		}
	}
	return nil
}

func (c *LogCleaner) compressFilesZip(files []os.FileInfo, dest string) error {
	zipfile, err := c.Create(dest)
	if err != nil {
		return fmt.Errorf("failed to open compressed log file: %v", err)
	}
	defer zipfile.Close()

	w := zip.NewWriter(zipfile)
	defer w.Close()

	for _, fileinfo := range files {
		fn := filepath.Join(c.path, fileinfo.Name())
		file, err := os.Open(fn)
		if err != nil {
			return err
		}
		err = c.compressFileZip(file, "", w)
		if err != nil {
			return err
		}

		if err := os.Remove(fn); err != nil {
			return err
		}
	}
	return nil
}

func (c *LogCleaner) Create(name string) (*os.File, error) {
	if c.compressFileMode <= 0 {
		return os.OpenFile(name, os.O_RDWR|os.O_CREATE|os.O_TRUNC, defaultCompressFileMode)
	}
	return os.OpenFile(name, os.O_RDWR|os.O_CREATE|os.O_TRUNC, c.compressFileMode)
}
