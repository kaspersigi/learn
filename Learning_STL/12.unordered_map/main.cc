// ============================
// file: learn_std_unordered_map.cc
// 说明：全面学习 std::unordered_map 的现代 C++ 用法（std::cout 版本）
// 编译：g++ -std=c++17 learn_std_unordered_map.cc -o learn_unordered_map
// ============================

#include <algorithm> // for_each, transform
#include <functional> // std::hash, std::equal_to
#include <iostream> // 👈 必须包含
#include <iterator> // std::inserter
#include <numeric>
#include <string>
#include <unordered_map>

// 辅助函数：打印 map（无序，顺序不确定）
template <typename Map>
void print_map(const Map& m, const char* label = "")
{
    if (*label)
        std::cout << label << ":" << std::endl;
    for (const auto& [key, value] : m) {
        std::cout << "  " << key << ": " << value << std::endl;
    }
    std::cout << std::endl;
}

// 自定义键类型
struct UserID {
    int id;
    UserID(int i)
        : id(i)
    {
    }
    bool operator==(const UserID& other) const { return id == other.id; }
};

// 为 UserID 提供哈希函数
namespace std {
template <>
struct hash<UserID> {
    size_t operator()(const UserID& u) const
    {
        return hash<int>()(u.id);
    }
};
}

// 自定义值类型
struct UserProfile {
    std::string name;
    int age;
    UserProfile(std::string n, int a)
        : name(std::move(n))
        , age(a)
    {
    }
};

// ✅ 为 UserID 重载 operator<<
std::ostream& operator<<(std::ostream& os, const UserID& u)
{
    return os << u.id;
}

// ✅ 为 UserProfile 重载 operator<<
std::ostream& operator<<(std::ostream& os, const UserProfile& p)
{
    return os << p.name << " (" << p.age << "岁)";
}

// 自定义哈希函数（用于字符串键）
struct StringHash {
    size_t operator()(const std::string& s) const
    {
        size_t h = 0;
        for (char c : s) {
            h = h * 31 + static_cast<unsigned char>(c);
        }
        return h;
    }
};

// 示例 1: 基本用法与初始化
void example_basic()
{
    std::cout << "\n=== 示例 1: 基本用法与初始化 ===" << std::endl;

    // ✅ 默认构造
    std::unordered_map<std::string, int> word_count;
    word_count["apple"] = 3;
    word_count["banana"] = 5;
    word_count["cherry"] = 2;
    word_count["apple"] = 4; // 重复键 → 覆盖旧值！

    print_map(word_count, "word_count (无序)");

    // ✅ 初始化列表
    std::unordered_map<int, std::string> id_to_name {
        { 101, "Alice" },
        { 103, "Bob" },
        { 102, "Charlie" },
        { 101, "David" } // 重复键 → David 覆盖 Alice！
    };
    print_map(id_to_name, "id_to_name (初始化列表，重复键被覆盖)");

    // ✅ 使用自定义哈希和相等比较
    std::unordered_map<std::string, int, StringHash> custom_map;
    custom_map["hello"] = 1;
    custom_map["world"] = 2;
    custom_map["hello"] = 3; // 覆盖
    print_map(custom_map, "custom_map (自定义哈希)");

    // ✅ 指定桶数量
    std::unordered_map<std::string, int> bucket_map(20); // 预分配20个桶
    bucket_map.insert({ "a", 1 });
    bucket_map.insert({ "b", 2 });
    bucket_map.insert({ "c", 3 });
    print_map(bucket_map, "bucket_map (预分配20桶)");

    // ✅ 拷贝构造
    std::unordered_map<std::string, int> copy_map = word_count;
    print_map(copy_map, "copy_map");
}

