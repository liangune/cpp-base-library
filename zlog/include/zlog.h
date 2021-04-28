/*
* zlog 跨平台头文件
*
*/

#ifndef _ZLOG_COSS_PLATFORM_H
#define _ZLOG_COSS_PLATFORM_H

#ifdef _MSC_VER
#include "windows/zlog.h"
#elif defined __GNUC__
#include "linux/zlog.h"
#endif

// trace级别用来打印access log
// format: "{\"date\":\"%s\", \"host\":\"%s\", \"method\":\"%s\", \"uri\":\"%s\", \"code\":%d, \"handleTime\":%d, \"path\":\"%s\"}
enum {
    ZLOG_LEVEL_TRACE = 140,
};

#if (defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L) || (defined _MSC_VER)
/* zlog macros */
#define dzlog_trace(...) \
    dzlog(__FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__, \
	ZLOG_LEVEL_TRACE, __VA_ARGS__)
#elif defined __GNUC__
/* dzlog macros */
#define dzlog_trace(format, args...) \
	dzlog(__FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__, \
	ZLOG_LEVEL_TRACE, format, ##args)
#endif


#endif // _ZLOG_COSS_PLATFORM_H
