/* include/trace/events/mychar.h */
#undef TRACE_SYSTEM
#define TRACE_SYSTEM mychar

#include <linux/tracepoint.h>

TRACE_EVENT(char_slice,
    TP_PROTO(char type, const char* name),
    TP_ARGS(type, name),
    TP_STRUCT__entry(
        __field(char, track_event_type)
            __string(slice_name, name)),
    TP_fast_assign(
        __entry->track_event_type = type;
        __assign_str(slice_name, name);),
    TP_printk("type=%c name=%s", __entry->track_event_type, __get_str(slice_name)));

#include <trace/define_trace.h>