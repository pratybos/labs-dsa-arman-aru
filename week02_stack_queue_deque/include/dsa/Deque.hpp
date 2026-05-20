// Deque<T>
// --------
// Double-ended queue. I can push and pop from BOTH ends in O(1).
// Same idea as Queue: a circular buffer with front_ and back_ indices.
//
// Convention I use here:
//   front_ = index of the FIRST real element (if size_ > 0)
//   back_  = index of the slot AFTER the last real element (next push_back slot)
//   Number of items in the ring = size_.
//
// push_front: move front_ one step BACKWARDS (with wrap), then write.
// push_back:  write at back_, then move back_ FORWARDS (with wrap).

#pragma once
#include <cstddef>
#include <stdexcept>

namespace dsa {

    template <class T>
    class Deque {
    public:
        Deque()
            : data_(nullptr), capacity_(0), size_(0), front_(0), back_(0) {
        }

        ~Deque() {
            delete[] data_;
        }

        // push_back — add to the end. O(1) amortized.
        void push_back(const T& value) {
            if (size_ == capacity_) grow();
            data_[back_] = value;
            back_ = (back_ + 1) % capacity_;
            size_ = size_ + 1;
        }

        // push_front — add to the beginning. O(1) amortized.
        // I move front_ one step backward (with wrap-around using a trick:
        // (front_ + capacity_ - 1) % capacity_ instead of front_ - 1
        // because front_ is unsigned and could underflow).
        void push_front(const T& value) {
            if (size_ == capacity_) grow();
            front_ = (front_ + capacity_ - 1) % capacity_;
            data_[front_] = value;
            size_ = size_ + 1;
        }

        // pop_front — remove the first element.
        void pop_front() {
            if (size_ == 0) {
                throw std::out_of_range("Deque::pop_front - deque is empty");
            }
            front_ = (front_ + 1) % capacity_;
            size_ = size_ - 1;
        }

        // pop_back — remove the last element.
        // back_ points AFTER the last element, so I move it one step back.
        void pop_back() {
            if (size_ == 0) {
                throw std::out_of_range("Deque::pop_back - deque is empty");
            }
            back_ = (back_ + capacity_ - 1) % capacity_;
            size_ = size_ - 1;
        }

        // Look at the first / last element (do not remove).
        T& front() {
            if (size_ == 0) throw std::out_of_range("Deque::front - empty");
            return data_[front_];
        }
        const T& front() const {
            if (size_ == 0) throw std::out_of_range("Deque::front - empty");
            return data_[front_];
        }

        T& back() {
            if (size_ == 0) throw std::out_of_range("Deque::back - empty");
            // The real last item is one step BEFORE back_.
            std::size_t lastIdx = (back_ + capacity_ - 1) % capacity_;
            return data_[lastIdx];
        }
        const T& back() const {
            if (size_ == 0) throw std::out_of_range("Deque::back - empty");
            std::size_t lastIdx = (back_ + capacity_ - 1) % capacity_;
            return data_[lastIdx];
        }

        bool empty() const { return size_ == 0; }
        std::size_t size() const { return size_; }

    private:
        T* data_;
        std::size_t capacity_;
        std::size_t size_;
        std::size_t front_;
        std::size_t back_;

        void grow() {
            std::size_t newCap = (capacity_ == 0) ? 1 : capacity_ * 2;
            T* newData = new T[newCap];

            // Re-pack the ring into a linear block starting at index 0.
            for (std::size_t i = 0; i < size_; ++i) {
                newData[i] = data_[(front_ + i) % capacity_];
            }

            delete[] data_;
            data_ = newData;
            capacity_ = newCap;
            front_ = 0;
            back_ = size_;
        }
    };

} // namespace dsa
