// BinaryTree<T>
// -------------
// IMPORTANT: this is NOT a Binary Search Tree.
// There is no ordering rule. I build the tree MANUALLY by saying
// "add this child under this parent". Values are assumed unique.
//
// Operations I implement:
//   set_root, add_left, add_right          (manual build)
//   preorder, inorder, postorder           (recursion, write to T* out)
//   height, contains                       (recursion)
//   clear, ~BinaryTree                     (delete all nodes)

#pragma once
#include <cstddef>
#include <stdexcept>

namespace dsa {

    template <class T>
    class BinaryTree {
    private:
        struct Node {
            T value;
            Node* left;
            Node* right;
            Node(const T& v) : value(v), left(nullptr), right(nullptr) {}
        };

        Node* root_;
        std::size_t size_;

        // -------- private recursive helpers --------

        // Delete every node in the subtree rooted at n.
        // Post-order (children first, then n) so we never delete a parent
        // while it still owns living children.
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

        // Height: empty subtree = 0, leaf = 1, otherwise 1 + max(left,right).
        std::size_t height_rec(Node* n) const {
            if (n == nullptr) return 0;
            std::size_t hL = height_rec(n->left);
            std::size_t hR = height_rec(n->right);
            return 1 + (hL > hR ? hL : hR);
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

        std::size_t height() const {
            return height_rec(root_);
        }

        bool contains(const T& value) const {
            return find_rec(root_, value) != nullptr;
        }
    };

} // namespace dsa
