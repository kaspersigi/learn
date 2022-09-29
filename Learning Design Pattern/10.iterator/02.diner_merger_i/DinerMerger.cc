#include "DinerMerger.h"
#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    auto waitress = std::make_shared<Waitress>(new PancakeHouseMenu(), new DinerMenu());

    waitress->printMenu();
    std::cout << "------------------------------" << std::endl;

    waitress->printVegetarianMenu();
    std::cout << "------------------------------" << std::endl;

    std::cout << "\nCustomer asks, is the Hotdog vegetarian?" << std::endl;
    std::cout << "Waitress says: ";
    if (waitress->isItemVegetarian("Hotdog")) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }
    std::cout << "\nCustomer asks, are the Waffles vegetarian?" << std::endl;
    std::cout << "Waitress says: ";
    if (waitress->isItemVegetarian("Waffles")) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }
    return 0;
}