#include <iostream>

// #define __MY_ANSWER__
#define __OFFICIAL_ANSWER__

using namespace std;

class ListNode {
public:
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

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
#ifdef __MY_ANSWER__
        auto l3 = add(l1, l2);
        return reverse(l3);
    }
    ListNode* reverse(ListNode* l1) const
    {
#if 0
        ListNode* p = new ListNode(l1->val);
        ListNode* q = l1->next;
        while (q != nullptr) {
            ListNode* r = new ListNode(q->val);
            r->next = p;
            p = r;
            q = q->next;
        }
        return p;
#endif
        ListNode* head = l1;
        ListNode* p = l1->next;
        ListNode* temp = nullptr;
        l1->next = nullptr;
        while (p != nullptr) {
            temp = p->next;
            p->next = head;
            head = p;
            p = temp;
        }
        return head;
    }
    ListNode* add(ListNode* rl1, ListNode* rl2) const
    {
        ListNode* rp1 = rl1;
        ListNode* rp2 = rl2;
        ListNode* head = nullptr;
        int carry = 0;
        int sum = 0;
        while (rp1 != nullptr && rp2 != nullptr) {
            sum = rp1->val + rp2->val + carry;
            ListNode* rp3 = new ListNode(sum % 10);
            carry = sum / 10;
            rp3->next = head;
            head = rp3;
            rp1 = rp1->next;
            rp2 = rp2->next;
        }
        while (rp1 != nullptr) {
            sum = rp1->val + carry;
            ListNode* rp3 = new ListNode(sum % 10);
            carry = sum / 10;
            rp3->next = head;
            head = rp3;
            rp1 = rp1->next;
        }
        while (rp2 != nullptr) {
            sum = rp2->val + carry;
            ListNode* rp3 = new ListNode(sum % 10);
            carry = sum / 10;
            rp3->next = head;
            head = rp3;
            rp2 = rp2->next;
        }
        if (carry != 0) {
            ListNode* rp3 = new ListNode(carry);
            rp3->next = head;
            head = rp3;
        }
        return head;
    }
#endif
#ifdef __OFFICIAL_ANSWER__
    ListNode *head = nullptr, *tail = nullptr;
    int carry = 0;
    while (l1 || l2) {
        int n1 = l1 ? l1->val : 0;
        int n2 = l2 ? l2->val : 0;
        int sum = n1 + n2 + carry;
        if (!head) {
            head = tail = new ListNode(sum % 10);
        } else {
            tail->next = new ListNode(sum % 10);
            tail = tail->next;
        }
        carry = sum / 10;
        if (l1) {
            l1 = l1->next;
        }
        if (l2) {
            l2 = l2->next;
        }
    }
    if (carry > 0) {
        tail->next = new ListNode(carry);
    }
    return head;
}
#endif
}
;

auto main(int argc, char* argv[]) -> int
{
    Solution s;
    auto l1 = new ListNode(2);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(3);
    auto l2 = new ListNode(5);
    l2->next = new ListNode(6);
    l2->next->next = new ListNode(4);
    auto result = s.addTwoNumbers(l1, l2);
    for (auto p = result; p != nullptr; p = p->next)
        cout << p->val;
    cout << endl;

    return 0;
}