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
    int group;
    std::shared_ptr<Element> parent;
public:
    Element(int data = 0);

    std::shared_ptr<Element> getParent();

    void setParent(std::shared_ptr<Element> new_parent);

    int getGroup();

    void setGroup(int new_group);
    
    ~Element() = default;
};

Element::Element(int data): data(data), group(data), parent() {}

std::shared_ptr<Element> Element::getParent() { return parent; }

void Element::setParent(std::shared_ptr<Element> new_parent) { parent = new_parent; }

int Element::getGroup() { return group; }

void Element::setGroup(int new_group) { group = new_group; }


/* Group class */
class Group {
    std::shared_ptr<Element> root;
    int size;
public:
    Group(std::shared_ptr<Element> root);

    void setSize(int new_size);

    int getSize();

    void setRoot(std::shared_ptr<Element> new_root);

    std::shared_ptr<Element> getRoot();

    ~Group() = default;
};

Group::Group(std::shared_ptr<Element> root): root(root), size(1) {}

void Group::setSize(int new_size) { size = new_size; }

int Group::getSize() { return size; }

void Group::setRoot(std::shared_ptr<Element> new_root) { root = new_root; }

std::shared_ptr<Element> Group::getRoot() { return root; }


/* UnionFind class */
class UnionFind {
    std::vector<std::shared_ptr<Element>> elements;
    std::vector<std::shared_ptr<Group>> groups;
    int n;
public:
    UnionFind(int n);

    std::shared_ptr<Element> Find(int i);

    void Union(int p, int q);

    ~UnionFind() = default;
};

UnionFind::UnionFind(int n): n(n) {
    for (int i = 0; i < n; i++) {
        elements.push_back(std::make_shared<Element>(i));
        groups.push_back(std::make_shared<Group>(elements[i]));
    }
}

std::shared_ptr<Element> UnionFind::Find(int i) {
    if (i < 0 || i > n-1 || !elements[i].get())
        return NULL;
    std::shared_ptr<Element> root = elements[i];
    std::shared_ptr<Element> parent = elements[i]->getParent();
    while (parent) {
        root = parent;
        parent = parent->getParent();
    }
    std::shared_ptr<Element> element_tmp = elements[i];
    std::shared_ptr<Element> parent_tmp = elements[i]->getParent();
    while (parent_tmp) {
        element_tmp->setParent(root);
        element_tmp = parent_tmp;
        parent_tmp = parent_tmp->getParent();
    }

    return root;
}

void UnionFind::Union(int p, int q) {
    if (p < 0 || p > n-1 || q < 0 || q > n-1)
        return;
    std::shared_ptr<Element> p1 = Find(p);
    std::shared_ptr<Element> p2 = Find(q);
    if (groups[p1->getGroup()]->getSize() > groups[p2->getGroup()]->getSize()) {
        p2->setParent(p1);
        groups[p1->getGroup()]->setSize(groups[p1->getGroup()]->getSize() + groups[p2->getGroup()]->getSize());
    }
    else {
        p1->setParent(p2);
        groups[p2->getGroup()]->setSize(groups[p1->getGroup()]->getSize() + groups[p2->getGroup()]->getSize());
    }
}

#endif /* UNION_FIND */
