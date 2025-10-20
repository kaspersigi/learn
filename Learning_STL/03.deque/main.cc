// ============================
// file: learn_std_deque.cc
// 说明：全面学习 std::deque 的现代 C++ 用法
// 编译：g++ -std=c++17 learn_std_deque.cc -o learn_deque
// ============================

#include <algorithm> // sort, find, remove_if, transform, copy
#include <deque>
#include <iterator> // std::distance
#include <numeric> // accumulate, iota
#include <print> // C++23 (可选)

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

// 自定义类型（带日志）
struct Item {
    int id;
    Item(int i)
        : id(i)
    {
        std::println("Item({}) constructed", i);
    }
    Item(const Item& other)
        : id(other.id)
    {
        std::println("Item({}) copy-constructed", id);
    }
    Item(Item&& other) noexcept
        : id(other.id)
    {
        std::println("Item({}) move-constructed", id);
    }
    ~Item() { std::println("Item({}) destructed", id); }
    auto operator<=>(const Item&) const = default;
};

// 示例 1: 初始化方式
void example_init()
{
    std::println("\n=== 示例 1: 初始化方式 ===");

    // ✅ 默认构造
    std::deque<int> dq1;
    std::println("dq1.size() = {}", dq1.size());

    // ✅ 初始化列表
    std::deque<int> dq2 { 1, 2, 3, 4, 5 };
    print_container(dq2, "dq2");

    // ✅ 指定大小 + 默认值
    std::deque<double> dq3(3, 3.14);
    print_container(dq3, "dq3");

    // ✅ 指定大小（值初始化）
    std::deque<int> dq4(4);
    print_container(dq4, "dq4");

    // ✅ 拷贝构造
    std::deque<int> dq5 = dq2;
    print_container(dq5, "dq5 (copy)");

    // ✅ 从迭代器范围构造
    std::deque<int> dq6(dq2.begin() + 1, dq2.end() - 1);
    print_container(dq6, "dq6 (range)");
}

// 示例 2: 双端操作 —— deque 的核心优势！
void example_double_ended()
{
    std::println("\n=== 示例 2: 双端操作（核心优势） ===");

    std::deque<int> dq;

    // ✅ push_back / pop_back（像 vector）
    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);

    // ✅ push_front / pop_front（vector 不支持！）
    dq.push_front(0);
    dq.push_front(-1);

    print_container(dq, "After push_front/back");

    // ✅ pop_front
    dq.pop_front(); // 移除 -1
    // ✅ pop_back
    dq.pop_back(); // 移除 3

    print_container(dq, "After pop_front/back");

    // ✅ 访问两端
    std::println("front: {}, back: {}", dq.front(), dq.back());
}

// 示例 3: 随机访问与迭代器
void example_access()
{
    std::println("\n=== 示例 3: 随机访问与迭代器 ===");

    std::deque<char> dq { 'A', 'B', 'C', 'D', 'E' };

    // ✅ operator[]
    dq[0] = 'X';

    // ✅ at() —— 边界检查
    try {
        dq.at(10) = 'Y'; // 抛异常
    } catch (const std::out_of_range& e) {
        std::println("Caught: {}", e.what());
    }

    // ✅ 迭代器（正向、反向、const）
    std::println("Forward:");
    for (auto it = dq.begin(); it != dq.end(); ++it) {
        std::print("{} ", *it);
    }
    std::println("");

    std::println("Reverse:");
    for (auto it = dq.rbegin(); it != dq.rend(); ++it) {
        std::print("{} ", *it);
    }
    std::println("");

    // ✅ 范围 for
    std::println("Range-for:");
    for (const auto& c : dq) {
        std::print("{} ", c);
    }
    std::println("");
}

// 示例 4: 插入与删除（任意位置）
void example_insert_erase()
{
    std::println("\n=== 示例 4: 插入与删除（任意位置） ===");

    std::deque<int> dq { 10, 20, 30, 40 };

    print_container(dq, "原始");

    // ✅ insert —— 在位置插入单个元素
    auto it = dq.begin() + 2;
    dq.insert(it, 99); // 在索引2插入99
    print_container(dq, "insert 99 at index 2");

    // ✅ insert —— 插入多个相同元素
    dq.insert(dq.end(), 3, 88); // 末尾插入3个88
    print_container(dq, "insert 3x88 at end");

    // ✅ insert —— 插入初始化列表
    dq.insert(dq.begin(), { 1, 2, 3 });
    print_container(dq, "insert {1,2,3} at begin");

    // ✅ erase —— 删除单个元素
    it = dq.begin() + 1;
    dq.erase(it);
    print_container(dq, "erase at index 1");

    // ✅ erase —— 删除范围
    dq.erase(dq.begin() + 2, dq.begin() + 5);
    print_container(dq, "erase range [2,5)");

    // ✅ clear
    dq.clear();
    std::println("clear 后 size = {}", dq.size());
}

