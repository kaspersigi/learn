#include <iostream>

struct ListNode {
    int val;
    ListNode* next;
    ListNode()
        : val(0)
        , next(nullptr)
    {
    }
    ListNode(int x)
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

ListNode* reverse_list(ListNode* head)
{
}

auto main(int argc, char* argv[]) -> int
{
    std::cout << "Hello World!" << std::endl;
    return 0;
}