// ============================
// file: learn_std_stack.cc
// 说明：全面学习 std::stack 的现代 C++ 用法（std::cout 版本）
// 编译：g++ -std=c++17 learn_std_stack.cc -o learn_stack
// ============================

#include <deque>
#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <vector>

// ✅ 修复：支持任意底层容器 Container
template <typename T, typename Container>
void print_stack(std::stack<T, Container> s, const char* label = "")
{
    if (*label)
        std::cout << label << " (size=" << s.size() << "):" << std::endl;
    if (s.empty()) {
        std::cout << "  <empty>" << std::endl;
        return;
    }
    std::cout << "  栈顶 -> 底部:" << std::endl;
    while (!s.empty()) {
        std::cout << "    " << s.top() << std::endl;
        s.pop();
    }
}

// 自定义类型
struct Task {
    std::string name;
    int priority;
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

// 示例 1: 基本用法与初始化
void example_basic()
{
    std::cout << "\n=== 示例 1: 基本用法 ===" << std::endl;

    // ✅ 默认构造（底层容器是 deque）
    std::stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);

    print_stack(s1, "s1");

    // ✅ 从另一个 stack 拷贝
    std::stack<int> s2 = s1;
    print_stack(s2, "s2 (拷贝 s1)");

    // ✅ 比较两个 stack（C++11 起支持）
    std::cout << "s1 == s2: " << (s1 == s2 ? "true" : "false") << std::endl;
    s2.pop();
    std::cout << "s1 == s2 after pop: " << (s1 == s2 ? "true" : "false") << std::endl;
}

// 示例 2: 自定义底层容器（vector / list / deque）
void example_containers()
{
    std::cout << "\n=== 示例 2: 自定义底层容器 ===" << std::endl;

    // ✅ 使用 vector 作为底层容器
    std::stack<int, std::vector<int>> stack_vector;
    stack_vector.push(10);
    stack_vector.push(20);
    stack_vector.push(30);
    print_stack(stack_vector, "stack_vector (底层: vector)");

    // ✅ 使用 list 作为底层容器
    std::stack<int, std::list<int>> stack_list;
    stack_list.push(100);
    stack_list.push(200);
    stack_list.push(300);
    print_stack(stack_list, "stack_list (底层: list)");

    // ✅ 使用 deque（默认）
    std::stack<int, std::deque<int>> stack_deque;
    stack_deque.push(1000);
    stack_deque.push(2000);
    print_stack(stack_deque, "stack_deque (底层: deque)");

    // ✅ 性能对比（概念性说明）
    std::cout << "\n底层容器性能对比:" << std::endl;
    std::cout << "  - vector: 内存连续，缓存友好，但扩容可能移动数据" << std::endl;
    std::cout << "  - list: 任意位置插入稳定，但内存不连续，缓存不友好" << std::endl;
    std::cout << "  - deque: 两端操作高效，内存分段连续，最常用" << std::endl;
}

// 示例 3: 自定义类型支持
void example_custom_type()
{
    std::cout << "\n=== 示例 3: 自定义类型 ===" << std::endl;

    std::stack<Task> task_stack;
    task_stack.emplace("编码", 1);
    task_stack.emplace("测试", 2);
    task_stack.emplace("部署", 3);

    std::cout << "任务栈 (size=" << task_stack.size() << "):" << std::endl;
    while (!task_stack.empty()) {
        std::cout << "  执行: " << task_stack.top() << std::endl;
        task_stack.pop();
    }
}

// 示例 4: 实战应用 —— 括号匹配检查
bool is_balanced(const std::string& expr)
{
    std::stack<char> s;
    for (char c : expr) {
        if (c == '(' || c == '[' || c == '{') {
            s.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (s.empty())
                return false;
            char top = s.top();
            s.pop();
            if ((c == ')' && top != '(') || (c == ']' && top != '[') || (c == '}' && top != '{')) {
                return false;
            }
        }
    }
    return s.empty();
}

void example_parentheses()
{
    std::cout << "\n=== 示例 4: 实战应用 —— 括号匹配 ===" << std::endl;

    std::vector<std::string> test_cases = {
        "()", // true
        "()[]{}", // true
        "([{}])", // true
        "([)]", // false
        "(((", // false
        ")))", // false
        "{[()]}", // true
        "{[(])}" // false
    };

    for (const auto& expr : test_cases) {
        bool balanced = is_balanced(expr);
        std::cout << expr << " -> " << (balanced ? "✅ 平衡" : "❌ 不平衡") << std::endl;
    }
}

