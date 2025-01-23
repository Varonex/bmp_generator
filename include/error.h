#pragma once

#define ERRC(msg,code) _err(msg, __LINE__, __FILE__, __FUNCTION__, code)
#define ERR(msg) _err(msg, __LINE__, __FILE__, __FUNCTION__, 1)

#define WARN(msg) _warn(msg, __LINE__, __FILE__, __FUNCTION__)

#define ASSERTM(cond, msg) _cassert(cond, msg, __LINE__, __FILE__, __FUNCTION__)
#define ASSERT(cond) _cassert(cond, "", __LINE__, __FILE__, __FUNCTION__)

void _cassert(const int cond, const char *msg, const int line, const char *file, const char *func);
void _warn(const char *msg, const int line, const char *file, const char *func);
void _err(const char *msg, const int line, const char *file, const char *func, const int code);