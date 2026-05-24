// main.cpp — Week 07 demo: Bubble Sort vs Shell Sort
// I run BOTH algorithms on the same random data and print how many
// comparisons and swaps each one did, plus the sorted result.
#include <iostream>
#include "dsa/Sorting.hpp"

// Helper that prints n integers separated by spaces.
static void print(int* a, std::size_t n) {
    for (std::size_t i = 0; i < n; ++i) std::cout << a[i] << " ";
    std::cout << "\n";
}

int main() {
    // The original data — I keep it untouched so I can copy from it twice.
    int original[10] = {7, 3, 9, 1, 5, 8, 2, 4, 6, 0};

    // ---- Bubble sort run ----
    int a[10];
    // Copy the original into the working buffer.
    for (int i = 0; i < 10; ++i) a[i] = original[i];
    // Counters for comparisons and swaps.
    std::size_t cmp = 0, sw = 0;
    // Sort using bubble sort and let it write the counts into cmp/sw.
    dsa::bubble_sort(a, 10, &cmp, &sw);
    // Print the sorted array and the counters.
    std::cout << "Bubble sort: "; print(a, 10);
    std::cout << "  comparisons=" << cmp << " swaps=" << sw << "\n";

    // ---- Shell sort run on the SAME starting data ----
    for (int i = 0; i < 10; ++i) a[i] = original[i];
    // Reset the counters before the second run.
    cmp = 0; sw = 0;
    dsa::shell_sort(a, 10, &cmp, &sw);
    std::cout << "Shell sort:  "; print(a, 10);
    std::cout << "  comparisons=" << cmp << " swaps=" << sw << "\n";
    return 0;
}