// 示例 2: 插入与访问（多种方式）
void example_insert_access()
{
    std::cout << "\n=== 示例 2: 插入与访问 ===" << std::endl;

    std::unordered_map<std::string, int> scores;

    // ✅ 方式1: operator[] —— 不存在则插入默认值（0），然后赋值
    scores["Alice"] = 95;
    scores["Bob"] = 87;
    scores["Alice"] = 98; // 存在则覆盖

    // ✅ 方式2: insert —— 返回 pair<iterator, bool>
    auto [it1, success1] = scores.insert({ "Charlie", 92 });
    std::cout << "插入 Charlie: " << (success1 ? "成功" : "失败（键已存在）") << std::endl;

    auto [it2, success2] = scores.insert({ "Bob", 88 }); // Bob 已存在 → 失败，不覆盖！
    std::cout << "插入 Bob: " << (success2 ? "成功" : "失败（键已存在）") << std::endl;
    std::cout << "Bob 的分数仍是: " << it2->second << std::endl;

    // ✅ 方式3: emplace —— 原地构造 pair
    auto [it3, success3] = scores.emplace("Diana", 90);
    std::cout << "emplace Diana: " << (success3 ? "成功" : "失败") << std::endl;

    // ✅ 方式4: try_emplace (C++17) —— 不存在才构造
    auto [it4, success4] = scores.try_emplace("Alice", 100); // Alice 存在 → 不构造，不覆盖
    std::cout << "try_emplace Alice: " << (success4 ? "成功" : "失败") << std::endl;
    std::cout << "Alice 的分数仍是: " << it4->second << std::endl;

    // ✅ 方式5: insert_or_assign (C++17) —— 存在则赋值，不存在则插入
    auto [it5, success5] = scores.insert_or_assign("Eve", 85); // Eve 不存在 → 插入
    auto [it6, success6] = scores.insert_or_assign("Bob", 89); // Bob 存在 → 赋值
    std::cout << "insert_or_assign Eve: " << (success5 ? "插入" : "赋值") << std::endl;
    std::cout << "insert_or_assign Bob: " << (success6 ? "插入" : "赋值") << std::endl;

    print_map(scores, "最终 scores");
}

// 示例 3: 查找与删除
void example_find_erase()
{
    std::cout << "\n=== 示例 3: 查找与删除 ===" << std::endl;

    std::unordered_map<std::string, int> m {
        { "Alice", 95 },
        { "Bob", 87 },
        { "Charlie", 92 },
        { "Diana", 90 }
    };

    print_map(m, "原始");

    // ✅ find —— 返回迭代器
    auto it = m.find("Bob");
    if (it != m.end()) {
        std::cout << "找到 Bob: " << it->second << "分" << std::endl;
    } else {
        std::cout << "未找到 Bob" << std::endl;
    }

    // ✅ count —— 对 map 总是 0 或 1
    std::cout << "Bob 的个数: " << m.count("Bob") << std::endl;

// ✅ contains (C++20) —— 更语义化
#if __cplusplus >= 202002L
    if (m.contains("Alice")) {
        std::cout << "包含 Alice" << std::endl;
    }
#endif

    // ✅ at —— 带异常检查
    try {
        [[maybe_unused]] int score = m.at("Charlie");
        std::cout << "Charlie: " << score << "分" << std::endl;
        score = m.at("Unknown"); // 抛出 std::out_of_range
    } catch (const std::out_of_range& e) {
        std::cout << "at('Unknown'): " << e.what() << std::endl;
    }

    // ✅ erase by key
    size_t erased = m.erase("Bob"); // 返回删除的元素个数（0或1）
    std::cout << "删除 Bob: 删除了 " << erased << " 个元素" << std::endl;

    // ✅ erase by iterator
    auto it2 = m.find("Diana");
    if (it2 != m.end()) {
        m.erase(it2); // 删除 Diana
    }

    print_map(m, "删除后");

    // ✅ clear
    m.clear();
    std::cout << "clear 后 size = " << m.size() << std::endl;
}

// 示例 4: 哈希表信息与性能控制
void example_hash_info()
{
    std::cout << "\n=== 示例 4: 哈希表信息与性能控制 ===" << std::endl;

    std::unordered_map<int, std::string> m;
    for (int i = 1; i <= 10; ++i) {
        m[i] = "value" + std::to_string(i);
    }

    print_map(m, "数据");

    // ✅ 哈希表信息
    std::cout << "size: " << m.size() << std::endl;
    std::cout << "bucket_count: " << m.bucket_count() << std::endl;
    std::cout << "load_factor: " << m.load_factor() << std::endl;
    std::cout << "max_load_factor: " << m.max_load_factor() << std::endl;

    // ✅ 遍历每个桶（调试用）
    std::cout << "各桶元素:" << std::endl;
    for (size_t i = 0; i < m.bucket_count(); ++i) {
        std::cout << "桶 " << i << " (大小 " << m.bucket_size(i) << "): ";
        for (auto it = m.begin(i); it != m.end(i); ++it) {
            std::cout << "(" << it->first << "," << it->second << ") ";
        }
        std::cout << std::endl;
    }

    // ✅ 设置最大负载因子（默认1.0）
    m.max_load_factor(0.7); // 更低 → 更少冲突，更多内存
    std::cout << "设置 max_load_factor=0.7 后: " << m.load_factor() << std::endl;

    // ✅ rehash —— 强制重建哈希表
    m.rehash(50);
    std::cout << "rehash(50) 后 bucket_count = " << m.bucket_count() << std::endl;
}

