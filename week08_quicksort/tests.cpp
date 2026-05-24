// Ask doctest to generate main() automatically.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dsa/Sorting.hpp"

// Helper: is the array non-decreasing?
static bool isSorted(int* a, std::size_t n) {
    for (std::size_t i = 1; i < n; ++i) if (a[i] < a[i-1]) return false;
    return true;
}

TEST_CASE("quicksort empty / one") {
    // Edge cases — must not crash, must not change the single element.
    int a[1] = {7};
    dsa::quicksort<int>(a, 0);
    dsa::quicksort<int>(a, 1);
    CHECK(a[0] == 7);
}

TEST_CASE("quicksort random") {
    // Standard mixed-up array.
    int a[10] = {5,3,8,1,7,2,9,4,6,0};
    dsa::quicksort<int>(a, 10);
    // The array must be sorted afterwards.
    CHECK(isSorted(a, 10));
    // The min ends up at index 0, the max at index 9.
    CHECK(a[0] == 0);
    CHECK(a[9] == 9);
}

TEST_CASE("quicksort already sorted") {
    // Pre-sorted input — must still come out sorted.
    int a[6] = {1,2,3,4,5,6};
    dsa::quicksort<int>(a, 6);
    CHECK(isSorted(a, 6));
}

TEST_CASE("quicksort reverse sorted") {
    // Reverse input is one of quicksort's classic worst cases for Lomuto.
    int a[6] = {6,5,4,3,2,1};
    dsa::quicksort<int>(a, 6);
    CHECK(isSorted(a, 6));
}

TEST_CASE("quicksort duplicates") {
    // Many equal values — must still produce a sorted array.
    int a[8] = {3,3,3,1,2,1,2,3};
    dsa::quicksort<int>(a, 8);
    CHECK(isSorted(a, 8));
}

TEST_CASE("partition correctness") {
    // Lomuto partition picks arr[high] as the pivot. Here pivot = 5.
    int a[6] = {3,8,1,7,2,5};
    int p = dsa::partition(a, 0, 5);
    // After partition: everything at indices [0..p-1] must be <= pivot.
    for (int i = 0; i < p; ++i)   CHECK(a[i] <= 5);
    // Everything at [p+1..5] must be > pivot.
    for (int i = p + 1; i < 6; ++i) CHECK(a[i] > 5);
    // The pivot ends up at position p.
    CHECK(a[p] == 5);
}
