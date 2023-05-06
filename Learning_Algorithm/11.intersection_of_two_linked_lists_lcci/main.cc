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

ListNode* get_intersection_node(ListNode* headA, ListNode* headB)
{
    int lengthA {};
    int lengthB {};
    ListNode* p = headA;
    ListNode* heada = nullptr;
    ListNode* headb = nullptr;
    while (p) {
        p = p->next;
        ++lengthA;
    }
    p = headB;
    while (p) {
        p = p->next;
        ++lengthB;
    }
    heada = headA;
    headb = headB;
    if (lengthA < lengthB) {
        for (int i = 0; i < lengthB - lengthA; ++i)
            headb = headb->next;
    } else if (lengthA > lengthB) {
        for (int i = 0; i < lengthA - lengthB; ++i)
            heada = heada->next;
    }
    for (int i = 0; i < (lengthA < lengthB ? lengthA : lengthB); ++i) {
        if (heada == headb)
            return heada;
        else {
            heada = heada->next;
            headb = headb->next;
        }
    }
    return nullptr;
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
    std::vector<int> vi { 1, 2, 3, 4, 5 };
    auto head = create_linklist(vi);
    print_linklist(head);
    destroy_linklist(head);
    return 0;
}