#include <assert.h>
#include <dlfcn.h>

static const char path[] = "./libobject/libobject.so";
typedef int* (*InitIObject)();
typedef void* (*Show)();
typedef void* (*DestroyIObject)();

int main(int argc, char* argv[])
{
    void* handle = dlopen(path, RTLD_LAZY);
    assert(handle);
    InitIObject initIObject = (InitIObject)dlsym(handle, "initIObject");
    Show show = (Show)dlsym(handle, "show");
    DestroyIObject destroyIObject = (DestroyIObject)dlsym(handle, "destroyIObject");
    assert(0 == initIObject());
    show();
    destroyIObject();
    dlclose(handle);

    return 0;
}