// ============================
// file: learn_std_vector.cc
// 说明：全面学习 std::vector 的现代 C++ 用法
// 编译：g++ -std=c++17 learn_std_vector.cc -o learn_vector
// ============================

#include <algorithm> // sort, find, remove_if, unique, transform, copy
#include <numeric> // accumulate, iota
#include <print> // C++23 (可选)
#include <vector>

// 辅助函数：打印容器
template <typename Container>
void print_container(const Container& c, const char* label = "")
{
    if (*label)
        std::println("{}: ", label);
    for (const auto& elem : c) {
        std::print("{} ", elem);
    }
    std::println("");
}

// 演示用自定义类型（带构造/析构日志）
struct Widget {
    int id;
    Widget(int i)
        : id(i)
    {
        std::println("Widget({}) constructed", i);
    }
    Widget(const Widget& w)
        : id(w.id)
    {
        std::println("Widget({}) copy-constructed", id);
    }
    Widget(Widget&& w) noexcept
        : id(w.id)
    {
        std::println("Widget({}) move-constructed", id);
    }
    ~Widget() { std::println("Widget({}) destructed", id); }
    auto operator<=>(const Widget&) const = default; // C++20 spaceship
};

// 示例 1: 初始化方式
void example_init()
{
    std::println("\n=== 示例 1: 初始化方式 ===");

    // ✅ 默认构造（空 vector）
    std::vector<int> v1;
    std::println("v1.size()={}, v1.capacity()={}", v1.size(), v1.capacity());

    // ✅ 初始化列表
    std::vector<int> v2 { 1, 2, 3, 4, 5 };
    print_container(v2, "v2");

    // ✅ 指定大小 + 默认值
    std::vector<double> v3(5, 3.14); // 5 个 3.14
    print_container(v3, "v3");

    // ✅ 指定大小（值初始化为0）
    std::vector<int> v4(4); // {0,0,0,0}
    print_container(v4, "v4");

    // ✅ 从另一个 vector 拷贝
    std::vector<int> v5 = v2;
    print_container(v5, "v5 (copy of v2)");

    // ✅ 从迭代器范围构造
    std::vector<int> v6(v2.begin() + 1, v2.end() - 1); // {2,3,4}
    print_container(v6, "v6 (range from v2)");

    // ✅ 使用 std::initializer_list（同初始化列表）
    auto v7 = std::vector<int> { 10, 20, 30 };
    print_container(v7, "v7");
}

// 示例 2: 容量管理
void example_capacity()
{
    std::println("\n=== 示例 2: 容量管理 ===");

    std::vector<int> v;

    std::println("初始: size={}, capacity={}", v.size(), v.capacity());

    // ✅ reserve —— 预分配内存（不改变 size）
    v.reserve(10);
    std::println("reserve(10) 后: size={}, capacity={}", v.size(), v.capacity());

    // ✅ push_back 触发扩容演示
    for (int i = 1; i <= 12; ++i) {
        v.push_back(i);
        std::println("push_back({}) 后: size={}, capacity={}", i, v.size(), v.capacity());
    }

    // ✅ resize —— 改变 size（可扩容或缩容）
    v.resize(5); // 截断到前5个
    std::println("resize(5) 后: size={}, capacity={}", v.size(), v.capacity());
    print_container(v, "v after resize(5)");

    v.resize(8, 99); // 扩展到8，新元素=99
    print_container(v, "v after resize(8,99)");

    // ✅ shrink_to_fit —— 请求释放多余容量（非强制）
    v.shrink_to_fit();
    std::println("shrink_to_fit 后: size={}, capacity={}", v.size(), v.capacity());
}

// 示例 3: 元素访问
void example_access()
{
    std::println("\n=== 示例 3: 元素访问 ===");

    std::vector<char> chars { 'A', 'B', 'C', 'D' };

    // ✅ operator[]
    chars[0] = 'X';

    // ✅ at() —— 边界检查
    try {
        chars.at(10) = 'Y'; // 抛异常
    } catch (const std::out_of_range& e) {
        std::println("Caught: {}", e.what());
    }

    // ✅ front() / back()
    std::println("front: {}, back: {}", chars.front(), chars.back());

    // ✅ data() —— 获取底层指针（兼容C接口）
    char* ptr = chars.data();
    std::println("data()[2] = {}", ptr[2]);

    print_container(chars, "chars");
}

