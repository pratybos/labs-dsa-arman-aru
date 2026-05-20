// BST<T>  — Binary Search Tree
// ----------------------------
// Skeleton step: Node struct + ctor + dtor + clear.
// I will add insert/contains/min/max/height/inorder/remove
// in the next commits.

#pragma once
#include <cstddef>
#include <stdexcept>

namespace dsa {

    template <class T>
    class BST {
    private:
        struct Node {
            T key;
            Node* left;
            Node* right;
            Node(const T& k) : key(k), left(nullptr), right(nullptr) {}
        };

        Node* root_;
        std::size_t size_;

        // Recursively delete every node in the subtree.
        void clear_rec(Node* n) {
            if (n == nullptr) return;
            clear_rec(n->left);
            clear_rec(n->right);
            delete n;
        }

        // Insert key into the subtree. Duplicates are ignored.
        Node* insert_rec(Node* n, const T& key) {
            if (n == nullptr) {
                size_ = size_ + 1;
                return new Node(key);
            }
            if (key < n->key) {
                n->left = insert_rec(n->left, key);
            } else if (n->key < key) {
                n->right = insert_rec(n->right, key);
            }
            return n;
        }

    public:
        BST() : root_(nullptr), size_(0) {}
        ~BST() { clear_rec(root_); }

        std::size_t size() const { return size_; }
        bool empty() const { return root_ == nullptr; }

        void insert(const T& key) {
            root_ = insert_rec(root_, key);
        }
    };

} // namespace dsa
