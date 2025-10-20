#pragma once

#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// 初始化/销毁
bool ftrace_init(void);
void ftrace_close(void);

// Duration Events (B/E/X)
size_t ftrace_duration_begin(const char* message);
size_t ftrace_duration_end(void);
size_t ftrace_duration_complete(const char* message, uint64_t duration_us);

// Instant Events (I)
size_t ftrace_instant(const char* message);

// Counter Events (C)
size_t ftrace_counter_set(const char* message, size_t count);
size_t ftrace_counter_zero(const char* message);

// Async Events (b/n/e)
size_t ftrace_async_start(const char* message, const char* id);
size_t ftrace_async_step(const char* message, const char* id);
size_t ftrace_async_end(const char* message, const char* id);

// Flow Events (s/t/f)
size_t ftrace_flow_start(const char* message, const char* id);
size_t ftrace_flow_step(const char* message, const char* id);
size_t ftrace_flow_end(const char* message, const char* id);

// Object Events (N/O/D)
size_t ftrace_obj_create(const char* obj, const char* message);
size_t ftrace_obj_snapshot(const char* obj, const char* message);
size_t ftrace_obj_destroy(const char* obj);

// Metadata (M) and Memory Dump (V/v)
size_t ftrace_metadata(const char* key, const char* value);
size_t ftrace_memory_dump(bool is_global, const char* data);

#ifdef __cplusplus
}
#endif