#include <iostream>
#include <unordered_set>
#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    ListNode()
        : val(0)
        , next(nullptr)
    {
    }
    explicit ListNode(int x)
        : val(x)
        , next(nullptr)
    {
    }
    ListNode(int x, ListNode* next)
        : val(x)
        , next(next)
    {
    }
};

#if 0
ListNode* detect_cycle(ListNode* head)
{
    std::unordered_set<ListNode*> sl {};
    ListNode* p = head;
    while (sl.find(p) == sl.end() && p) {
        sl.insert(p);
        p = p->next;
    }
    return p;
}
#endif

#if 1
// 1、怎么判断有环——快慢指针相遇
// 2、怎么判断相遇时，快指针绕了几圈
ListNode* detect_cycle(ListNode* head)
{
    ListNode* p = head;
    for (int i = 0; i < 10001; ++i) {
        if (p)
            p = p->next;
        else
            return nullptr;
    }
    ListNode* fast = head->next->next;
    ListNode* slow = head->next;
    size_t i = 1;
    while (fast != slow) {
        fast = fast->next->next;
        slow = slow->next;
        ++i;
    }
    fast = head;
    while (fast != slow) {
        fast = fast->next;
        slow = slow->next;
    }
    return fast;
}
#endif

ListNode* create_linklist(std::vector<int>& vi)
{
    if (vi.empty())
        return nullptr;
    else {
        ListNode* head = new ListNode(vi.back());
        for (auto i = vi.crbegin() + 1; i != vi.crend(); ++i) {
            ListNode* p = new ListNode(*i, head);
            head = p;
        }
        return head;
    }
}

void print_linklist(ListNode* head)
{
    auto p = head;
    while (p) {
        std::cout << p->val << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

void destroy_linklist(ListNode* head)
{
    while (head) {
        auto p = head->next;
        delete head;
        head = p;
    }
}

auto main(int argc, char* argv[]) -> int
{
    std::vector<int> vi { 3, 2, 0, 4 };
    auto head = create_linklist(vi);
    print_linklist(head);
    head->next->next->next->next = head->next;
    auto node = detect_cycle(head);
    std::cout << node->val << std::endl;
    head->next->next->next->next = nullptr;
    print_linklist(head);
    destroy_linklist(head);
    return 0;
}