#include <cstddef>
#include <iostream>

class Node {
public:
    Node() = default;
    explicit Node(int val)
        : val(val)
    {
    }
    Node(int val, Node* next)
        : val(val)
        , next(next)
    {
    }
    ~Node() = default;

    int val {};
    Node* next { nullptr };
};

class MyLinkedList {
public:
    MyLinkedList() = default;
    ~MyLinkedList() // 重大设计失误，LinkList的析构函数和Node的析构函数是不一样的
    {
        Node* p = this->next;
        while (p) {
            this->next = p->next;
            delete p;
            p = this->next;
        }
    }

    int get(int index)
    {
        int i = -1;
        Node* p = this->next;
        while (p) {
            ++i;
            if (i == index)
                return p->val;
            p = p->next;
        }
        return -1;
    }

    int length()
    {
        int i = 0;
        Node* p = this->next;
        while (p) {
            p = p->next;
            ++i;
        }
        return i;
    }

    void print()
    {
        Node* p = this->next;
        while (p) {
            std::cout << p->val << " ";
            p = p->next;
        }
        std::cout << std::endl;
    }

    void addAtHead(int val)
    {
        Node* p = new Node(val, this->next);
        this->next = p;
    }

    void addAtTail(int val)
    {
        Node* q = new Node(val);
        if (!this->next) {
            this->next = q;
        } else {
            Node* p = this->next;
            while (p->next) {
                p = p->next;
            }
            p->next = q;
        }
    }

    void addAtIndex(int index, int val)
    {
        if (length() == index)
            return addAtTail(val);
        if (get(index) == -1)
            return;
        if (0 == index) {
            return addAtHead(val);
        } else {
            int i = 0;
            Node* p = this->next;
            while (p) {
                if (i == index - 1) {
                    Node* q = new Node(val, p->next);
                    p->next = q;
                    return;
                } else {
                    p = p->next;
                    ++i;
                }
            }
        }
    }

    void deleteAtIndex(int index)
    {
        if (get(index) == -1)
            return;
        if (0 == index) {
            Node* p = this->next;
            this->next = this->next->next;
            delete p;
        } else {
            int i = 0;
            Node* p = this->next;
            while (p) {
                if (i == index - 1) {
                    Node* temp = p->next;
                    p->next = p->next->next;
                    delete temp;
                    return;
                } else {
                    p = p->next;
                    ++i;
                }
            }
        }
    }

private:
    Node* next { nullptr };
};

auto main(int argc, char* argv[]) -> int
{
    MyLinkedList* list = new MyLinkedList();
    list->addAtHead(1);
    list->addAtHead(2);
    list->addAtHead(3);
    list->print();
    std::cout << list->get(1) << std::endl;
    std::cout << list->get(5) << std::endl;
    list->addAtTail(100);
    list->print();
    list->deleteAtIndex(3);
    list->print();
    list->addAtIndex(5, 100);
    list->print();
    list->addAtIndex(0, 100);
    list->print();
    list->addAtIndex(3, 100);
    list->print();
    list->addAtIndex(5, 1000);
    list->print();
    delete list;
    return 0;
}