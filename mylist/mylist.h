#ifndef MYLIST_H
#define MYLIST_H

#include "mynode.h"

class Mylist
{
public:
    // Constructors
    Mylist() = default;
    Mylist(int val);

    // Member functions
    Mynode* last();
    Mylist& append(int val);
    Mynode *find(int val);
    void print();

    // Member variables
    Mynode* head = nullptr;
};


#endif
