package main

/*
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
*/
import "C"

import (
	"time"
)

//export GoLogCleaner
func GoLogCleaner(path *C.char, interval uint32, reserve uint32, isCompress int32, compressMethod int8) {
	compress := false
	if isCompress == 1 {
		compress = true
	}
	NewLogCleaner(InitOption{
		Path:           C.GoString(path),
		Interval:       time.Minute * time.Duration(interval),
		Reserve:        reserve,
		Compress:       compress,
		CompressMethod: compressMethod,
	})
}

func main() {}
