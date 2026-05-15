// DynamicArray<T>
// ----------------
// My own simple version of std::vector for the DSA course.
// It is a template so it can hold any type T (int, double, string, ...).
// I use raw memory (new[] / delete[]) like the lab requires.
//
// Idea in one sentence:
//   I keep a pointer to a block of memory (data_),
//   I remember how many items I actually have (size_),
//   and I remember how big the block is (capacity_).
//   When the block gets full, I make a bigger block and copy everything over.

#pragma once
#include <cstddef>     // for std::size_t
#include <stdexcept>   // for std::out_of_range

namespace dsa {

    template <class T>
    class DynamicArray {
    public:
        // ---- Big three: constructor, destructor ----
        DynamicArray();
        ~DynamicArray();

        // ---- Info about the array ----
        std::size_t size() const;       // how many items I currently store
        std::size_t capacity() const;   // how many items fit before I must grow

        // ---- Fast access (no checking, like std::vector::operator[]) ----
        T& operator[](std::size_t index);
        const T& operator[](std::size_t index) const;

        // ---- Safe access (throws if index is bad) ----
        T& at(std::size_t index);
        const T& at(std::size_t index) const;

        // ---- Adding / removing at the end ----
        void push_back(const T& value);
        void pop_back();

        // ---- Part B: insert / erase anywhere ----
        void insert(std::size_t index, const T& value);
        void erase(std::size_t index);

        // ---- Manually grow the storage (does not shrink) ----
        void reserve(std::size_t newCapacity);

    private:
        T* data_;                 // pointer to the raw memory block
        std::size_t size_;        // number of real items in the array
        std::size_t capacity_;    // total slots available in data_
    };


    // =====================================================================
    // Implementation below.
    // Templates must have their code visible to the compiler when used,
    // so I put the definitions in this header file (not in a .cpp file).
    // =====================================================================


    // Constructor: build an empty array.
    // No memory is allocated yet — I only ask for memory when I really need it.
    template <class T>
    DynamicArray<T>::DynamicArray()
        : data_(nullptr), size_(0), capacity_(0) {
    }


    // Destructor: free the memory I allocated with new[].
    // delete[] is safe even when data_ is nullptr.
    template <class T>
    DynamicArray<T>::~DynamicArray() {
        delete[] data_;
    }


    // Return how many real elements are stored.
    template <class T>
    std::size_t DynamicArray<T>::size() const {
        return size_;
    }


    // Return how many elements fit inside the current memory block.
    template <class T>
    std::size_t DynamicArray<T>::capacity() const {
        return capacity_;
    }


    // operator[] — fast access, no bounds checking (just like std::vector).
    // The user is responsible for passing a valid index here.
    template <class T>
    T& DynamicArray<T>::operator[](std::size_t index) {
        return data_[index];
    }

    template <class T>
    const T& DynamicArray<T>::operator[](std::size_t index) const {
        return data_[index];
    }


    // at() — safe access. If the index is wrong I throw std::out_of_range.
    // I check index >= size_ (NOT capacity_) because empty slots are not real items.
    template <class T>
    T& DynamicArray<T>::at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("DynamicArray::at - index is out of range");
        }
        return data_[index];
    }

    template <class T>
    const T& DynamicArray<T>::at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("DynamicArray::at - index is out of range");
        }
        return data_[index];
    }

} // namespace dsa
