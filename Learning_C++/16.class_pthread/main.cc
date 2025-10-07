#include "MyWorker.h"

auto main(int argc, char* argv[]) -> int
{
    auto mw = std::make_shared<MainWorker>();
    mw->execute();
    return 0;
}