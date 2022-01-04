#include <iostream>
#include "union_find.h"

int main(int, char**) {
    std::cout << "Hello, world!\n";

    UnionFind uf(5);

    uf.Union(5,2);
    uf.Union(0,1);
    uf.Union(2,3);
    uf.Union(1,2);

    uf.Find(0);
    
    return 0;
}
