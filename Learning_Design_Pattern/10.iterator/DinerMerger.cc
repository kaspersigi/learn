#include "DinerMerger.h"

auto main(int argc, char* argv[]) -> int
{
    auto waitress = std::make_shared<Waitress>(new PancakeHouseMenu(), new DinerMenu());

    waitress->printMenu();
    return 0;
}