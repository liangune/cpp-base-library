#### 日子清理归档工具

- go语言编写，导出dll给c++使用
- zlog_cleaner.def文件需要人工创建并编辑内容
- 编译：运行build.bat脚本
- 生成的头文件中需要注释部分代码，c++编译才不会出错

```
// typedef __SIZE_TYPE__ GoUintptr;
typedef float GoFloat32;
typedef double GoFloat64;
// typedef float _Complex GoComplex64;
// typedef double _Complex GoComplex128;
```
