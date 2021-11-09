#pragma once
#include <iostream>

using namespace std;

template <typename Key, typename Info>
class Sequence {
    public:

    // Public struct used to return data stored in the list
    struct Item {
        Key key;
        Info info;

        Item(Key k, Info i) : key(k), info(i) {}
    };

    Sequence();

    Sequence(const Sequence& src);

    ~Sequence();

    Sequence& operator=(const Sequence& src);

    int size() const;

    void push_front(const Key& key, const Info& info); // keys are not unique!

    bool pop_front();

    void print() const;

    const Item& get_item(int index) const;

    Item& get_item_by_key(Key key);

    private:

    // Private struct used to store the data
    struct Node {
        Item *item;
        // Key key;
        // Info info;
        Node *next;

        // Node(Key k, Info i, Node *n = nullptr) : key(k), info(i), next(n) {}
        Node(Item *i, Node *n = nullptr) : item(i), next(n) {}
    };

    Node *head = nullptr;
    unsigned int num_nodes = 0;

    void remove_all();

    void copy_all(const Sequence& rhs);

    void push_end(const Key& key, const Info& info);

};

template <typename Key, typename Info>
Sequence<Key, Info> join(const Sequence<Key, Info>& left, const Sequence<Key, Info>& right, Info (*aggregate)(const Info& left, const Info& right));

#include "sequence.tpp"
