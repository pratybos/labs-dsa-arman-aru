// Make doctest generate main().
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dsa/Heap.hpp"
#include "dsa/Sorting.hpp"
#include <stdexcept>

// Helper: non-decreasing array check.
static bool isSorted(int* a, int n) {
    for (int i = 1; i < n; ++i) if (a[i] < a[i-1]) return false;
    return true;
}

TEST_CASE("Heap empty throws") {
    // A brand-new heap is empty.
    dsa::Heap<int> h;
    CHECK(h.empty());
    // top() and pop() must throw on an empty heap.
    CHECK_THROWS_AS(h.top(), std::out_of_range);
    CHECK_THROWS_AS(h.pop(), std::out_of_range);
}

TEST_CASE("Heap push keeps max on top") {
    // Push several values; the largest one seen so far must always be on top.
    dsa::Heap<int> h;
    h.push(3); CHECK(h.top() == 3);
    h.push(1); CHECK(h.top() == 3);
    h.push(9); CHECK(h.top() == 9);
    h.push(4); CHECK(h.top() == 9);
    h.push(7); CHECK(h.top() == 9);
    CHECK(h.size() == 5);
}

TEST_CASE("Heap pop gives descending order") {
    // Pushing then repeatedly popping a max-heap should yield values
    // in DESCENDING order (largest first).
    dsa::Heap<int> h;
    int vals[] = {3,1,9,4,7,2,8};
    for (int v : vals) h.push(v);
    // Track the previous popped value so I can check the order.
    int prev = 1000000;
    while (!h.empty()) {
        int t = h.top();
        // Each new top must be <= the previous top.
        CHECK(t <= prev);
        prev = t;
        h.pop();
    }
}

TEST_CASE("heapsort empty / one") {
    // Edge cases must not crash.
    int a[1] = {42};
    dsa::heapsort<int>(a, 0);
    dsa::heapsort<int>(a, 1);
    CHECK(a[0] == 42);
}

TEST_CASE("heapsort random") {
    // Standard test on shuffled input.
    int a[10] = {5,3,8,1,7,2,9,4,6,0};
    dsa::heapsort<int>(a, 10);
    CHECK(isSorted(a, 10));
}

TEST_CASE("heapsort already sorted") {
    // Already sorted -> still sorted.
    int a[5] = {1,2,3,4,5};
    dsa::heapsort<int>(a, 5);
    CHECK(isSorted(a, 5));
}

TEST_CASE("heapsort reverse sorted") {
    // Reverse case.
    int a[6] = {6,5,4,3,2,1};
    dsa::heapsort<int>(a, 6);
    CHECK(isSorted(a, 6));
}

TEST_CASE("heapsort duplicates") {
    // Duplicates must not break the algorithm.
    int a[7] = {3,1,3,2,1,3,2};
    dsa::heapsort<int>(a, 7);
    CHECK(isSorted(a, 7));
}
