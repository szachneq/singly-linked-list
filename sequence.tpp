#pragma once
#include "sequence.h"

template <typename Key, typename Info>
Sequence<Key, Info>::Sequence() {
    cout << "Sequence created \n";
}

template <typename Key, typename Info>
Sequence<Key, Info>::Sequence(const Sequence& src) {
    copy_all(src);
}

template <typename Key, typename Info>
Sequence<Key, Info>::~Sequence() {
    remove_all();
}

template <typename Key, typename Info>
Sequence<Key, Info>& Sequence<Key, Info>::operator=(const Sequence& src) {
    if (this == &src) return *this;
    remove_all();
    copy_all(src);
    return *this;
}

template <typename Key, typename Info>
unsigned int Sequence<Key, Info>::size() const {
    return num_nodes;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::push_front(const Key& key, const Info& info) {
    Node *node = new Node;
    node->key = key;
    node->info = info;
    node->next = head;
    head = node;
    num_nodes += 1;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::pop_front() {
    if (head == nullptr) return false;
    Node *next = head->next;
    delete head;
    head = next;
    num_nodes -= 1;
    return true;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::print() {
    Node *current = head;

    if (head == nullptr) {
        cout << "Empty sequence" << endl;
    }

    while(current != nullptr) {
        cout << " - " << current->key << " : " << current->info << endl;
        current = current->next;
    }

    cout << endl;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::remove_all() {
    Node *n = head;
    while (n) {
        n = n->next;
        delete head;
        head = n;
    }
    head = nullptr;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::copy_all(const Sequence& rhs) {
    if (head != nullptr) return;

    Node *rhs_current = rhs.head;

    while (rhs_current) {
        push_end(rhs_current->key, rhs_current->info);
        rhs_current = rhs_current->next;
    }
}

template <typename Key, typename Info>
void Sequence<Key, Info>::push_end(const Key& key, const Info& info) {
    Node *node = new Node;
    
    if (!node) {
        cerr << "Memory allocation error" << endl;
        return;
    }
    
    node->key = key;
    node->info = info;
    node->next = nullptr;

    if (!head) {
        head = node;
        num_nodes += 1;
        return;
    } 

    Node *current = head;
    while (current->next) {
        current = current->next;
    }

    current->next = node;
    num_nodes += 1;
}
