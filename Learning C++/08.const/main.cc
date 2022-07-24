#include <iostream>

// 默认情况下，const对象只在本文件有效，如同static
// 如果需要其他文件共享，需要extern
const double PI = 3.14;
extern const double Pi = 3.1415906535;

#if 0
const& 重载将仅用于const，non-const和lvalue对象
& 此重载将仅用于非const对象
&& 此重载将仅用于右值对象
#endif

// 形参为常量时，实参可以是变量、常量或者常数
int func1(int n)
{
    return n;
}

// 形参为普通引用时，实参必须为变量
int func2(int& n)
{
    return n;
}

// 形参为常量引用时，实参可以是变量、常量或者常数
int func3(const int& n)
{
    return n;
}

#if 0
形参的本质，是一个左值
当进行函数调用时，会用实参去初始化，生成一个形参类型的左值（可就是说问什么说函数调用是值传递，会生成一个副本）
因此在接收常量时，const&的好处就在于，常引用可以被任意表达式初始化，可以是变量，可以是常量，可以是常数
如果仅仅是&的话，就不能接收常数了
#endif

auto main(int argc, char* argv[]) -> int
{
    int a = 1;
    // 常引用，可以被任何表达式初始化
    const int& var1 = 1;
    const int& var2 = a;
    const int& var3 = a * 2;
    // var1 = 1; 初始化完成后，常引用不可被重新绑定
    // int& var3 = var1; // &引用只能绑定非const对象
    int&& var4 = 2; // 右值引用，但var4是左值
    var4++;
    // int&& var5 = var4; // var4是左值，所以普通情况下，无法将右值引用绑定到右值引用的变量上
    int&& var6 = std::move(var4); // 但是std::move()可以做到
    var6++;

    std::cout << "var4: " << var4 << std::endl;
    std::cout << "var6: " << var6 << std::endl;
    std::cout << "var4: " << var4 << std::endl;
    std::cout << func1(3) << std::endl;
    // std::cout << func2(3) << std::endl; // 非常量引用的初始值必须为左值
    std::cout << func3(3) << std::endl;

    std::cout << func1(a) << std::endl;
    std::cout << func2(a) << std::endl;
    std::cout << func3(a) << std::endl;

    return 0;
}