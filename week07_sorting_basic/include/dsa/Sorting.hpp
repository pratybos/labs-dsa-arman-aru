// Sorting.hpp — Week 07
// ---------------------
// Two classic sorting algorithms written from scratch.
// I also count comparisons and swaps so I can compare them
// in the demo program later.
//
// Bubble Sort:
//   Walk the array many times. On each walk, swap any two
//   neighbors that are in wrong order. The biggest values
//   "bubble" to the end one pass at a time.
//   Time: O(n^2) worst & average. Stable. In-place.
//
// Shell Sort:
//   Like insertion sort but compares items "gap" positions apart.
//   We start with a big gap and reduce it down to 1.
//   Time: depends on gap sequence. With n/2, n/4, ..., 1 it is
//   often around O(n^2) worst, O(n log^2 n) average-ish.
//   In-place, NOT stable.

#pragma once
#include <cstddef>

namespace dsa {

    // ---- Bubble Sort ----
    // Sorts a[0..n-1] in non-decreasing order.
    // Counters (comparisons, swaps) are optional — pass nullptr to ignore.
    template <class T>
    void bubble_sort(T* a, std::size_t n,
                     std::size_t* comparisons = nullptr,
                     std::size_t* swaps = nullptr) {
        if (comparisons) *comparisons = 0;
        if (swaps) *swaps = 0;
        if (n < 2) return;

        // After pass i, the last i elements are already in place.
        // So the inner loop only needs to go up to n - 1 - i.
        for (std::size_t i = 0; i < n - 1; ++i) {
            bool sortedNow = true;  // small optimization: stop early if no swaps
            for (std::size_t j = 0; j + 1 < n - i; ++j) {
                if (comparisons) ++(*comparisons);
                if (a[j + 1] < a[j]) {
                    // Swap the two neighbors.
                    T tmp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = tmp;
                    if (swaps) ++(*swaps);
                    sortedNow = false;
                }
            }
            if (sortedNow) break;
        }
    }

    // ---- Shell Sort ----
    // Gap sequence: n/2, n/4, ..., 1.
    // For each gap, we do an "insertion sort" but stepping by `gap`.
    template <class T>
    void shell_sort(T* a, std::size_t n,
                    std::size_t* comparisons = nullptr,
                    std::size_t* swaps = nullptr) {
        if (comparisons) *comparisons = 0;
        if (swaps) *swaps = 0;
        if (n < 2) return;

        for (std::size_t gap = n / 2; gap > 0; gap /= 2) {
            // Gapped insertion sort.
            for (std::size_t i = gap; i < n; ++i) {
                T temp = a[i];
                std::size_t j = i;
                // Shift larger elements `gap` positions to the right.
                while (j >= gap) {
                    if (comparisons) ++(*comparisons);
                    if (a[j - gap] > temp) {
                        a[j] = a[j - gap];
                        if (swaps) ++(*swaps);
                        j -= gap;
                    } else {
                        break;
                    }
                }
                // Place temp in its correct gapped position (only if we moved).
                if (j != i) {
                    a[j] = temp;
                    if (swaps) ++(*swaps);
                }
            }
        }
    }

} // namespace dsa
