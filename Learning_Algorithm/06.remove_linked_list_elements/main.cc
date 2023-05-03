#include <algorithm>
#include <iostream>
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

// 构造一个头节点
ListNode* remove_elements(ListNode* head, int val)
{
    ListNode* dummy_head = new ListNode(0, head);
    ListNode* p = dummy_head;
    while (p->next) {
        if (p->next->val == val) {
            auto temp = p->next;
            p->next = temp->next;
            delete temp;
        } else
            p = p->next;
    }
    p = dummy_head->next;
    delete dummy_head;
    return p;
}

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
    std::vector<int> vi { 1, 2, 6, 3, 4, 5, 6 };
    auto head = create_linklist(vi);
    print_linklist(head);
    head = remove_elements(head, 6);
    print_linklist(head);
    destroy_linklist(head);
    return 0;
}