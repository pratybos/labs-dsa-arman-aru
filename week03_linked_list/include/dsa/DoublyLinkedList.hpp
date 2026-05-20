// DoublyLinkedList<T>  (bonus task)
// ---------------------------------
// Like SinglyLinkedList, but every node also has a "prev" pointer.
// That lets me walk backwards and do pop_back in O(1).

#pragma once
#include <cstddef>
#include <stdexcept>

namespace dsa {

    template <class T>
    class DoublyLinkedList {
    private:
        struct Node {
            T value;
            Node* prev;
            Node* next;
            Node(const T& v) : value(v), prev(nullptr), next(nullptr) {}
        };

        Node* head_;
        Node* tail_;
        std::size_t size_;

    public:
        DoublyLinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}

        ~DoublyLinkedList() {
            Node* cur = head_;
            while (cur != nullptr) {
                Node* nxt = cur->next;
                delete cur;
                cur = nxt;
            }
        }

        void push_front(const T& value) {
            Node* n = new Node(value);
            n->next = head_;
            if (head_ != nullptr) head_->prev = n;
            head_ = n;
            if (tail_ == nullptr) tail_ = n;
            size_ = size_ + 1;
        }

        void push_back(const T& value) {
            Node* n = new Node(value);
            n->prev = tail_;
            if (tail_ != nullptr) tail_->next = n;
            tail_ = n;
            if (head_ == nullptr) head_ = n;
            size_ = size_ + 1;
        }

        void pop_front() {
            if (head_ == nullptr) throw std::out_of_range("DLL::pop_front empty");
            Node* old = head_;
            head_ = head_->next;
            if (head_ != nullptr) head_->prev = nullptr;
            else tail_ = nullptr;
            delete old;
            size_ = size_ - 1;
        }

        void pop_back() {
            if (tail_ == nullptr) throw std::out_of_range("DLL::pop_back empty");
            Node* old = tail_;
            tail_ = tail_->prev;
            if (tail_ != nullptr) tail_->next = nullptr;
            else head_ = nullptr;
            delete old;
            size_ = size_ - 1;
        }

        T& front() {
            if (head_ == nullptr) throw std::out_of_range("DLL::front empty");
            return head_->value;
        }
        T& back() {
            if (tail_ == nullptr) throw std::out_of_range("DLL::back empty");
            return tail_->value;
        }

        bool empty() const { return head_ == nullptr; }
        std::size_t size() const { return size_; }
    };

} // namespace dsa
