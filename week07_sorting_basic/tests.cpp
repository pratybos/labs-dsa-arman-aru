// Make doctest generate main() automatically.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dsa/Sorting.hpp"

// Helper: returns true if a[0..n-1] is in non-decreasing order.
static bool isSorted(int* a, std::size_t n) {
    // Walk from index 1 onward; any descending neighbor pair means not sorted.
    for (std::size_t i = 1; i < n; ++i) if (a[i] < a[i-1]) return false;
    return true;
}

TEST_CASE("bubble_sort empty/one") {
    // Edge cases: an empty array and a one-element array must NOT crash.
    int a[1] = {42};
    dsa::bubble_sort<int>(a, 0); // n=0 -> nothing to do
    dsa::bubble_sort<int>(a, 1); // n=1 -> already sorted
    // The single element must remain untouched.
    CHECK(a[0] == 42);
}

TEST_CASE("bubble_sort random") {
    // A mixed-up array.
    int a[8] = {5,3,8,1,7,2,9,4};
    dsa::bubble_sort<int>(a, 8);
    // After sorting, the array must be in order.
    CHECK(isSorted(a, 8));
}

TEST_CASE("bubble_sort already sorted") {
    // Best case for bubble sort: already sorted -> still sorted at the end.
    int a[5] = {1,2,3,4,5};
    dsa::bubble_sort<int>(a, 5);
    CHECK(isSorted(a, 5));
}

TEST_CASE("bubble_sort reverse sorted") {
    // Worst case for bubble sort: every neighbor is wrong -> many swaps.
    int a[5] = {5,4,3,2,1};
    dsa::bubble_sort<int>(a, 5);
    CHECK(isSorted(a, 5));
}

TEST_CASE("bubble_sort counters increase") {
    // Sanity check: the comparison/swap counters must actually grow when
    // the input is unsorted.
    int a[5] = {5,4,3,2,1};
    std::size_t c = 0, s = 0;
    dsa::bubble_sort<int>(a, 5, &c, &s);
    CHECK(c > 0);
    CHECK(s > 0);
}

TEST_CASE("shell_sort random") {
    // Same idea: random array gets sorted correctly.
    int a[8] = {5,3,8,1,7,2,9,4};
    dsa::shell_sort<int>(a, 8);
    CHECK(isSorted(a, 8));
}

TEST_CASE("shell_sort already sorted") {
    // Already sorted -> remains sorted.
    int a[5] = {1,2,3,4,5};
    dsa::shell_sort<int>(a, 5);
    CHECK(isSorted(a, 5));
}

TEST_CASE("shell_sort reverse sorted") {
    // Reverse case for shell sort.
    int a[6] = {6,5,4,3,2,1};
    dsa::shell_sort<int>(a, 6);
    CHECK(isSorted(a, 6));
}

TEST_CASE("shell_sort duplicates") {
    // Duplicates must not confuse the algorithm.
    int a[7] = {3,1,3,2,1,3,2};
    dsa::shell_sort<int>(a, 7);
    CHECK(isSorted(a, 7));
}
