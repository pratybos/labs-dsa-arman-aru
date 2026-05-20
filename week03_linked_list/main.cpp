// main.cpp — Week 03 demo: SinglyLinkedList
// Tiny program that prints the state of the list after each operation.
#include <iostream>
#include "dsa/SinglyLinkedList.hpp"

// Helper template that prints size + front of the list.
// I do not iterate inside because the nodes are private members of the list.
template <class T>
static void printList(dsa::SinglyLinkedList<T>& l) {
    // Show the count of items.
    std::cout << "size=" << l.size();
    // If there is at least one item, print the front value too.
    if (!l.empty()) std::cout << " front=" << l.front();
    // Finish the line.
    std::cout << "\n";
}

int main() {
    // Build an empty integer list.
    dsa::SinglyLinkedList<int> list;
    // Show empty state.
    std::cout << "Empty list:\n"; printList(list);

    // Add 10, 20, 30 to the back -> list: 10 -> 20 -> 30.
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    std::cout << "\nAfter push_back 10,20,30:\n"; printList(list);

    // Insert 5 at the HEAD -> list: 5 -> 10 -> 20 -> 30.
    list.push_front(5);
    std::cout << "\nAfter push_front(5):\n"; printList(list);

    // Demonstrate find(): true for 20, false for 999.
    std::cout << "\nfind(20)=" << list.find(20)
              << " find(999)=" << list.find(999) << "\n";

    // Remove the first occurrence of 20 -> list: 5 -> 10 -> 30.
    list.remove_first(20);
    std::cout << "\nAfter remove_first(20):\n"; printList(list);

    // Reverse in place -> list: 30 -> 10 -> 5.
    list.reverse();
    std::cout << "\nAfter reverse():\n"; printList(list);

    // Drop the new head (30) -> list: 10 -> 5.
    list.pop_front();
    std::cout << "\nAfter pop_front():\n"; printList(list);

    return 0;
}