// 示例 5: 与 STL 算法配合
void example_algorithms()
{
    std::println("\n=== 示例 5: STL 算法配合 ===");

    std::deque<int> dq { 4, 1, 9, 0, 5, 0, 3, 0, 2, 8 };

    print_container(dq, "原始数据");

    // ✅ sort —— deque 支持随机访问，可排序
    std::sort(dq.begin(), dq.end());
    print_container(dq, "排序后");

    // ✅ find
    auto it = std::find(dq.begin(), dq.end(), 5);
    if (it != dq.end()) {
        std::println("找到 5，索引 = {}", std::distance(dq.begin(), it));
    }

    // ✅ count
    size_t zeros = std::count(dq.begin(), dq.end(), 0);
    std::println("0 的个数: {}", zeros);

    // ✅ remove_if + erase（惯用法）
    auto new_end = std::remove_if(dq.begin(), dq.end(), [](int x) { return x % 2 == 0; });
    dq.erase(new_end, dq.end());
    print_container(dq, "移除偶数后");

    // ✅ transform
    std::transform(dq.begin(), dq.end(), dq.begin(), [](int x) { return x * x; });
    print_container(dq, "平方后");

    // ✅ accumulate
    int sum = std::accumulate(dq.begin(), dq.end(), 0);
    std::println("总和: {}", sum);

    // ✅ iota（填充序列）
    std::deque<int> seq(5);
    std::iota(seq.begin(), seq.end(), 100);
    print_container(seq, "iota 从100开始");
}

// 示例 6: 移动语义与自定义类型
void example_move()
{
    std::println("\n=== 示例 6: 移动语义与自定义类型 ===");

    std::deque<Item> items;

    // ✅ push_back —— 可能 move
    items.push_back(Item(1));

    // ✅ emplace_back —— 直接构造
    items.emplace_back(2);

    // ✅ push_front —— deque 特有！
    items.push_front(Item(3));
    items.emplace_front(4); // C++11 起支持 emplace_front

    std::println("items 大小: {}", items.size());

    // ✅ 析构自动调用
}

// 示例 7: 作为 stack / queue 的底层容器（演示）
void example_as_container()
{
    std::println("\n=== 示例 7: 作为 stack / queue 的底层容器 ===");

    // ✅ 用 deque 实现一个栈
    std::deque<int> stack;
    stack.push_back(1); // 入栈
    stack.push_back(2);
    stack.push_back(3);

    std::println("栈顶: {}", stack.back());
    stack.pop_back(); // 出栈
    std::println("出栈后栈顶: {}", stack.back());

    // ✅ 用 deque 实现一个队列
    std::deque<int> queue;
    queue.push_back(10); // 入队
    queue.push_back(20);
    queue.push_back(30);

    std::println("队首: {}", queue.front());
    queue.pop_front(); // 出队
    std::println("出队后队首: {}", queue.front());
}

// 示例 8: 内存结构说明（无 data()）
void example_memory()
{
    std::println("\n=== 示例 8: 内存结构说明 ===");

    std::deque<int> dq { 1, 2, 3, 4, 5 };

    // ❌ deque 没有 .data() 成员 —— 因为内存不连续！
    // int* ptr = dq.data(); // 编译错误！

    std::println("deque 不提供 .data() —— 内存分段存储，不连续。");

    // ✅ 但你可以取第一个元素的地址（仅当不为空）
    if (!dq.empty()) {
        int* first_elem = &dq[0];
        std::println("第一个元素地址: {:p}", static_cast<void*>(first_elem));
        // 注意：这个指针只对第一个块有效，不能用于遍历整个 deque！
    }

    // ✅ 正确遍历：必须用迭代器或索引
    std::println("正确遍历方式：");
    for (size_t i = 0; i < dq.size(); ++i) {
        std::print("{} ", dq[i]);
    }
    std::println("");
}

// 主函数
auto main(int argc, char* argv[]) -> int
{
    example_init();
    example_double_ended();
    example_access();
    example_insert_erase();
    example_algorithms();
    example_move();
    example_as_container();
    example_memory();

    std::println("\n✅ std::deque 学习完成！");
    return 0;
}