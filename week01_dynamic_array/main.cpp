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

    // Push a few numbers. Capacity will grow automatically.
    std::cout << "\nAfter push_back 10, 20, 30, 40, 50:\n";
    a.push_back(10);
    a.push_back(20);
    a.push_back(30);
    a.push_back(40);
    a.push_back(50);
    printArray(a);

    // Insert 99 at position 2 — the values to the right shift over.
    std::cout << "\nAfter insert(2, 99):\n";
    a.insert(2, 99);
    printArray(a);

    // Erase the element at position 0 — the rest shifts left.
    std::cout << "\nAfter erase(0):\n";
    a.erase(0);
    printArray(a);

    return 0;
}
