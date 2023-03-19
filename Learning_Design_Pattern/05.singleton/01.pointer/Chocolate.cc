#include "Chocolate.h"
#include <iostream>
// #include <memory>

auto main(int argc, char* argv[]) -> int
{
#if 0
    std::shared_ptr<ChocolateBoiler> boiler1(ChocolateBoiler::getInstance());
    boiler1->fill();
    boiler1->boil();
    boiler1->drain();

    单例模式的陷阱，使用智能指针，会导致二次释放，因此这种写法是有缺陷的，最好是返回的实例就是智能指针，防止二次释放
    std::shared_ptr<ChocolateBoiler> boiler2(ChocolateBoiler::getInstance());
#endif

    ChocolateBoiler* boiler1 = ChocolateBoiler::getInstance();
    boiler1->fill();
    boiler1->boil();
    boiler1->drain();

    ChocolateBoiler* boiler2 = ChocolateBoiler::getInstance();

    if (boiler1 == boiler2)
        std::cout << "Got same boiler" << std::endl;
    else
        std::cout << "Oh oh! got a different boiler" << std::endl;

    return 0;
}
