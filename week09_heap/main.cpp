// main.cpp — Week 09 demo: Max-Heap + Heapsort
#include <iostream>
#include "dsa/Heap.hpp"
#include "dsa/Sorting.hpp"

// Helper that prints n integers on one line.
static void print(int* a, std::size_t n) {
    for (std::size_t i = 0; i < n; ++i) std::cout << a[i] << " ";
    std::cout << "\n";
}

int main() {
    // ----- Heap used as a priority queue -----
    std::cout << "=== Max-Heap as priority queue ===\n";
    // Empty heap of ints.
    dsa::Heap<int> h;
    // Push a few values and print the new top after each one so I can
    // see the heap property in action (top always = max so far).
    int vals[] = {3, 1, 9, 4, 7, 2, 8};
    for (int v : vals) { h.push(v); std::cout << "push " << v
                                              << " -> top=" << h.top() << "\n"; }
    // Repeatedly pop -> values come out from largest to smallest.
    std::cout << "Pop order (should be 9,8,7,4,3,2,1): ";
    while (!h.empty()) { std::cout << h.top() << " "; h.pop(); }
    std::cout << "\n";

    // ----- Heapsort -----
    std::cout << "\n=== Heapsort ===\n";
    // Mixed-up array.
    int a[10] = {5,3,8,1,7,2,9,4,6,0};
    std::cout << "before: "; print(a, 10);
    // Heapsort in place — O(n log n) worst case.
    dsa::heapsort(a, 10);
    std::cout << "after : "; print(a, 10);
    return 0;
}
