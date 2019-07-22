#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

#include "mylist.h"

using namespace std;

typedef vector<int> Intv;
typedef set<int> IntSet;

bool has_dups(Intv v1)
{
    IntSet found_ints;
    
    for (auto &val : v1) {
        if (found_ints.find(val) != found_ints.end())
            return true;
        found_ints.insert(val);
        cout << "added: " << val << endl;
    }
    return false;
}

int main(const int argc, const char* argv[])
{
    int result = 0;

    Intv v1 {6, 2, -3, 22, 2, 7};

    cout << "v1 auto iterator ";
    for (auto iter = v1.begin(); iter != v1.end(); ++iter) {
        cout << " " << *iter;
    }
    cout << endl;

    cout << "v1 range for loop: ";
    for (auto &val : v1) {
        cout << " " << val;
    }
    cout << endl;

    bool dupsp = has_dups(v1);
    cout << "v1 has dups: " << dupsp << endl;

    Mylist list1(2);
    Mynode* nodep = list1.head;
    cout << "list1 " << nodep->val << " " << nodep->next << endl;

    list1.append(3);
    list1.append(4);

    while (nodep != nullptr) {
        std::cout << "node val " << nodep->val << " next " << nodep->next << endl;
        nodep = nodep->next;
    }
    cout << "Print: ";
    list1.print();
    cout << endl;

    return result;
}
