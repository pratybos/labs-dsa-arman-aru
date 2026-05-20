// This special define tells the doctest header to also create a main() function
// for me so I do NOT have to write `int main()` myself in this file.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
// Include the single-header testing library (lives in include/doctest.h).
#include "doctest.h"

// My own dynamic array implementation that I am about to test.
#include "dsa/DynamicArray.hpp"
// std::size_t — the unsigned integer type used for sizes and indices.
#include <cstddef>
// std::out_of_range — the exception my class throws on a bad index.
#include <stdexcept>

TEST_CASE("starts empty") {
    // Make a fresh array of ints.
    dsa::DynamicArray<int> a;
    // Brand-new array must have zero elements.
    CHECK(a.size() == 0);
    // And zero capacity, because I do not allocate until I really need to.
    CHECK(a.capacity() == 0);
}

TEST_CASE("push_back stores values") {
    // Empty array.
    dsa::DynamicArray<int> a;
    // Add three values to the end, one at a time.
    a.push_back(5);
    a.push_back(8);
    a.push_back(2);

    // size() should report exactly 3 items.
    CHECK(a.size() == 3);
    // The values must appear in insertion order: 5, 8, 2.
    CHECK(a[0] == 5);
    CHECK(a[1] == 8);
    CHECK(a[2] == 2);
}

TEST_CASE("capacity grows but never less than size") {
    // I push 30 items and check after each push that:
    //   - size matches the number of pushes
    //   - capacity is big enough to fit them
    //   - capacity never SHRINKS (it can stay the same or grow)
    dsa::DynamicArray<int> a;

    // Remember the previous capacity so I can compare each round.
    std::size_t lastCap = a.capacity();
    for (int i = 0; i < 30; ++i) {
        // Add another integer.
        a.push_back(i);
        // size() must match how many items I have pushed (i+1).
        CHECK(a.size() == static_cast<std::size_t>(i + 1));
        // capacity must be at least as big as size — there must always be
        // enough room for the items I already stored.
        CHECK(a.capacity() >= a.size());
        // capacity is allowed to GROW between pushes, but never shrink.
        CHECK(a.capacity() >= lastCap);
        // Remember the current capacity for the next iteration.
        lastCap = a.capacity();
    }
}

TEST_CASE("pop_back decreases size (does not require shrinking capacity)") {
    // Build a small array of 3 items.
    dsa::DynamicArray<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    // Capture the capacity BEFORE pop_back so I can compare later.
    const std::size_t capBefore = a.capacity();

    // Remove the last element. size() drops to 2 but the values that stay
    // must be unchanged.
    a.pop_back();
    CHECK(a.size() == 2);
    CHECK(a[0] == 1);
    CHECK(a[1] == 2);

    // The lab rule says pop_back must NOT shrink the buffer — capacity
    // must be the same as it was before the pop.
    CHECK(a.capacity() == capBefore);
}

TEST_CASE("at() bounds checking") {
    // One-element array.
    dsa::DynamicArray<int> a;
    a.push_back(10);

    // at(0) is valid and returns the stored value.
    CHECK(a.at(0) == 10);
    // at(1) is one past the end -> out_of_range.
    CHECK_THROWS_AS(a.at(1), std::out_of_range);
    // A wildly invalid index also throws.
    CHECK_THROWS_AS(a.at(999), std::out_of_range);
}

TEST_CASE("insert shifts elements to the right") {
    // Start with [10, 20, 30].
    dsa::DynamicArray<int> a;
    a.push_back(10);
    a.push_back(20);
    a.push_back(30);

    // insert(1, 99) — put 99 at index 1, shift 20 and 30 right.
    // Resulting array: [10, 99, 20, 30].
    a.insert(1, 99);
    CHECK(a.size() == 4);
    CHECK(a[0] == 10);
    CHECK(a[1] == 99);
    CHECK(a[2] == 20);
    CHECK(a[3] == 30);
}

TEST_CASE("insert at end behaves like push_back") {
    // [1, 2]
    dsa::DynamicArray<int> a;
    a.push_back(1);
    a.push_back(2);

    // insert at index == size means "put at the very end" -> [1, 2, 3].
    a.insert(2, 3);
    CHECK(a.size() == 3);
    CHECK(a[0] == 1);
    CHECK(a[1] == 2);
    CHECK(a[2] == 3);
}

TEST_CASE("erase shifts elements to the left") {
    // Build [10, 20, 30, 40].
    dsa::DynamicArray<int> a;
    a.push_back(10);
    a.push_back(20);
    a.push_back(30);
    a.push_back(40);

    // Remove the element at index 1 (value 20).
    // The values to the right (30, 40) shift one step left.
    // Resulting array: [10, 30, 40].
    a.erase(1);
    CHECK(a.size() == 3);
    CHECK(a[0] == 10);
    CHECK(a[1] == 30);
    CHECK(a[2] == 40);
}

TEST_CASE("erase last element is like pop_back") {
    // [7, 8, 9]
    dsa::DynamicArray<int> a;
    a.push_back(7);
    a.push_back(8);
    a.push_back(9);

    // Erasing the last index is the same effect as pop_back -> [7, 8].
    a.erase(2);
    CHECK(a.size() == 2);
    CHECK(a[0] == 7);
    CHECK(a[1] == 8);
}

TEST_CASE("insert/erase invalid index throws") {
    // [1, 2]
    dsa::DynamicArray<int> a;
    a.push_back(1);
    a.push_back(2);

    // insert at index > size is forbidden -> out_of_range.
    CHECK_THROWS_AS(a.insert(99, 5), std::out_of_range);
    // erase at index >= size is forbidden -> out_of_range.
    CHECK_THROWS_AS(a.erase(99), std::out_of_range);

    // erase at index == size (here 2) is also invalid — there is no
    // element at position "size", only positions 0..size-1.
    CHECK_THROWS_AS(a.erase(a.size()), std::out_of_range);
}
