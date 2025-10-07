#include "libobject/IObject.h"
#include <dlfcn.h>
#include <iostream>

static const char path[] = "./libobject/libobject.so";
typedef IObject* (*GetInstanceFunc)();
typedef void (*ReleaseInstanceFunc)(IObject*);

auto main(int argc, char* argv[]) -> int
{
    void* handle = dlopen(path, RTLD_LAZY);
    if (!handle) {
        std::cerr << "Cannot open library: " << dlerror() << std::endl;
        return -1;
    }

    GetInstanceFunc getInstance = (GetInstanceFunc)dlsym(handle, "GetInstance");
    if (!getInstance) {
        std::cerr << "Cannot load symbol 'GetInstance': " << dlerror() << std::endl;
        dlclose(handle);
        return -1;
    }

    ReleaseInstanceFunc releaseInstance = (ReleaseInstanceFunc)dlsym(handle, "ReleaseInstance");
    if (!releaseInstance) {
        std::cerr << "Cannot load symbol 'ReleaseInstance': " << dlerror() << std::endl;
        dlclose(handle);
        return -1;
    }

    IObject* instance = getInstance();
    if (instance) {
        instance->show();
        releaseInstance(instance);
    }

    if (handle) {
        dlclose(handle);
    }

    return 0;
}