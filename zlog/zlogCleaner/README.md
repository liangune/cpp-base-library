#### 日子清理归档工具

- go语言实现，导出动态库或者静态库给c++使用

#### windows
- zlog_cleaner.def文件需要人工创建并编辑内容
- 编译：运行build.bat脚本
- 生成的头文件中需要注释部分代码，c++部分工程编译才不会出错

```
#ifdef _MSC_VER
// #include <complex.h>
// typedef _Fcomplex GoComplex64;
// typedef _Dcomplex GoComplex128;
#else
typedef float _Complex GoComplex64;
typedef double _Complex GoComplex128;
#endif
```
