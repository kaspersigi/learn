// ============================
// file: learn_std_priority_queue.cc
// 说明：全面学习 std::priority_queue 的现代 C++ 用法（std::cout 版本）
// 编译：g++ -std=c++17 learn_std_priority_queue.cc -o learn_priority_queue
// ============================

#include <functional> // std::greater
#include <iostream>
#include <queue>
#include <string>
#include <vector>

// ✅ 辅助函数：打印优先级队列（注意：需要复制，因为 pop() 会删除元素）
template <typename T, typename Container, typename Compare>
void print_pq(std::priority_queue<T, Container, Compare> pq, const char* label = "")
{
    if (*label)
        std::cout << label << " (size=" << pq.size() << "):" << std::endl;
    if (pq.empty()) {
        std::cout << "  <empty>" << std::endl;
        return;
    }
    std::cout << "  优先级从高到低:" << std::endl;
    int i = 1;
    while (!pq.empty()) {
        std::cout << "    #" << i++ << ": " << pq.top() << std::endl;
        pq.pop();
    }
}

// 自定义类型
struct Task {
    std::string name;
    int priority; // 数值越大，优先级越高
    Task(std::string n, int p)
        : name(std::move(n))
        , priority(p)
    {
    }
};

// ✅ 为 Task 重载 operator<<（用于 std::cout）
std::ostream& operator<<(std::ostream& os, const Task& t)
{
    return os << t.name << "(P" << t.priority << ")";
}

// ✅ 为 Task 定义比较器（优先级高的 Task 排在前面）
struct CompareTask {
    bool operator()(const Task& a, const Task& b)
    {
        return a.priority < b.priority; // 最大堆：优先级高的先出
    }
};

// 示例 1: 基本用法与初始化（最大堆）
void example_basic()
{
    std::cout << "\n=== 示例 1: 基本用法（最大堆） ===" << std::endl;

    // ✅ 默认构造（最大堆，底层 vector）
    std::priority_queue<int> pq1;
    pq1.push(3);
    pq1.push(1);
    pq1.push(4);
    pq1.push(1);
    pq1.push(5);
    pq1.push(9);

    print_pq(pq1, "pq1 (最大堆)");

    // ✅ 修复：使用 vector + 迭代器范围构造
    std::vector<int> init_data = { 5, 3, 8, 1, 9 };
    std::priority_queue<int> pq2(init_data.begin(), init_data.end());
    print_pq(pq2, "pq2 (初始化列表)");

    // ✅ 拷贝构造
    std::priority_queue<int> pq3 = pq1;
    print_pq(pq3, "pq3 (拷贝 pq1)");

    // ✅ 访问堆顶
    if (!pq1.empty()) {
        std::cout << "堆顶元素: " << pq1.top() << std::endl;
    }
}

// 示例 2: 最小堆与自定义比较器
void example_min_heap()
{
    std::cout << "\n=== 示例 2: 最小堆与自定义比较器 ===" << std::endl;

    // ✅ 最小堆：使用 std::greater
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;
    min_pq.push(3);
    min_pq.push(1);
    min_pq.push(4);
    min_pq.push(1);
    min_pq.push(5);
    min_pq.push(9);

    print_pq(min_pq, "min_pq (最小堆)");

    // ✅ 自定义比较器（按字符串长度排序）
    auto cmp = [](const std::string& a, const std::string& b) {
        return a.length() < b.length(); // 长度大的优先
    };
    std::priority_queue<std::string, std::vector<std::string>, decltype(cmp)> len_pq(cmp);
    len_pq.push("hi");
    len_pq.push("hello");
    len_pq.push("a");
    len_pq.push("world");

    print_pq(len_pq, "len_pq (按长度，长的优先)");
}

// 示例 3: 自定义类型支持
void example_custom_type()
{
    std::cout << "\n=== 示例 3: 自定义类型 ===" << std::endl;

    // ✅ 使用自定义比较器
    std::priority_queue<Task, std::vector<Task>, CompareTask> task_pq;
    task_pq.emplace("编码", 1);
    task_pq.emplace("测试", 3); // 高优先级
    task_pq.emplace("部署", 2);
    task_pq.emplace("设计", 5); // 最高优先级
    task_pq.emplace("文档", 1);

    print_pq(task_pq, "task_pq (按优先级排序)");

    // ✅ 注意：优先级相同的元素，顺序不确定！
}

// 示例 4: 实战应用 —— Top K 高频元素
#include <unordered_map>

std::vector<int> topKFrequent(std::vector<int>& nums, int k)
{
    // 统计频次
    std::unordered_map<int, int> freq;
    for (int num : nums) {
        freq[num]++;
    }

    // 最小堆：保存频次最高的 k 个元素
    auto cmp = [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second > b.second; // 频次小的优先（最小堆）
    };
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)> min_heap(cmp);

    for (const auto& [num, count] : freq) {
        min_heap.push({ num, count });
        if (min_heap.size() > k) {
            min_heap.pop(); // 移除频次最小的
        }
    }

    // 提取结果
    std::vector<int> result;
    while (!min_heap.empty()) {
        result.push_back(min_heap.top().first);
        min_heap.pop();
    }
    return result; // 注意：顺序是频次从低到高
}

