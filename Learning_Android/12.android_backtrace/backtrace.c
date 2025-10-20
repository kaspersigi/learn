#include "backtrace.h"
#include <dlfcn.h>

_Unwind_Reason_Code _unwind_callback(struct _Unwind_Context* context, void* data)
{
    struct backtrace_stack* state = (struct backtrace_stack*)(data);
    uintptr_t pc = _Unwind_GetIP(context);
    if (pc) {
        if (state->current == state->end) {
            return _URC_END_OF_STACK;
        } else {
            *state->current++ = (void*)(pc);
        }
    }
    return _URC_NO_REASON;
}

size_t _fill_backtraces_buffer(void** buffer, size_t max)
{
    struct backtrace_stack stack = { buffer, buffer + max };
    _Unwind_Backtrace(_unwind_callback, &stack);
    return stack.current - buffer;
}

void backtrace()
{
    void* buffer[30];
    void* addr;
    size_t count = _fill_backtraces_buffer(buffer, 30);
    for (int index = 0; index < count; ++index) {
        addr = buffer[index];
        Dl_info info;
        if (dladdr(addr, &info)) {
            LOGE("# %d: pc:%p offset:[0x%-8lx] %s(%s)",
                index,
                addr,
                (char*)addr - (char*)info.dli_fbase,
                info.dli_fname,
                info.dli_sname);
        }
    }
}