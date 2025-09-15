// ============================
// file: learn_std_queue.cc
// 说明：全面学习 std::queue 的现代 C++ 用法（std::cout 版本）
// 编译：g++ -std=c++17 learn_std_queue.cc -o learn_queue
// ============================

#include <deque>
#include <iostream>
#include <list>
#include <queue>
#include <string>

// ✅ 修复：支持任意底层容器 Container
template <typename T, typename Container>
void print_queue(std::queue<T, Container> q, const char* label = "")
{
    if (*label)
        std::cout << label << " (size=" << q.size() << "):" << std::endl;
    if (q.empty()) {
        std::cout << "  <empty>" << std::endl;
        return;
    }
    std::cout << "  队首 -> 队尾:" << std::endl;
    while (!q.empty()) {
        std::cout << "    " << q.front();
        q.pop();
        if (!q.empty())
            std::cout << " <- ";
    }
    std::cout << std::endl;
}

// 自定义类型
struct Message {
    int id;
    std::string content;
    Message(int i, std::string c)
        : id(i)
        , content(std::move(c))
    {
    }
};

// ✅ 为 Message 重载 operator<<（用于 std::cout）
std::ostream& operator<<(std::ostream& os, const Message& m)
{
    return os << "Msg#" << m.id << ":\"" << m.content << "\"";
}

// 示例 1: 基本用法与初始化
void example_basic()
{
    std::cout << "\n=== 示例 1: 基本用法 ===" << std::endl;

    // ✅ 默认构造（底层容器是 deque）
    std::queue<int> q1;
    q1.push(1);
    q1.push(2);
    q1.push(3);

    print_queue(q1, "q1");

    // ✅ 从另一个 queue 拷贝
    std::queue<int> q2 = q1;
    print_queue(q2, "q2 (拷贝 q1)");

    // ✅ 访问队首和队尾
    if (!q1.empty()) {
        std::cout << "队首: " << q1.front() << ", 队尾: " << q1.back() << std::endl;
    }

    // ✅ 比较两个 queue（C++11 起支持）
    std::cout << "q1 == q2: " << (q1 == q2 ? "true" : "false") << std::endl;
    q2.pop();
    std::cout << "q1 == q2 after pop: " << (q1 == q2 ? "true" : "false") << std::endl;
}

// 示例 2: 自定义底层容器（list / deque）
void example_containers()
{
    std::cout << "\n=== 示例 2: 自定义底层容器 ===" << std::endl;

    // ✅ 使用 list 作为底层容器
    std::queue<int, std::list<int>> queue_list;
    queue_list.push(10);
    queue_list.push(20);
    queue_list.push(30);
    print_queue(queue_list, "queue_list (底层: list)");

    // ✅ 使用 deque（默认）
    std::queue<int, std::deque<int>> queue_deque;
    queue_deque.push(100);
    queue_deque.push(200);
    print_queue(queue_deque, "queue_deque (底层: deque)");

    // ❌ 不能使用 vector —— 因为 queue 需要高效的 pop_front（vector 的 pop_front 是 O(n)）
    // std::queue<int, std::vector<int>> queue_vector; // 编译错误！

    // ✅ 性能对比（概念性说明）
    std::cout << "\n底层容器性能对比:" << std::endl;
    std::cout << "  - deque: 两端操作高效，内存分段连续，最常用" << std::endl;
    std::cout << "  - list: 任意位置插入稳定，但内存不连续，缓存不友好" << std::endl;
    std::cout << "  - vector: ❌ 不支持！因为前端删除效率低" << std::endl;
}

// 示例 3: 自定义类型支持
void example_custom_type()
{
    std::cout << "\n=== 示例 3: 自定义类型 ===" << std::endl;

    std::queue<Message> msg_queue;
    msg_queue.emplace(1, "Hello");
    msg_queue.emplace(2, "World");
    msg_queue.emplace(3, "C++");

    std::cout << "消息队列 (size=" << msg_queue.size() << "):" << std::endl;
    while (!msg_queue.empty()) {
        std::cout << "  处理: " << msg_queue.front() << std::endl;
        msg_queue.pop();
    }
}

