#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

typedef vector<int> Intv;
typedef set<int> IntSet;

bool hasDups(Intv v1)
{
    bool rcode = false;
    IntSet foundInts;

    for (int &val : v1)
    {
        if (foundInts.find(val) != foundInts.end())
            return true;
        foundInts.insert(val); 
    }
    return rcode;
}

int main(const int argc, const char* argv[])
{
    int result = 0;
    Intv v1 {6, 2, 22, 3, 2, 7};

    cout << "v1 iterator ";
    for (Intv::iterator iter = v1.begin(); iter != v1.end(); ++iter)
    {
        cout << " " << *iter;
    }
    cout << std::endl;

    cout << "v1 auto ";
    for (auto iter = v1.begin(); iter != v1.end(); ++iter)
    {
        cout << " " << *iter;
    }
    cout << std::endl;

    cout << "v1 ranged_for_loop ";
    for (int &val : v1)
    {
        cout << " " << val;
    }
    cout << std::endl;

    bool has_dups = hasDups(v1);
    cout << "v1 has dups: " << has_dups << std::endl;

    return result;
}
