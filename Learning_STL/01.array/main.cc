// ============================
// file: learn_std_array.cc
// 说明：全面学习 std::array 的现代 C++ 用法
// 编译：g++ -std=c++17 learn_std_array.cc -o learn_array
// ============================

#include <algorithm> // sort, find, count, remove_if, copy
#include <array>
#include <iterator> // std::ostream_iterator
#include <numeric> // accumulate
#include <print> // C++23: std::println (可选，若不支持可注释掉或改回 cout)

// 辅助函数：打印容器（支持任何支持 begin/end 的容器）
template <typename Container>
void print_container(const Container& c, const char* label = "")
{
    if (*label)
        std::println("{}: ", label); // 若支持 C++23
    // 若不支持 std::println，请用下面这行替代：
    // if (*label) std::cout << label << ": ";
    for (const auto& elem : c) {
        std::print("{} ", elem); // 或 std::cout << elem << " ";
    }
    std::println(""); // 或 std::cout << std::endl;
}

// 示例 1: 基本初始化和容量
void example_basic()
{
    std::println("\n=== 示例 1: 基本初始化与容量 ===");

    // ✅ 方式1: 显式指定类型和大小
    std::array<int, 5> arr1 { 1, 2, 3, 4, 5 };

    // ✅ 方式2: CTAD（C++17 起支持类模板参数推导）
    std::array arr2 { 10, 20, 30 }; // 类型 int, 大小 3

    // ✅ 方式3: 默认初始化（值初始化为0）
    std::array<double, 4> arr3 {}; // {0.0, 0.0, 0.0, 0.0}

    // ✅ 方式4: 部分初始化（其余补0）
    std::array<int, 6> arr4 { 1, 2 }; // {1,2,0,0,0,0}

    print_container(arr1, "arr1");
    print_container(arr2, "arr2");
    print_container(arr3, "arr3");
    print_container(arr4, "arr4");

    std::println("arr1.size() = {}", arr1.size());
    std::println("arr1.max_size() = {}", arr1.max_size());
    std::println("arr1.empty() = {}", arr1.empty() ? "true" : "false");
}

// 示例 2: 元素访问
void example_access()
{
    std::println("\n=== 示例 2: 元素访问 ===");

    std::array<char, 4> chars { 'A', 'B', 'C', 'D' };

    // ✅ operator[]
    chars[0] = 'X';
    // ✅ at() —— 带边界检查，越界抛异常
    try {
        chars.at(10) = 'Y'; // 会抛出 std::out_of_range
    } catch (const std::out_of_range& e) {
        std::println("Caught exception: {}", e.what());
    }

    // ✅ front() / back()
    std::println("front: {}, back: {}", chars.front(), chars.back());

    // ✅ data() —— 获取底层 C 风格数组指针
    char* ptr = chars.data();
    std::println("data()[2] = {}", ptr[2]);

    print_container(chars, "chars after access");
}

// 示例 3: 迭代器与范围 for
void example_iterators()
{
    std::println("\n=== 示例 3: 迭代器与范围 for ===");

    std::array<int, 5> nums { 5, 3, 8, 1, 9 };

    // ✅ 正向迭代
    std::println("Forward:");
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        std::print("{} ", *it);
    }
    std::println("");

    // ✅ 反向迭代
    std::println("Reverse:");
    for (auto it = nums.rbegin(); it != nums.rend(); ++it) {
        std::print("{} ", *it);
    }
    std::println("");

    // ✅ const 迭代器（不修改）
    std::println("Const forward:");
    for (auto it = nums.cbegin(); it != nums.cend(); ++it) {
        std::print("{} ", *it);
    }
    std::println("");

    // ✅ 范围 for（最常用）
    std::println("Range-for (read-only):");
    for (const auto& x : nums) {
        std::print("{} ", x);
    }
    std::println("");

    std::println("Range-for (modify):");
    for (auto& x : nums) {
        x *= 2; // 修改元素
    }
    print_container(nums, "After doubling");
}

