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
int ftrace_duration_begin(const char* message);
int ftrace_duration_end(void);
int ftrace_duration_complete(const char* message, uint64_t duration_ns);

// Instant Events (i)
int ftrace_instant(const char* message);

// Counter Events (C)
int ftrace_counter_set(const char* message, size_t count);
int ftrace_counter_zero(const char* message);

// Async Events (b/n/e)
int ftrace_async_begin(const char* id, const char* message);
int ftrace_async_instant(const char* id, const char* message);
int ftrace_async_end(const char* id);

// Flow Events (s/t/f)
int ftrace_flow_start(const char* flow_id, const char* message);
int ftrace_flow_step(const char* flow_id, const char* message);
int ftrace_flow_end(const char* flow_id);

// Object Events (N/O/D)
int ftrace_obj_create(const char* obj, const char* message);
int ftrace_obj_snapshot(const char* obj, const char* message);
int ftrace_obj_destroy(const char* obj);

// Metadata (M) and Memory Dump (V/v)
int ftrace_metadata(const char* key, const char* value);
int ftrace_memory_dump(bool is_global, const char* data);

#ifdef __cplusplus
}
#endif