// 示例 4: 实战应用 —— 广度优先搜索（BFS）遍历二叉树
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x)
        : val(x)
        , left(nullptr)
        , right(nullptr)
    {
    }
};

void bfs_traverse(TreeNode* root)
{
    if (!root)
        return;

    std::queue<TreeNode*> q;
    q.push(root);

    std::cout << "BFS 遍历: ";
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        std::cout << node->val << " ";

        if (node->left)
            q.push(node->left);
        if (node->right)
            q.push(node->right);
    }
    std::cout << std::endl;
}

void example_bfs()
{
    std::cout << "\n=== 示例 4: 实战应用 —— BFS 遍历 ===" << std::endl;

    // 构建二叉树:
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    bfs_traverse(root);

    // 清理内存（实际项目中建议用智能指针）
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right;
    delete root;
}

// 示例 5: 实战应用 —— 生产者-消费者模型（简化版）
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>

std::queue<int> task_queue;
std::mutex mtx;
std::condition_variable cv;
bool finished = false;

void producer(int id, int count)
{
    for (int i = 1; i <= count; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::lock_guard<std::mutex> lock(mtx);
        task_queue.push(id * 100 + i);
        std::cout << "生产者 " << id << " 生产任务: " << task_queue.back() << std::endl;
        cv.notify_one();
    }
}

void consumer(int id)
{
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !task_queue.empty() || finished; });
        if (task_queue.empty() && finished)
            break;

        int task = task_queue.front();
        task_queue.pop();
        lock.unlock();

        std::cout << "消费者 " << id << " 处理任务: " << task << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

void example_producer_consumer()
{
    std::cout << "\n=== 示例 5: 实战应用 —— 生产者-消费者模型 ===" << std::endl;

    std::thread p1(producer, 1, 3);
    std::thread p2(producer, 2, 2);
    std::thread c1(consumer, 1);
    std::thread c2(consumer, 2);

    p1.join();
    p2.join();
    finished = true;
    cv.notify_all();
    c1.join();
    c2.join();

    std::cout << "生产者-消费者模型执行完毕" << std::endl;
}

// 示例 6: 性能与使用建议
void example_performance()
{
    std::cout << "\n=== 示例 6: 性能与使用建议 ===" << std::endl;

    std::cout << "std::queue 特性总结:" << std::endl;
    std::cout << "  - 底层: 默认 std::deque，可自定义（常用 std::list）" << std::endl;
    std::cout << "  - 操作: push, pop, front, back, empty, size" << std::endl;
    std::cout << "  - 时间复杂度: 所有操作 O(1)" << std::endl;
    std::cout << "  - 无迭代器: 不能遍历，需复制或改用底层容器" << std::endl;

    std::cout << "\n何时使用 queue:" << std::endl;
    std::cout << "  - 需要 FIFO 语义（先进先出）" << std::endl;
    std::cout << "  - 算法题：BFS、任务调度" << std::endl;
    std::cout << "  - 系统设计：消息队列、生产者-消费者模型" << std::endl;

    std::cout << "\n何时不使用 queue:" << std::endl;
    std::cout << "  - 需要随机访问或遍历 → 用 vector/deque" << std::endl;
    std::cout << "  - 需要优先级 → 用 priority_queue" << std::endl;
    std::cout << "  - 需要后进先出 → 用 stack" << std::endl;

    std::cout << "\n底层容器选择建议:" << std::endl;
    std::cout << "  - 一般情况 → 用默认 deque" << std::endl;
    std::cout << "  - 频繁 push/pop 且需要稳定迭代器 → 用 list" << std::endl;
    std::cout << "  - ❌ 不要用 vector —— 前端删除效率低" << std::endl;
}

// 主函数
auto main(int argc, char* argv[]) -> int
{
    example_basic();
    example_containers();
    example_custom_type();
    example_bfs();
    example_producer_consumer();
    example_performance();

    std::cout << "\n✅ std::queue 学习完成！" << std::endl;
    return 0;
}