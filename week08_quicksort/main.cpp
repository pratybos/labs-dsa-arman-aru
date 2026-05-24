// main.cpp — Week 08 demo: Quicksort on 3 different inputs.
// Pivot strategy used: LAST element (Lomuto partition).
#include <iostream>
#include "dsa/Sorting.hpp"

// Helper that prints n integers on one line.
static void print(int* a, std::size_t n) {
    for (std::size_t i = 0; i < n; ++i) std::cout << a[i] << " ";
    std::cout << "\n";
}

int main() {
    // ---- Case 1: random data ----
    {
        // Mixed-up array.
        int a[10] = {5,3,8,1,7,2,9,4,6,0};
        std::cout << "random  before: "; print(a, 10);
        // Sort it in place.
        dsa::quicksort(a, 10);
        std::cout << "random  after : "; print(a, 10);
    }
    // ---- Case 2: already sorted ----
    {
        int a[6] = {1,2,3,4,5,6};
        std::cout << "sorted  before: "; print(a, 6);
        dsa::quicksort(a, 6);
        std::cout << "sorted  after : "; print(a, 6);
    }
    // ---- Case 3: reverse sorted ----
    {
        int a[6] = {6,5,4,3,2,1};
        std::cout << "reverse before: "; print(a, 6);
        dsa::quicksort(a, 6);
        std::cout << "reverse after : "; print(a, 6);
    }
    return 0;
}
