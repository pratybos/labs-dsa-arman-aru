// Sorting.hpp — Heapsort + helpers
// --------------------------------
// heapify_down: classic "sift down" on a raw array.
// build_heap:   turn arr[0..n-1] into a max-heap by sifting down from
//               the last non-leaf back to index 0. O(n) overall.
// heapsort:     after build_heap, repeatedly swap arr[0] with arr[end]
//               and sift_down on the shrinking heap [0..end-1].
//
// Complexity: heapsort is O(n log n) in the WORST case
// (unlike quicksort, whose worst case is O(n^2)).

#pragma once
#include <cstddef>

namespace dsa {

    template <class T>
    void heapify_down(T* arr, int n, int i) {
        while (true) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int largest = i;
            if (left  < n && arr[largest] < arr[left])  largest = left;
            if (right < n && arr[largest] < arr[right]) largest = right;
            if (largest == i) break;
            T tmp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = tmp;
            i = largest;
        }
    }

    // Bottom-up build_heap. Runs in O(n).
    template <class T>
    void build_heap(T* arr, int n) {
        for (int i = n / 2 - 1; i >= 0; --i) {
            heapify_down(arr, n, i);
        }
    }

    template <class T>
    void heapsort(T* arr, int n) {
        if (n < 2) return;
        build_heap(arr, n);
        for (int end = n - 1; end > 0; --end) {
            // The biggest element is at arr[0]; move it to the end.
            T tmp = arr[0];
            arr[0] = arr[end];
            arr[end] = tmp;
            // Restore the heap property on the shrunken heap [0..end-1].
            heapify_down(arr, end, 0);
        }
    }

    template <class T>
    void heapsort(T* arr, std::size_t n) {
        heapsort(arr, static_cast<int>(n));
    }

} // namespace dsa
