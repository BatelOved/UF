#ifndef UNION_FIND
#define UNION_FIND

/**
 * @file   union_find.h
 * @author Batel Oved
 * @date   Jan-2021
*/

#include <vector>
#include <memory>

class Group;
class Element;

/* Element class */
// TODO: change data type to std::shared_ptr<T>.
class Element {
    int data;
    std::shared_ptr<Element> parent;
    std::shared_ptr<Group> group;
public:
    Element(int data);
    std::shared_ptr<Element> getParent();
    void setParent(std::shared_ptr<Element> new_parent);
    std::shared_ptr<Group> getGroup();
    void setGroup(std::shared_ptr<Group> new_group);
};

Element::Element(int data): data(data), parent(nullptr), group(nullptr) {}

std::shared_ptr<Element> Element::getParent() { return parent; }

void Element::setParent(std::shared_ptr<Element> new_parent) { parent = new_parent; }

std::shared_ptr<Group> Element::getGroup() { return group; }

void Element::setGroup(std::shared_ptr<Group> new_group) { group = new_group; }

/* Group class */
class Group {
    std::shared_ptr<Element> root;
    int size;
public:
    Group(std::shared_ptr<Element> root);
    void updateSize(int new_size);
    int getSize();
};

Group::Group(std::shared_ptr<Element> root): root(std::shared_ptr<Element>(root)), size(1) {}

void Group::updateSize(int new_size) { size = new_size; }

int Group::getSize() { return size; }

/* UnionFind class */
class UnionFind {
    std::vector<std::shared_ptr<Element>> elements;
    std::vector<std::shared_ptr<Group>> groups;
    int n;
public:
    UnionFind(int n);
    ~UnionFind();
    Element* Find(int i);
    void Union(int p, int q);
};

UnionFind::UnionFind(int n): n(n) {
    for (int i = 0; i < n; i++) {
        std::shared_ptr<Element> new_element = std::make_shared<Element>(i);
        elements.push_back(new_element);
        groups.push_back(std::make_shared<Group>(new_element));
        elements[i]->setGroup(groups[i]);
    }
}

UnionFind::~UnionFind() {}

Element* UnionFind::Find(int i) {
    if (i < 0 || i > n || !elements[i].get())
        return NULL;
    Element* element = elements[i].get();
    Element* parent = elements[i].get()->getParent().get();
    while (parent) {
        element = parent;
        parent = parent->getParent().get();
    }
    return element;
}

void UnionFind::Union(int p, int q) {
    if (p < 0 || p > n || q < 0 || q > n)
        return;
    Element* p1 = Find(p);
    Element* p2 = Find(q);
    if (p1->getGroup()->getSize() > p2->getGroup()->getSize()) {
        p2->setParent(std::shared_ptr<Element>(p1));
        p2->getGroup()->updateSize(p1->getGroup()->getSize() + p2->getGroup()->getSize());
    }
    else {
        p1->setParent(std::shared_ptr<Element>(p2));
        p1->getGroup()->updateSize(p1->getGroup()->getSize() + p2->getGroup()->getSize());
    }
}



#endif /* UNION_FIND */
