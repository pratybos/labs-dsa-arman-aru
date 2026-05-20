// BinaryTree<T> — Week 04
// -----------------------
// Skeleton step: I lay down the basics first (private Node struct,
// constructor, destructor, clear). Methods like set_root/traversals
// will be added in the next commits.

#pragma once
#include <cstddef>
#include <stdexcept>

namespace dsa {

    template <class T>
    class BinaryTree {
    private:
        // Each tree node holds a value and two child pointers.
        struct Node {
            T value;
            Node* left;
            Node* right;
            Node(const T& v) : value(v), left(nullptr), right(nullptr) {}
        };

        Node* root_;
        std::size_t size_;

        // Recursively delete a subtree (post-order so children go first).
        void clear_rec(Node* n) {
            if (n == nullptr) return;
            clear_rec(n->left);
            clear_rec(n->right);
            delete n;
        }

    public:
        BinaryTree() : root_(nullptr), size_(0) {}
        ~BinaryTree() { clear(); }

        std::size_t size() const { return size_; }
        bool empty() const { return root_ == nullptr; }

        void clear() {
            clear_rec(root_);
            root_ = nullptr;
            size_ = 0;
        }
    };

} // namespace dsa
