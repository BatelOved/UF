#ifndef UNION_FIND
#define UNION_FIND

/**
 * @file   union_find.h
 * @author Batel Oved
 * @date   Jan-2021
*/

#include <vector>
#include <memory>

template <typename T>
class Element;
template <typename T>
class Group;

/* Element class */
template <typename T>
class Element {
    int group;
    std::shared_ptr<T> data;
    std::shared_ptr<Element> parent;
public:
    Element(int group = 0, std::shared_ptr<T> data = nullptr);

    std::shared_ptr<Element> getParent() const;

    void setParent(std::shared_ptr<Element> new_parent);

    int getGroup();

    void setGroup(int new_group);
};

template <typename T>
Element<T>::Element(int group, std::shared_ptr<T> data): group(group), data(data), parent(nullptr) {}

template <typename T>
std::shared_ptr<Element<T>> Element<T>::getParent() const { return parent; }

template <typename T>
void Element<T>::setParent(std::shared_ptr<Element<T>> new_parent) { parent = new_parent; }

template <typename T>
int Element<T>::getGroup() {
    if (!parent)
        return group;
    std::shared_ptr<Element<T>> p = getParent();
    while (p)
        p = p.get()->getParent();
    group = p.get()->getGroup();
    return group; 
}

template <typename T>
void Element<T>::setGroup(int new_group) { group = new_group; }


/* Group class */
template <typename T>
class Group {
    std::shared_ptr<Element<T>> root;
    int size;
public:
    Group(std::shared_ptr<Element<T>> root);

    void setSize(int new_size);

    int getSize() const;

    void setRoot(std::shared_ptr<Element<T>> new_root);

    std::shared_ptr<Element<T>> getRoot();
};

template <typename T>
Group<T>::Group(std::shared_ptr<Element<T>> root): root(root), size(1) {}

template <typename T>
void Group<T>::setSize(int new_size) { size = new_size; }

template <typename T>
int Group<T>::getSize() const { return size; }

template <typename T>
void Group<T>::setRoot(std::shared_ptr<Element<T>> new_root) { root = new_root; }

template <typename T>

std::shared_ptr<Element<T>> Group<T>::getRoot() { return root; }


/* UnionFind class */
template <typename T>
class UnionFind {
    std::vector<std::shared_ptr<Element<T>>> elements;
    std::vector<std::shared_ptr<Group<T>>> groups;
    int n;
public:
    UnionFind(int n = 0);

    void makeSet(std::shared_ptr<Element<T>> element);

    std::shared_ptr<Element<T>> Find(int i);

    void Union(int p, int q);
};

template <typename T>
UnionFind<T>::UnionFind(int n): n(n) {
    for (int i = 0; i < n; i++) {
        elements.push_back(std::make_shared<Element<T>>(i));
        groups.push_back(std::make_shared<Group<T>>(elements[i]));
    }
}

template <typename T>
void UnionFind<T>::makeSet(std::shared_ptr<Element<T>> element) {
    elements.push_back(std::make_shared<Element<T>>(element));
    groups.push_back(std::make_shared<Group<T>>(element));
    ++n;
}

template <typename T>
std::shared_ptr<Element<T>> UnionFind<T>::Find(int i) {
    if (i < 0 || i > n-1 || !elements[i].get())
        return nullptr;
    std::shared_ptr<Element<T>> root = elements[i];
    std::shared_ptr<Element<T>> parent = elements[i]->getParent();
    while (parent) {
        root = parent;
        parent = parent->getParent();
    }
    std::shared_ptr<Element<T>> element_tmp = elements[i];
    std::shared_ptr<Element<T>> parent_tmp = elements[i]->getParent();
    while (parent_tmp) {
        element_tmp->setParent(root);
        element_tmp = parent_tmp;
        parent_tmp = parent_tmp->getParent();
    }

    return root;
}

template <typename T>
void UnionFind<T>::Union(int p, int q) {
    if (p < 0 || p > n-1 || q < 0 || q > n-1 || p == q)
        return;
    std::shared_ptr<Element<T>> p1 = Find(p);
    std::shared_ptr<Element<T>> p2 = Find(q);
    if (p1 == p2)
        return;
    if (groups[p1->getGroup()]->getSize() < groups[p2->getGroup()]->getSize()) {
        groups[p2->getGroup()]->setSize(groups[p1->getGroup()]->getSize() + groups[p2->getGroup()]->getSize());
        groups[p1->getGroup()]->setRoot(nullptr);
        p1->setParent(p2);
    }
    else {
        groups[p1->getGroup()]->setSize(groups[p1->getGroup()]->getSize() + groups[p2->getGroup()]->getSize());
        groups[p2->getGroup()]->setRoot(nullptr);
        p2->setParent(p1);
    }
}

#endif /* UNION_FIND */
