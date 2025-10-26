/* include/trace/events/mychar.h */
#undef TRACE_SYSTEM
#define TRACE_SYSTEM mytrace

// echo 1 > /sys/kernel/debug/tracing/events/mytrace/enable
// echo > /sys/kernel/debug/tracing/trace
// cat /sys/kernel/debug/tracing/trace

#include <linux/tracepoint.h>
#include <linux/version.h>

TRACE_EVENT(duration,
    TP_PROTO(
        char track_event_type,
        const char* slice_name),
    TP_ARGS(track_event_type, slice_name),
    TP_STRUCT__entry(
        __field(char, track_event_type)
            __string(slice_name, slice_name)),
    TP_fast_assign(
        __entry->track_event_type = track_event_type;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 10, 0)
        __assign_str(slice_name);
#else
        __assign_str(slice_name, slice_name);
#endif
        ),
    TP_printk(
        "type=%c slice_name=%s",
        __entry->track_event_type,
        __get_str(slice_name)));

TRACE_EVENT(counter,
    TP_PROTO(
        u64 counter_value,
        const char* counter_name),
    TP_ARGS(counter_value, counter_name),
    TP_STRUCT__entry(
        __field(u64, counter_value)
            __string(track_name, counter_name)
        // 可选：添加 scope 字段（如按进程、CPU 分组）
        // __field(pid_t, scope_tgid)
        ),
    TP_fast_assign(
        __entry->counter_value = counter_value;
        __assign_str(track_name, counter_name);
        // __entry->scope_tgid = current->tgid;
        ),
    TP_printk(
        "counter: %s = %llu",
        __get_str(track_name),
        (unsigned long long)__entry->counter_value));

#include <trace/define_trace.h>