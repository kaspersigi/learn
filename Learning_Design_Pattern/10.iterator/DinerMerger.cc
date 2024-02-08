#include "DinerMerger.h"
#include <memory>

auto main(int argc, char* argv[]) -> int
{
    auto waitress = std::make_shared<Waitress>(new PancakeHouseMenu(), new DinerMenu());

    waitress->printMenu();
    return 0;
}