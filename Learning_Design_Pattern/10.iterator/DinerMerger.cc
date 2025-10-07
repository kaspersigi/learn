#include "DinerMerger.h"
#include "menus/menus.h"
#include "waitress/Waitress.h"

int main(int argc, char* argv[])
{
    auto waitress = std::make_shared<Waitress>(std::make_shared<PancakeHouseMenu>(), std::make_shared<DinerMenu>());

    waitress->printMenu();
    waitress->printVegetarianMenu();
    return 0;
}