#include <iostream>
#include "union_find.h"

int main(int, char**) {
    std::cout << "Hello, world!\n";

    auto e = std::make_shared<Element>(5);

    Group g(e);

    UnionFind uf(5);

    Element* p1 = uf.Find(1);
    Element* p2 = uf.Find(3);

    uf.Union(1,3);

    Element* p3 = uf.Find(1);
    Element* p4 = uf.Find(3);
    
    return 0;
}
