#pragma once
#include "sequence.h"

template <typename Key, typename Info>
Sequence<Key, Info>::Sequence() {
    // cout << "Sequence created \n";
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
int Sequence<Key, Info>::size() const {
    return num_nodes;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::push_front(const Key& key, const Info& info) {
    Item *item = new Item(key, info);
    Node *node = new Node(item, head);
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
void Sequence<Key, Info>::print() const {
    Node *current = head;

    if (head == nullptr) {
        cout << "Empty sequence" << endl;
    }

    int index = 1;
    while(current != nullptr) {
        cout << index << ". " << current->item->key << " : " << current->item->info << endl;
        current = current->next;
        index += 1;
    }

    cout << endl;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::remove_all() {
    Node *n = head;
    while (n) {
        n = n->next;
        delete head->item;
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
        push_end(rhs_current->item->key, rhs_current->item->info);
        rhs_current = rhs_current->next;
    }
}

template <typename Key, typename Info>
void Sequence<Key, Info>::push_end(const Key& key, const Info& info) {
    Item *item = new Item(key, info);
    Node *node = new Node(item);
    
    if (!node) {
        cerr << "Memory allocation error" << endl;
        return;
    }

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

template <typename Key, typename Info>
const typename Sequence<Key, Info>::Item& Sequence<Key, Info>::get_item(int index) const {
    // Is it possible to return constant reference with mutable properties??
    // Counting in this function starts from 1 (index 1 == first element)
    if (index < 1 || index > this->size()) {
        throw std::out_of_range("Index out of range");
    }
    Node *current_node = head;
    int current_index = 1;
    while (current_index < index) {
        current_node = current_node->next;
        current_index += 1;
    }
    return *(current_node->item);
}

template <typename Key, typename Info>
typename Sequence<Key, Info>::Item& Sequence<Key, Info>::get_item_by_key(Key key) {
    // returns reference to first found occurence of given key
    // if key not found, adds it and returns reference
    Node *current = head;
    while (current) {
        if (current->item->key == key) return *(current->item);
        current = current->next;
    }
    
    push_end(key, *(new Info));
    return get_item_by_key(key);
}

template <typename Key, typename Info>
Sequence<Key, Info> join(const Sequence<Key, Info>& left, const Sequence<Key, Info>& right, Info (*aggregate)(const Info& left, const Info& right)) {
    if (left.size() < 1 && right.size() < 1) return left; // Both are empty se we can return either of them
    if (left.size() < 1 && right.size() > 0) return right;
    if (right.size() < 1 && left.size() > 0) return left;

    Sequence<Key, Info> output;

    for (int l_index = 1; l_index <= left.size(); l_index++) {
        try {
                Key k = left.get_item(l_index).key;
                output.get_item_by_key(k).info = aggregate(output.get_item_by_key(k).info, left.get_item(l_index).info);
        } catch(std::out_of_range const & err) {
            continue;
        }
    }

    for (int r_index = 1; r_index <= right.size(); r_index++) {
        try {
            Key k = right.get_item(r_index).key;
            output.get_item_by_key(k).info = aggregate(output.get_item_by_key(k).info, right.get_item(r_index).info);
        } catch(std::out_of_range const & err) {
            continue;
        }
    }

    return output;
}
