// Ask doctest to generate the main() function for us.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

// The two list implementations under test.
#include "dsa/SinglyLinkedList.hpp"
#include "dsa/DoublyLinkedList.hpp"
// For std::out_of_range below.
#include <stdexcept>

// ---- SinglyLinkedList ----
TEST_CASE("SLL empty") {
    // Brand-new list — must be empty and size 0.
    dsa::SinglyLinkedList<int> l;
    CHECK(l.empty());
    CHECK(l.size() == 0);
    // Reading/removing the front when empty must throw.
    CHECK_THROWS_AS(l.front(), std::out_of_range);
    CHECK_THROWS_AS(l.pop_front(), std::out_of_range);
}

TEST_CASE("SLL push_back/front order") {
    dsa::SinglyLinkedList<int> l;
    // Push 1, 2, 3 to the BACK -> list looks like 1 -> 2 -> 3.
    l.push_back(1); l.push_back(2); l.push_back(3);
    CHECK(l.size() == 3);
    // The first inserted (1) is the head -> front() == 1.
    CHECK(l.front() == 1);
    // Remove the head; now front() must be 2.
    l.pop_front();
    CHECK(l.front() == 2);
}

TEST_CASE("SLL push_front") {
    dsa::SinglyLinkedList<int> l;
    // push_front puts a new node at the HEAD each time.
    // After pushing 1, then 2, then 3, the list reads 3 -> 2 -> 1.
    l.push_front(1); l.push_front(2); l.push_front(3);
    CHECK(l.front() == 3);
    CHECK(l.size() == 3);
}

TEST_CASE("SLL find") {
    dsa::SinglyLinkedList<int> l;
    // Add 10, 20, 30 -> walking the list finds each of them.
    l.push_back(10); l.push_back(20); l.push_back(30);
    CHECK(l.find(10));
    CHECK(l.find(20));
    CHECK(l.find(30));
    // 99 is not in the list — find() must return false.
    CHECK_FALSE(l.find(99));
}

TEST_CASE("SLL remove_first head/middle/tail/notfound") {
    dsa::SinglyLinkedList<int> l;
    // Build 1 -> 2 -> 3 -> 4
    l.push_back(1); l.push_back(2); l.push_back(3); l.push_back(4);

    // Removing the value at the head (1): list becomes 2 -> 3 -> 4.
    CHECK(l.remove_first(1));
    CHECK(l.size() == 3);
    CHECK(l.front() == 2);

    // Removing a middle value (3): list becomes 2 -> 4.
    CHECK(l.remove_first(3));
    CHECK(l.size() == 2);

    // Removing the tail (4): list becomes 2.
    CHECK(l.remove_first(4));
    CHECK(l.size() == 1);
    CHECK(l.front() == 2);

    // Trying to remove a value that does not exist -> false.
    CHECK_FALSE(l.remove_first(999));
}

TEST_CASE("SLL reverse") {
    dsa::SinglyLinkedList<int> l;
    // Start with 1 -> 2 -> 3.
    l.push_back(1); l.push_back(2); l.push_back(3);
    // After reverse(): 3 -> 2 -> 1.
    l.reverse();
    // Pop the head three times and confirm the order is 3, 2, 1.
    CHECK(l.front() == 3);
    l.pop_front();
    CHECK(l.front() == 2);
    l.pop_front();
    CHECK(l.front() == 1);
}

TEST_CASE("SLL reverse empty/one") {
    dsa::SinglyLinkedList<int> l;
    // Reversing an empty list must not crash and the list stays empty.
    l.reverse();
    CHECK(l.empty());
    // Reversing a one-element list is a no-op (still that element).
    l.push_back(7);
    l.reverse();
    CHECK(l.front() == 7);
}

// ---- DoublyLinkedList ----
TEST_CASE("DLL push_back / pop_back") {
    // The doubly-linked list has prev pointers, so pop_back is O(1).
    dsa::DoublyLinkedList<int> d;
    // Build 1 <-> 2 <-> 3
    d.push_back(1); d.push_back(2); d.push_back(3);
    // Both ends are reachable.
    CHECK(d.front() == 1);
    CHECK(d.back() == 3);
    // pop_back removes the tail -> 1 <-> 2.
    d.pop_back();
    CHECK(d.back() == 2);
    // pop_front removes the head -> 2.
    d.pop_front();
    CHECK(d.front() == 2);
    CHECK(d.size() == 1);
}
