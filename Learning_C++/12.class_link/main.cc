#include "libobject/IObject.h"

auto main(int argc, char* argv[]) -> int
{
    auto object = IObject::createInstance();
    object->show();

    return 0;
}