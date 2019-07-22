#include <iostream>

#include "mylist.h"

// Constructors

Mylist::Mylist(int val) {
    head = new Mynode();
    head->val = val;
    head->next = nullptr;
}

// Member functions

Mynode* Mylist::last() {
    if (head == nullptr)
        return nullptr;
    Mynode* nodep = head;
    while (nodep != nullptr) {
        if (nodep->next == nullptr)
            return nodep;
        nodep = nodep->next;
    }
    return nodep;
}

Mylist& Mylist::append(int val) {
    Mynode* newnodep = new Mynode();
    newnodep->val = val;
    Mynode* lastp = last();
    lastp->next = newnodep;
    return *this;
}

void Mylist::print() {
    Mynode* nodep = head;
    while (nodep != nullptr) {
        std::cout << " " << nodep->val;
        nodep = nodep->next;
    }
}
