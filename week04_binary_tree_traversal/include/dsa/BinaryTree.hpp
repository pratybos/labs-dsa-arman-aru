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

        // Find a node by value anywhere in the subtree. Returns nullptr if not found.
        Node* find_rec(Node* n, const T& value) const {
            if (n == nullptr) return nullptr;
            if (n->value == value) return n;
            Node* leftRes = find_rec(n->left, value);
            if (leftRes != nullptr) return leftRes;
            return find_rec(n->right, value);
        }

        // Traversals: write into out[idx] and bump idx.
        void preorder_rec(Node* n, T* out, std::size_t& idx) const {
            if (n == nullptr) return;
            out[idx++] = n->value;       // visit
            preorder_rec(n->left, out, idx);
            preorder_rec(n->right, out, idx);
        }
        void inorder_rec(Node* n, T* out, std::size_t& idx) const {
            if (n == nullptr) return;
            inorder_rec(n->left, out, idx);
            out[idx++] = n->value;
            inorder_rec(n->right, out, idx);
        }
        void postorder_rec(Node* n, T* out, std::size_t& idx) const {
            if (n == nullptr) return;
            postorder_rec(n->left, out, idx);
            postorder_rec(n->right, out, idx);
            out[idx++] = n->value;
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

        // set_root — create the very first node. Error if root already exists.
        void set_root(const T& value) {
            if (root_ != nullptr) {
                throw std::logic_error("BinaryTree::set_root - root already exists");
            }
            root_ = new Node(value);
            size_ = 1;
        }

        // add_left(parent, child) — attach a new left child under the parent.
        // Throws std::out_of_range if parent not found.
        // Throws std::logic_error if the parent already has a left child.
        void add_left(const T& parentValue, const T& childValue) {
            Node* p = find_rec(root_, parentValue);
            if (p == nullptr) {
                throw std::out_of_range("BinaryTree::add_left - parent not found");
            }
            if (p->left != nullptr) {
                throw std::logic_error("BinaryTree::add_left - left child exists");
            }
            p->left = new Node(childValue);
            size_ = size_ + 1;
        }

        void add_right(const T& parentValue, const T& childValue) {
            Node* p = find_rec(root_, parentValue);
            if (p == nullptr) {
                throw std::out_of_range("BinaryTree::add_right - parent not found");
            }
            if (p->right != nullptr) {
                throw std::logic_error("BinaryTree::add_right - right child exists");
            }
            p->right = new Node(childValue);
            size_ = size_ + 1;
        }

        // Traversals: write into out (caller must give an array of at least size()).
        void preorder(T* out) const {
            std::size_t idx = 0;
            preorder_rec(root_, out, idx);
        }
        void inorder(T* out) const {
            std::size_t idx = 0;
            inorder_rec(root_, out, idx);
        }
        void postorder(T* out) const {
            std::size_t idx = 0;
            postorder_rec(root_, out, idx);
        }
    };

} // namespace dsa