// 示例 5: 自定义键类型
void example_custom_key()
{
    std::cout << "\n=== 示例 5: 自定义键类型 ===" << std::endl;

    std::unordered_map<UserID, UserProfile> user_db;
    user_db.emplace(UserID(101), UserProfile("Alice", 25));
    user_db.emplace(UserID(103), UserProfile("Bob", 30));
    user_db.emplace(UserID(102), UserProfile("Charlie", 28));

    std::cout << "用户数据库:" << std::endl;
    for (const auto& [id, profile] : user_db) {
        std::cout << "  ID " << id << ": " << profile << std::endl;
    }

    // ✅ 查找
    auto it = user_db.find(UserID(102));
    if (it != user_db.end()) {
        std::cout << "找到 ID 102: " << it->second << std::endl;
    }

    // ✅ 修改
    if (auto it2 = user_db.find(UserID(101)); it2 != user_db.end()) {
        it2->second.age = 26; // 修改年龄
    }

    std::cout << "修改后:" << std::endl;
    print_map(user_db, "user_db");
}

// 示例 6: 与 STL 算法配合
void example_algorithms()
{
    std::cout << "\n=== 示例 6: 与 STL 算法配合 ===" << std::endl;

    std::unordered_map<std::string, int> m {
        { "apple", 3 },
        { "banana", 5 },
        { "cherry", 2 }
    };

    // ✅ for_each —— 遍历并修改值
    std::for_each(m.begin(), m.end(), [](auto& pair) {
        pair.second *= 2; // 数量翻倍
    });
    print_map(m, "数量翻倍后");

    // ✅ transform —— 创建新 map（键不变，值变换）
    std::unordered_map<std::string, std::string> desc_map;
    std::transform(m.begin(), m.end(), std::inserter(desc_map, desc_map.begin()),
        [](const auto& pair) {
            return std::make_pair(pair.first, "count=" + std::to_string(pair.second));
        });
    print_map(desc_map, "描述性 map");

    // ✅ accumulate —— 计算总数量
    int total = std::accumulate(m.begin(), m.end(), 0,
        [](int sum, const auto& pair) { return sum + pair.second; });
    std::cout << "总数量: " << total << std::endl;
}

// 示例 7: 性能与使用建议
void example_performance()
{
    std::cout << "\n=== 示例 7: 性能与使用建议 ===" << std::endl;

    std::cout << "std::unordered_map 特性总结:" << std::endl;
    std::cout << "  - 底层: 哈希表（链地址法）" << std::endl;
    std::cout << "  - 插入/删除/查找: 平均 O(1)，最坏 O(n)" << std::endl;
    std::cout << "  - 无序: 遍历顺序不确定" << std::endl;
    std::cout << "  - 键唯一: 不允许重复键" << std::endl;
    std::cout << "  - 迭代器稳定性: ❌ 插入可能导致 rehash，使所有迭代器失效！" << std::endl;
    std::cout << "  - 内存开销: 较高（哈希桶 + 节点）" << std::endl;

    std::cout << "\n何时使用 unordered_map:" << std::endl;
    std::cout << "  - 需要键值对映射 + 快速查找（不需要排序）" << std::endl;
    std::cout << "  - 数据量大（> 1000），性能优势明显" << std::endl;
    std::cout << "  - 高频查找/插入/删除场景（如缓存、词频统计）" << std::endl;

    std::cout << "\n何时不使用 unordered_map:" << std::endl;
    std::cout << "  - 需要按键排序 → 用 map" << std::endl;
    std::cout << "  - 允许重复键 → 用 unordered_multimap" << std::endl;
    std::cout << "  - 数据量小（< 100）→ 用 vector<pair> + 线性查找，可能更快" << std::endl;

    std::cout << "\n性能优化建议:" << std::endl;
    std::cout << "  - 预分配桶数量: unordered_map(size_t n)" << std::endl;
    std::cout << "  - 设置合适的 max_load_factor (默认 1.0)" << std::endl;
    std::cout << "  - 提供高质量的哈希函数（避免冲突）" << std::endl;
    std::cout << "  - 避免在遍历时插入（可能导致 rehash 和迭代器失效）" << std::endl;
    std::cout << "  - 对小对象，考虑使用 operator[] 而非 insert（更简洁）" << std::endl;
}

// 主函数
auto main(int argc, char* argv[]) -> int
{
    example_basic();
    example_insert_access();
    example_find_erase();
    example_hash_info();
    example_custom_key();
    example_algorithms();
    example_performance();

    std::cout << "\n✅ std::unordered_map 学习完成！" << std::endl;
    return 0;
}