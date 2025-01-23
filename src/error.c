#include <stdio.h>
#include <stdlib.h>

#include "error.h"

void _cassert(const int cond, const char *msg, const int line, const char *file, const char *func) {
    if (!cond) {
        fprintf(stderr, "[ASSERT][@%s - %s:%zu]: %s\n", file, func, line, msg);
        exit(-1);
    }
}

void _warn(const char *msg, const int line, const char *file, const char *func) {
    fprintf(stderr, "[WARN][@%s - %s:%zu]: %s\n", file, func, line, msg);
}

void _err(const char *msg, const int line, const char *file, const char *func, const int code) {
    fprintf(stderr, "[ERROR][@%s - %s:%zu]: %s\n", file, func, line, msg);
    exit(code);
}