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

        bool contains_rec(Node* n, const T& key) const {
            if (n == nullptr) return false;
            if (key < n->key) return contains_rec(n->left, key);
            if (n->key < key) return contains_rec(n->right, key);
            return true; // equal
        }

        // Smallest key in the subtree = leftmost node.
        Node* min_node(Node* n) const {
            while (n->left != nullptr) n = n->left;
            return n;
        }

        Node* max_node(Node* n) const {
            while (n->right != nullptr) n = n->right;
            return n;
        }

        std::size_t height_rec(Node* n) const {
            if (n == nullptr) return 0;
            std::size_t hL = height_rec(n->left);
            std::size_t hR = height_rec(n->right);
            return 1 + (hL > hR ? hL : hR);
        }

    public:
        BST() : root_(nullptr), size_(0) {}
        ~BST() { clear_rec(root_); }

        std::size_t size() const { return size_; }
        bool empty() const { return root_ == nullptr; }

        void insert(const T& key) {
            root_ = insert_rec(root_, key);
        }

        bool contains(const T& key) const {
            return contains_rec(root_, key);
        }

        const T& min() const {
            if (root_ == nullptr) {
                throw std::out_of_range("BST::min - empty");
            }
            return min_node(root_)->key;
        }

        const T& max() const {
            if (root_ == nullptr) {
                throw std::out_of_range("BST::max - empty");
            }
            return max_node(root_)->key;
        }

        std::size_t height() const {
            return height_rec(root_);
        }
    };

} // namespace dsa