// 示例 5: 实战应用 —— 表达式求值（简化版，仅支持 + - * / 和整数）
int evaluate_expression(const std::string& expr)
{
    std::stack<int> values;
    std::stack<char> ops;

    for (size_t i = 0; i < expr.length(); ++i) {
        char c = expr[i];
        if (c == ' ')
            continue;

        if (isdigit(c)) {
            // 解析多位数字
            int val = 0;
            while (i < expr.length() && isdigit(expr[i])) {
                val = val * 10 + (expr[i] - '0');
                ++i;
            }
            --i; // 因 for 循环会 ++i
            values.push(val);
        } else if (c == '(') {
            ops.push(c);
        } else if (c == ')') {
            while (!ops.empty() && ops.top() != '(') {
                int val2 = values.top();
                values.pop();
                int val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                switch (op) {
                case '+':
                    values.push(val1 + val2);
                    break;
                case '-':
                    values.push(val1 - val2);
                    break;
                case '*':
                    values.push(val1 * val2);
                    break;
                case '/':
                    values.push(val1 / val2);
                    break;
                }
            }
            ops.pop(); // 弹出 '('
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!ops.empty() && ops.top() != '(' && ((c == '*' || c == '/') && (ops.top() == '*' || ops.top() == '/'))) {
                int val2 = values.top();
                values.pop();
                int val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                switch (op) {
                case '+':
                    values.push(val1 + val2);
                    break;
                case '-':
                    values.push(val1 - val2);
                    break;
                case '*':
                    values.push(val1 * val2);
                    break;
                case '/':
                    values.push(val1 / val2);
                    break;
                }
            }
            ops.push(c);
        }
    }

    while (!ops.empty()) {
        int val2 = values.top();
        values.pop();
        int val1 = values.top();
        values.pop();
        char op = ops.top();
        ops.pop();
        switch (op) {
        case '+':
            values.push(val1 + val2);
            break;
        case '-':
            values.push(val1 - val2);
            break;
        case '*':
            values.push(val1 * val2);
            break;
        case '/':
            values.push(val1 / val2);
            break;
        }
    }

    return values.top();
}

void example_expression()
{
    std::cout << "\n=== 示例 5: 实战应用 —— 表达式求值 ===" << std::endl;

    std::vector<std::string> test_cases = {
        "3 + 4 * 2", // 11
        "(1 + 2) * 3", // 9
        "10 / 2 - 3", // 2
        "2 * (3 + 4) - 5", // 9
        "1 + 2 + 3 * 4" // 15
    };

    for (const auto& expr : test_cases) {
        try {
            int result = evaluate_expression(expr);
            std::cout << expr << " = " << result << std::endl;
        } catch (...) {
            std::cout << expr << " = ❌ 计算错误" << std::endl;
        }
    }
}

// 示例 6: 性能与使用建议
void example_performance()
{
    std::cout << "\n=== 示例 6: 性能与使用建议 ===" << std::endl;

    std::cout << "std::stack 特性总结:" << std::endl;
    std::cout << "  - 底层: 默认 std::deque，可自定义" << std::endl;
    std::cout << "  - 操作: push, pop, top, empty, size" << std::endl;
    std::cout << "  - 时间复杂度: 所有操作 O(1)" << std::endl;
    std::cout << "  - 无迭代器: 不能遍历，需复制或改用底层容器" << std::endl;

    std::cout << "\n何时使用 stack:" << std::endl;
    std::cout << "  - 需要 LIFO 语义（后进先出）" << std::endl;
    std::cout << "  - 算法题：括号匹配、表达式求值、DFS" << std::endl;
    std::cout << "  - 系统设计：撤销操作、函数调用栈" << std::endl;

    std::cout << "\n何时不使用 stack:" << std::endl;
    std::cout << "  - 需要随机访问或遍历 → 用 vector/deque" << std::endl;
    std::cout << "  - 需要前端操作 → 用 deque" << std::endl;
    std::cout << "  - 数据量极大且内存敏感 → 考虑自定义底层容器" << std::endl;

    std::cout << "\n底层容器选择建议:" << std::endl;
    std::cout << "  - 一般情况 → 用默认 deque" << std::endl;
    std::cout << "  - 频繁 push/pop 且数据量稳定 → 用 vector（缓存友好）" << std::endl;
    std::cout << "  - 频繁插入且内存碎片敏感 → 用 list（但缓存不友好）" << std::endl;
}

// 主函数
auto main(int argc, char* argv[]) -> int
{
    example_basic();
    example_containers();
    example_custom_type();
    example_parentheses();
    example_expression();
    example_performance();

    std::cout << "\n✅ std::stack 学习完成！" << std::endl;
    return 0;
}