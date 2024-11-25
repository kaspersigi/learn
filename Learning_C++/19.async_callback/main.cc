#include "MyWorker.h"
#include <memory>

auto main(int argc, char* argv[]) -> int
{
    auto mw = std::make_shared<MyWorker>();
    mw->execute(9, std::string("Hello world!"));
    return 0;
}