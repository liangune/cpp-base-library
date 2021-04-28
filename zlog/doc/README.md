#### 配置说明

- zlog_linux.conf : linux平台的日记配置文件参考
- zlog_windows.conf : windows平台的日记配置文件参考



#### 使用

```
#include "zlog/zlog.h"

int main(int argc, const char* argv[]) {
	// windows平台
	//int ret = dzlog_init("E:/cpp/basic-library/test/jsoncpp/zlog.conf", "log_server");
	int ret = dzlog_init("..\\zlog.conf", "log_server");

    // linux平台
    int ret = dzlog_init("./zlog.conf", "log_server");
    
	dzlog_info("hello, zlog info");      
	dzlog_error("hello, zlog error");  
	dzlog_warn("hello, zlog warning");
	dzlog_debug("hello, zlog debug");  
	
	zlog_fini();
	return 0;
}
```

