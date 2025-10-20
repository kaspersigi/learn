#include "DinerMerger.h"

auto main(int argc, char* argv[]) -> int
{
    auto waitress = std::make_shared<Waitress>(std::make_shared<PancakeHouseMenu>(), std::make_shared<DinerMenu>());

    waitress->printMenu();
    waitress->printVegetarianMenu();
    return 0;
}