// main.cpp
// ---------
// Small demo program for my DynamicArray.
// It is not a test — the real tests live in tests.cpp.
// I just print things to the screen so I can SEE the array working.

// std::cout / std::cin live in <iostream>.
#include <iostream>
// My own dynamic array.
#include "dsa/DynamicArray.hpp"

// Helper that prints size, capacity, and every element of the array
// on one line so I can see exactly what is happening after each operation.
static void printArray(const dsa::DynamicArray<int>& a) {
    // Print the size and capacity first.
    std::cout << "size=" << a.size()
              << " capacity=" << a.capacity()
              << " [ ";
    // Then print each element separated by a space.
    for (std::size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << " ";
    }
    // Close the line.
    std::cout << "]\n";
}

int main() {
    // Make an empty int array.
    dsa::DynamicArray<int> a;
    // Show the starting state (should be size=0 capacity=0 [ ]).
    std::cout << "Just created an empty DynamicArray:\n";
    printArray(a);

    // Push five numbers in a row. Capacity grows automatically as needed.
    std::cout << "\nAfter push_back 10, 20, 30, 40, 50:\n";
    a.push_back(10);
    a.push_back(20);
    a.push_back(30);
    a.push_back(40);
    a.push_back(50);
    printArray(a);

    // Insert 99 at index 2 — every value at index >= 2 shifts one slot right.
    std::cout << "\nAfter insert(2, 99):\n";
    a.insert(2, 99);
    printArray(a);

    // Erase the element at index 0 — every remaining value shifts left.
    std::cout << "\nAfter erase(0):\n";
    a.erase(0);
    printArray(a);

    // pop_back removes the last element. size shrinks by 1; capacity stays.
    std::cout << "\nAfter pop_back():\n";
    a.pop_back();
    printArray(a);

    // at(index) throws std::out_of_range when index is bad. I catch the
    // exception so the program does not crash and so the teacher can see
    // the error message.
    std::cout << "\nTrying a.at(999) (should throw):\n";
    try {
        // This line will throw because the array has fewer than 999 items.
        std::cout << a.at(999) << "\n";
    } catch (const std::out_of_range& e) {
        // The catch block runs and prints the message carried by the exception.
        std::cout << "  Caught error: " << e.what() << "\n";
    }

    // Goodbye message.
    std::cout << "\nDemo finished.\n";
    return 0;
}