// 示例 4: 插入与删除
void example_modify()
{
    std::println("\n=== 示例 4: 插入与删除 ===");

    std::vector<int> v { 1, 2, 3, 4, 5 };

    print_container(v, "原始");

    // ✅ push_back / emplace_back
    v.push_back(6); // 拷贝插入
    v.emplace_back(7); // 原地构造（对复杂类型更高效）
    print_container(v, "push_back(6), emplace_back(7)");

    // ✅ insert —— 在位置插入
    auto it = v.begin() + 2;
    v.insert(it, 99); // 在索引2处插入99
    print_container(v, "insert 99 at index 2");

    // ✅ insert 多个元素
    v.insert(v.end(), 3, 88); // 在末尾插入3个88
    print_container(v, "insert 3x88 at end");

    // ✅ erase —— 删除单个元素
    it = v.begin() + 1;
    v.erase(it); // 删除索引1
    print_container(v, "erase at index 1");

    // ✅ erase —— 删除范围
    it = v.erase(v.begin() + 2, v.begin() + 4); // 删除 [2,4)
    print_container(v, "erase range [2,4)");

    // ✅ pop_back
    v.pop_back();
    print_container(v, "pop_back");

    // ✅ clear
    v.clear();
    std::println("clear 后: size={}, capacity={}", v.size(), v.capacity());
}

// 示例 5: 与 STL 算法配合
void example_algorithms()
{
    std::println("\n=== 示例 5: STL 算法配合 ===");

    std::vector<int> v { 4, 1, 9, 0, 5, 0, 3, 0, 2, 8 };

    print_container(v, "原始数据");

    // ✅ sort
    std::sort(v.begin(), v.end());
    print_container(v, "排序后");

    // ✅ find
    auto it = std::find(v.begin(), v.end(), 5);
    if (it != v.end()) {
        std::println("找到 5，索引 = {}", std::distance(v.begin(), it));
    }

    // ✅ count
    size_t zeros = std::count(v.begin(), v.end(), 0);
    std::println("0 的个数: {}", zeros);

    // ✅ remove_if —— 移除偶数（注意：返回新逻辑结尾）
    auto new_end = std::remove_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
    // ✅ 实际删除：erase + remove 惯用法
    v.erase(new_end, v.end());
    print_container(v, "移除偶数后");

    // ✅ unique —— 去重（需先排序）
    std::sort(v.begin(), v.end());
    auto uniq_end = std::unique(v.begin(), v.end());
    v.erase(uniq_end, v.end());
    print_container(v, "去重后");

    // ✅ transform —— 平方每个元素
    std::transform(v.begin(), v.end(), v.begin(), [](int x) { return x * x; });
    print_container(v, "平方后");

    // ✅ accumulate
    int sum = std::accumulate(v.begin(), v.end(), 0);
    std::println("总和: {}", sum);

    // ✅ iota —— 填充序列
    std::vector<int> seq(5);
    std::iota(seq.begin(), seq.end(), 10); // 10,11,12,13,14
    print_container(seq, "iota 从10开始");
}

// 示例 6: 移动语义与自定义类型
void example_move()
{
    std::println("\n=== 示例 6: 移动语义与自定义类型 ===");

    std::vector<Widget> widgets;

    // ✅ push_back —— 可能触发拷贝
    widgets.push_back(Widget(1)); // 临时对象 → move-construct

    // ✅ emplace_back —— 直接在 vector 内存中构造
    widgets.emplace_back(2); // 直接构造，无临时对象

    // ✅ 预留空间避免多次构造/析构
    widgets.reserve(5);
    widgets.emplace_back(3);
    widgets.emplace_back(4);

    std::println("widgets 大小: {}", widgets.size());

    // ✅ 析构会在 vector 离开作用域时自动调用
}

// 示例 7: 二维 vector
void example_2d()
{
    std::println("\n=== 示例 7: 二维 vector ===");

    // 创建 3x4 矩阵，初始化为0
    std::vector<std::vector<int>> matrix(3, std::vector<int>(4, 0));

    // 赋值
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            matrix[i][j] = static_cast<int>(i * 4 + j + 1);
        }
    }

    // 打印
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            std::print("{:2d} ", elem);
        }
        std::println("");
    }
}

// 示例 8: 与 C 风格数组交互
void example_c_array()
{
    std::println("\n=== 示例 8: 与 C 风格数组交互 ===");

    std::vector<int> v { 10, 20, 30, 40, 50 };

    // ✅ data() —— 获取底层指针，传给 C 函数
    auto print_c_array = [](const int* arr, size_t len) {
        for (size_t i = 0; i < len; ++i) {
            std::print("{} ", arr[i]);
        }
        std::println("");
    };

    print_c_array(v.data(), v.size());
}

// 主函数
auto main(int argc, char* argv[]) -> int
{
    example_init();
    example_capacity();
    example_access();
    example_modify();
    example_algorithms();
    example_move();
    example_2d();
    example_c_array();

    std::println("\n✅ std::vector 学习完成！");
    return 0;
}