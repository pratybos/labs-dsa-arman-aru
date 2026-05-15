// main.cpp
// ---------
// Small demo program for my DynamicArray.
// It is not a test — the real tests live in tests.cpp.
// I just print things to the screen so I can SEE the array working.

#include <iostream>
#include "dsa/DynamicArray.hpp"

// Helper: print the array on one line (so I can see it after each step).
static void printArray(const dsa::DynamicArray<int>& a) {
    std::cout << "size=" << a.size()
              << " capacity=" << a.capacity()
              << " [ ";
    for (std::size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << " ";
    }
    std::cout << "]\n";
}

int main() {
    // Make an empty array of ints.
    dsa::DynamicArray<int> a;
    std::cout << "Just created an empty DynamicArray:\n";
    printArray(a);

    return 0;
}
