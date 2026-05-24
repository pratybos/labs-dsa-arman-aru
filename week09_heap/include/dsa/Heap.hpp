// Heap.hpp — Max-Heap
// -------------------
// A binary max-heap stored INSIDE a flat array (DynamicArray).
// Indexing rule (this is the key trick):
//   parent of i  = (i - 1) / 2
//   left  child  =  2 * i + 1
//   right child  =  2 * i + 2
//
// Heap property: parent >= each child (so the largest is at index 0).
//
// push: place new value at the end, then "sift up" while it is bigger
//       than its parent.
// pop:  replace top with the last element, shrink size, then "sift down"
//       while the new top is smaller than its largest child.

#pragma once
#include <cstddef>
#include <stdexcept>
#include "DynamicArray.hpp"

namespace dsa {

    template <class T>
    class Heap {
    public:
        // push — insert a value. O(log n).
        void push(const T& value) {
            data_.push_back(value);
            sift_up(data_.size() - 1);
        }

        // top — read the maximum (do not remove). O(1). Throws if empty.
        const T& top() const {
            if (data_.size() == 0) {
                throw std::out_of_range("Heap::top - empty");
            }
            return data_[0];
        }

        // pop — remove the maximum. O(log n). Throws if empty.
        void pop() {
            std::size_t n = data_.size();
            if (n == 0) {
                throw std::out_of_range("Heap::pop - empty");
            }
            // Move the last element to index 0, drop the last slot,
            // then sift down to restore the heap property.
            data_[0] = data_[n - 1];
            data_.pop_back();
            if (data_.size() > 0) {
                sift_down(0, data_.size());
            }
        }

        bool empty() const { return data_.size() == 0; }
        std::size_t size() const { return data_.size(); }

    private:
        DynamicArray<T> data_;

        // Move data_[i] up while it is larger than its parent.
        void sift_up(std::size_t i) {
            while (i > 0) {
                std::size_t parent = (i - 1) / 2;
                if (data_[parent] < data_[i]) {
                    T tmp = data_[parent];
                    data_[parent] = data_[i];
                    data_[i] = tmp;
                    i = parent;
                } else {
                    break;
                }
            }
        }

        // Move data_[i] down while it is smaller than its biggest child.
        // n = current logical heap size (used by heapsort to shrink heap).
        void sift_down(std::size_t i, std::size_t n) {
            while (true) {
                std::size_t left = 2 * i + 1;
                std::size_t right = 2 * i + 2;
                std::size_t largest = i;
                if (left  < n && data_[largest] < data_[left])  largest = left;
                if (right < n && data_[largest] < data_[right]) largest = right;
                if (largest == i) break;
                T tmp = data_[i];
                data_[i] = data_[largest];
                data_[largest] = tmp;
                i = largest;
            }
        }
    };

} // namespace dsa