void example_top_k()
{
    std::cout << "\n=== 示例 4: 实战应用 —— Top K 高频元素 ===" << std::endl;

    std::vector<int> nums = { 1, 1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 5 };
    int k = 3;

    std::cout << "数组: ";
    for (int x : nums)
        std::cout << x << " ";
    std::cout << std::endl;

    std::vector<int> top_k = topKFrequent(nums, k);
    std::cout << "Top " << k << " 高频元素: ";
    for (int x : top_k)
        std::cout << x << " ";
    std::cout << std::endl;

    // 验证频次
    std::unordered_map<int, int> freq;
    for (int x : nums)
        freq[x]++;
    std::cout << "频次: ";
    for (int x : top_k) {
        std::cout << x << "(" << freq[x] << ") ";
    }
    std::cout << std::endl;
}

// 示例 5: 实战应用 —— Dijkstra 最短路径算法（简化版）
#include <climits>
#include <unordered_set>

struct Graph {
    int n;
    std::vector<std::vector<std::pair<int, int>>> adj; // {neighbor, weight}

    Graph(int nodes)
        : n(nodes)
        , adj(nodes)
    {
    }

    void add_edge(int u, int v, int w)
    {
        adj[u].push_back({ v, w });
        adj[v].push_back({ u, w }); // 无向图
    }

    std::vector<int> dijkstra(int start)
    {
        std::vector<int> dist(n, INT_MAX);
        dist[start] = 0;

        // 最小堆：{distance, node}
        auto cmp = [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.first > b.first; // 距离小的优先
        };
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)> pq(cmp);
        pq.push({ 0, start });

        std::unordered_set<int> visited;

        while (!pq.empty()) {
            int u = pq.top().second;
            [[maybe_unused]] int d = pq.top().first;
            pq.pop();

            if (visited.count(u))
                continue;
            visited.insert(u);

            for (const auto& [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({ dist[v], v });
                }
            }
        }

        return dist;
    }
};

void example_dijkstra()
{
    std::cout << "\n=== 示例 5: 实战应用 —— Dijkstra 最短路径 ===" << std::endl;

    // 构建图:
    //    1
    // 0 --- 1
    // | \   |
    // 4  2  2
    // |   \ |
    // 3 --- 2
    //    1
    Graph g(4);
    g.add_edge(0, 1, 1);
    g.add_edge(0, 2, 4);
    g.add_edge(0, 3, 3);
    g.add_edge(1, 2, 2);
    g.add_edge(2, 3, 1);

    std::vector<int> dist = g.dijkstra(0);

    std::cout << "从节点 0 出发的最短距离:" << std::endl;
    for (int i = 0; i < dist.size(); ++i) {
        std::cout << "  到节点 " << i << ": " << (dist[i] == INT_MAX ? "INF" : std::to_string(dist[i])) << std::endl;
    }
}

// 示例 6: 性能与使用建议
void example_performance()
{
    std::cout << "\n=== 示例 6: 性能与使用建议 ===" << std::endl;

    std::cout << "std::priority_queue 特性总结:" << std::endl;
    std::cout << "  - 底层: 默认 std::vector，必须支持随机访问" << std::endl;
    std::cout << "  - 操作: push, pop, top, empty, size" << std::endl;
    std::cout << "  - 时间复杂度: push/pop O(log n), top O(1)" << std::endl;
    std::cout << "  - 无迭代器: 不能遍历，需复制或改用底层容器" << std::endl;

    std::cout << "\n何时使用 priority_queue:" << std::endl;
    std::cout << "  - 需要按优先级处理元素（最高/最低优先级先出）" << std::endl;
    std::cout << "  - 算法题：Top K、堆排序、Dijkstra" << std::endl;
    std::cout << "  - 系统设计：任务调度、事件处理" << std::endl;

    std::cout << "\n何时不使用 priority_queue:" << std::endl;
    std::cout << "  - 需要 FIFO/LIFO → 用 queue/stack" << std::endl;
    std::cout << "  - 需要随机访问或遍历 → 用 vector" << std::endl;
    std::cout << "  - 需要频繁修改已有元素优先级 → 用 set/multiset" << std::endl;

    std::cout << "\n底层容器选择建议:" << std::endl;
    std::cout << "  - 一般情况 → 用默认 vector（缓存友好）" << std::endl;
    std::cout << "  - 频繁插入且数据量大 → 用 deque（避免 vector 扩容）" << std::endl;
    std::cout << "  - ❌ 不能用 list —— 不支持随机访问" << std::endl;

    std::cout << "\n比较器选择:" << std::endl;
    std::cout << "  - 最大堆 → std::less<T> (默认)" << std::endl;
    std::cout << "  - 最小堆 → std::greater<T>" << std::endl;
    std::cout << "  - 自定义优先级 → 自定义仿函数或 lambda" << std::endl;
}

// 主函数
auto main(int argc, char* argv[]) -> int
{
    example_basic();
    example_min_heap();
    example_custom_type();
    example_top_k();
    example_dijkstra();
    example_performance();

    std::cout << "\n✅ std::priority_queue 学习完成！" << std::endl;
    return 0;
}