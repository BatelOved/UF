#ifndef UNION_FIND
#define UNION_FIND

/**
 * @file   union_find.h
 * @author Batel Oved
 * @date   Jan-2021
*/

#include <memory>

/* Group class */
template <typename T>
class Group {
    std::shared_ptr<T> data;
    int parent;
    int size;
public:
    Group(): data(std::make_shared<T>()), parent(-1), size(1) {}

    void setData(std::shared_ptr<T> new_data) { data = new_data; }

    void setParent(int new_parent) { parent = new_parent; }

    int getParent() const { return parent; }

    void setSize(int new_size) { size = new_size; }

    int getSize() const { return size; }
};


/* UnionFind class */
template <typename T>
class UnionFind {
    std::shared_ptr<Group<T>>* groups;
    int numOfGroups;
public:
    UnionFind(int numOfGroups);

    void Union(int p, int q);

    int Find(int i);

    ~UnionFind();

    const int NO_PARENT = -1;

    const int FAILURE   = -1;
};

template <typename T>
UnionFind<T>::UnionFind(int numOfGroups): groups(new std::shared_ptr<Group<T>>[numOfGroups]), numOfGroups(numOfGroups) {
    for (int i = 0; i < numOfGroups; i++) {
        groups[i] = std::make_shared<Group<T>>();
    }
}

template <typename T>
void UnionFind<T>::Union(int p, int q) {
    if (p < 0 || p > numOfGroups-1 || q < 0 || q > numOfGroups-1)
        return;
    int p_group = Find(p);
    int g_group = Find(q);
    if (p_group == g_group)
        return;
    if (groups[p_group]->getSize() < groups[g_group]->getSize()) {
        groups[g_group]->setSize(groups[p_group]->getSize() + groups[g_group]->getSize());
        groups[g_group]->setParent(-1);
        groups[p_group]->setParent(g_group);
    }
    else {
        groups[p_group]->setSize(groups[p_group]->getSize() + groups[g_group]->getSize());
        groups[p_group]->setParent(-1);
        groups[g_group]->setParent(p_group);
    }
}

template <typename T>
int UnionFind<T>::Find(int i) {
    if (i < 0 || i > numOfGroups-1)
        return FAILURE;
    int group = i;
    int group_parent = groups[i]->getParent();
    while (group_parent != -1) {
        group = group_parent;
        group_parent = groups[group_parent]->getParent();
    }
    group_parent = groups[i]->getParent();
    while (group_parent != -1) {
        groups[i]->setParent(group);
        i = group_parent;
        group_parent = groups[group_parent]->getParent();
    }
    return group;
}

template <typename T>
UnionFind<T>::~UnionFind() {
    delete[] groups;
}


#endif /* UNION_FIND */