// 示例 4: 修改操作 — fill & swap
void example_modify()
{
    std::println("\n=== 示例 4: fill & swap ===");

    std::array<int, 4> a1 { 1, 2, 3, 4 };
    std::array<int, 4> a2 { 5, 6, 7, 8 };

    std::println("Before fill: ");
    print_container(a1, "a1");

    // ✅ fill —— 全部设为同一个值
    a1.fill(99);
    print_container(a1, "a1 after fill(99)");

    std::println("Before swap:");
    print_container(a1, "a1");
    print_container(a2, "a2");

    // ✅ swap —— 交换两个 array 内容（必须同类型同大小）
    a1.swap(a2);

    std::println("After swap:");
    print_container(a1, "a1");
    print_container(a2, "a2");
}

// 示例 5: 与 STL 算法配合
void example_algorithms()
{
    std::println("\n=== 示例 5: STL 算法配合 ===");

    std::array<int, 8> data { 4, 1, 9, 0, 5, 0, 3, 0 };

    print_container(data, "Original data");

    // ✅ sort
    std::sort(data.begin(), data.end());
    print_container(data, "After sort");

    // ✅ find
    auto it = std::find(data.begin(), data.end(), 5);
    if (it != data.end()) {
        std::println("Found 5 at index: {}", std::distance(data.begin(), it));
    }

    // ✅ count
    size_t zeros = std::count(data.begin(), data.end(), 0);
    std::println("Count of 0: {}", zeros);

    // ✅ remove_if —— 移除偶数（注意：不改变 size，返回新逻辑结尾）
    auto new_end = std::remove_if(data.begin(), data.end(), [](int x) { return x % 2 == 0; });
    // ✅ 手动“擦除”：std::array 不能 resize，但我们可以用 fill 或 ignore 尾部
    std::fill(new_end, data.end(), -1); // 标记移除部分
    print_container(data, "After remove_if(even) + fill(-1)");

    // ✅ accumulate
    int sum = std::accumulate(data.begin(), data.end(), 0);
    std::println("Sum: {}", sum);

    // ✅ copy 到另一个 array（必须大小足够）
    std::array<int, 8> copy_data;
    std::copy(data.begin(), data.end(), copy_data.begin());
    print_container(copy_data, "Copied data");
}

// 示例 6: 与 C 风格数组互操作
void example_c_array()
{
    std::println("\n=== 示例 6: 与 C 风格数组互操作 ===");

    int c_arr[] = { 10, 20, 30, 40 };
    constexpr size_t N = sizeof(c_arr) / sizeof(c_arr[0]);

    // ✅ 从 C 数组构造 std::array（C++14 起可用 std::to_array，或手动）
    std::array<int, N> cpp_arr;
    std::copy(std::begin(c_arr), std::end(c_arr), cpp_arr.begin());
    print_container(cpp_arr, "Converted from C array");

    // ✅ 反向：用 data() 传给 C 函数
    auto print_c_array = [](const int* arr, size_t len) {
        for (size_t i = 0; i < len; ++i) {
            std::print("{} ", arr[i]);
        }
        std::println("");
    };

    print_c_array(cpp_arr.data(), cpp_arr.size());
}

// 示例 7: 编译期能力（constexpr）
constexpr auto make_squared_array()
{
    std::array<int, 5> arr {};
    for (size_t i = 0; i < arr.size(); ++i) {
        arr[i] = static_cast<int>(i * i);
    }
    return arr;
}

void example_constexpr()
{
    std::println("\n=== 示例 7: constexpr 支持 ===");

    constexpr auto sq = make_squared_array();
    print_container(sq, "Compile-time squared array");
}

// 示例 8: 多维数组
void example_2d()
{
    std::println("\n=== 示例 8: 多维数组 ===");

    // 3x4 矩阵
    std::array<std::array<int, 4>, 3> matrix { { { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 } } };

    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            std::print("{:2d} ", matrix[i][j]); // 格式化对齐
        }
        std::println("");
    }
}

// 主函数
auto main(int argc, char* argv[]) -> int
{
    example_basic();
    example_access();
    example_iterators();
    example_modify();
    example_algorithms();
    example_c_array();
    example_constexpr();
    example_2d();

    std::println("\n✅ std::array 学习完成！");
    return 0;
}