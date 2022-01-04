#include <iostream>
#include "union_find.h"

int main(int, char**) {
    std::cout << "Hello, world!\n";
    std::shared_ptr<Element> e = (std::shared_ptr<Element>)new Element(5);

    Group g(e);

    UnionFind uf(5);

    //std::shared_ptr<Element> p1 = uf.Find(3);

    //uf.Union(1,3);

    //std::shared_ptr<Element> p2 = uf.Find(3);

    //delete e;

    return 0;
}
