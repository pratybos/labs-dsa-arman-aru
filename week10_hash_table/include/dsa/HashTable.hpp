// HashTable.hpp — Hash Table with Separate Chaining
// -------------------------------------------------
// Keys = int, Values = int.
// Hash function (required by the lab):
//   index = key % capacity
// Negative keys: I make them non-negative first so the modulo result
// is always in [0..capacity-1].
//
// Collisions are handled by SEPARATE CHAINING:
//   buckets_[i] is a list of (key, value) pairs.
//   To find key K, I jump to bucket = hash(K) and then walk that list.

#pragma once
#include <cstddef>

namespace dsa {

    class HashTable {
    private:
        // A single chain node. I write a simple linked list here by hand
        // because I need a (key, value) pair and the SinglyLinkedList<T>
        // template would force me to define operator== for the pair.
        struct Node {
            int key;
            int value;
            Node* next;
            Node(int k, int v) : key(k), value(v), next(nullptr) {}
        };

        Node** buckets_;       // array of `capacity_` head pointers
        int capacity_;
        int size_;             // number of (key,value) pairs stored

        // Turn any int (even negative) into a valid bucket index.
        int hash(int key) const {
            int h = key % capacity_;
            if (h < 0) h += capacity_;
            return h;
        }

    public:
        HashTable(int capacity)
            : buckets_(nullptr), capacity_(capacity), size_(0) {
            if (capacity_ < 1) capacity_ = 1;
            buckets_ = new Node*[capacity_];
            for (int i = 0; i < capacity_; ++i) buckets_[i] = nullptr;
        }

        ~HashTable() {
            // For every bucket, delete the whole chain.
            for (int i = 0; i < capacity_; ++i) {
                Node* cur = buckets_[i];
                while (cur != nullptr) {
                    Node* nxt = cur->next;
                    delete cur;
                    cur = nxt;
                }
            }
            delete[] buckets_;
        }

        // put — insert if new key, update if exists.
        // Returns true if a NEW key was inserted, false if an existing one was updated.
        bool put(int key, int value) {
            int idx = hash(key);
            // Walk the chain and look for the key.
            Node* cur = buckets_[idx];
            while (cur != nullptr) {
                if (cur->key == key) {
                    cur->value = value;
                    return false;
                }
                cur = cur->next;
            }
            // Not found -> insert a new node at the FRONT of the chain (cheap).
            Node* n = new Node(key, value);
            n->next = buckets_[idx];
            buckets_[idx] = n;
            size_ = size_ + 1;
            return true;
        }

        bool contains(int key) const {
            int idx = hash(key);
            Node* cur = buckets_[idx];
            while (cur != nullptr) {
                if (cur->key == key) return true;
                cur = cur->next;
            }
            return false;
        }

        // get — returns POINTER to value if found, nullptr otherwise.
        // I return a pointer (not a reference) so I can safely return "not found".
        int* get(int key) {
            int idx = hash(key);
            Node* cur = buckets_[idx];
            while (cur != nullptr) {
                if (cur->key == key) return &cur->value;
                cur = cur->next;
            }
            return nullptr;
        }

        // remove — returns true if removed, false if not found.
        // I need a prev pointer to re-link the chain when I delete a middle/tail.
        bool remove(int key) {
            int idx = hash(key);
            Node* prev = nullptr;
            Node* cur = buckets_[idx];
            while (cur != nullptr) {
                if (cur->key == key) {
                    if (prev == nullptr) buckets_[idx] = cur->next;
                    else                 prev->next   = cur->next;
                    delete cur;
                    size_ = size_ - 1;
                    return true;
                }
                prev = cur;
                cur = cur->next;
            }
            return false;
        }

        int size() const { return size_; }
        int bucket_count() const { return capacity_; }
    };

} // namespace dsa
