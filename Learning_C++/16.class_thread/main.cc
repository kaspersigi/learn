#include "MyWorker.h"
#include <memory>

auto main(int argc, char* argv[]) -> int
{
    auto mw = std::make_shared<MyWorker>();
    mw->main_worker();
    return 0;
}