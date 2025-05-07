int func(int i)
{
    int sum = 0;
    for (int i = 0; i < 1000000; ++i) {
        sum += i;
    }
    return sum;
}

// 通过 attribute 标记的初始化函数
__attribute__((constructor)) static void init_library()
{
    int sum = 0;
    for (int i = 0; i < 1000000; ++i) {
        sum += i;
    }
}

// 通过 attribute 标记的反初始化函数
__attribute__((destructor)) static void deinit_library()
{
    int sum = 0;
    for (int i = 0; i < 1000000; ++i) {
        sum += i;
    }
}