#include "libobject/IObject.h"
#include <cassert>
#include <dlfcn.h>

static const char path[] = "./libobject/libobject.so";
typedef IObject* (*GetInstance)();

auto main(int argc, char* argv[]) -> int
{
    void* handle = dlopen(path, RTLD_LAZY);
    assert(handle);
    GetInstance getInstance = (GetInstance)dlsym(handle, "getInstance");
    assert(getInstance);
    IObject* p_io1 = getInstance();
    p_io1->show();
    delete p_io1;
    p_io1 = nullptr;

    return 0;
}