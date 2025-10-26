/* include/trace/events/mychar.h */
#undef TRACE_SYSTEM
#define TRACE_SYSTEM mychar

// echo 1 > /sys/kernel/debug/tracing/events/mychar/enable
// echo > /sys/kernel/debug/tracing/trace
// cat /sys/kernel/debug/tracing/trace

#include <linux/tracepoint.h>

TRACE_EVENT(char_slice,
    TP_PROTO(char type, const char* name),
    TP_ARGS(type, name),
    TP_STRUCT__entry(
        __field(char, type)          // ← 关键：字段名必须是 "type"
        __string(name, name)         // ← 字段名必须是 "name"
    ),
    TP_fast_assign(
        __entry->type = type;
        __assign_str(name, name);
    ),
    TP_printk("type=%c name=%s", __entry->type, __get_str(name))
);

#include <trace/define_trace.h>