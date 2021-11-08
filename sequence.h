#pragma once
#include <iostream>

using namespace std;

template <typename Key, typename Info>
class Sequence {
    public:

    Sequence();

    Sequence(const Sequence& src);

    ~Sequence();

    Sequence& operator=(const Sequence& src);

    unsigned int size() const;

    void push_front(const Key& key, const Info& info); // keys are not unique!

    bool pop_front();

    void print();

    private:

    struct Node {
        Key key;
        Info info;
        Node *next;
    };

    Node *head = nullptr;
    unsigned int num_nodes = 0;

    void remove_all();

    void copy_all(const Sequence& rhs);

    void push_end(const Key& key, const Info& info);

};

#include "sequence.tpp"
