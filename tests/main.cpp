#include "../union_find.h"
#include <iostream>
#include "cassert"
using namespace std;


int main() {
    UnionFind<int> uf(8);
    assert(uf.Find(1).get()->getGroup()==1);
    uf.Union(2,1);
    assert(uf.Find(1).get()->getGroup()==2);
    uf.Union(4,3);
    uf.Union(4,2);
    assert(uf.Find(1).get()->getGroup()==4);

    cout << "PASS" << endl;
}