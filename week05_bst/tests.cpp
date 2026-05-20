// Ask doctest to generate main() automatically.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dsa/BST.hpp"
#include <stdexcept>

TEST_CASE("BST empty") {
    // A brand-new BST must be empty and have height 0.
    dsa::BST<int> b;
    CHECK(b.empty());
    CHECK(b.size() == 0);
    CHECK(b.height() == 0);
    // contains() on empty tree -> false.
    CHECK_FALSE(b.contains(1));
    // min()/max() on empty tree must throw.
    CHECK_THROWS_AS(b.min(), std::out_of_range);
    CHECK_THROWS_AS(b.max(), std::out_of_range);
}

TEST_CASE("BST insert + contains + ignore duplicates") {
    dsa::BST<int> b;
    // Insert three distinct keys plus one duplicate (the second 30).
    b.insert(50); b.insert(30); b.insert(70); b.insert(30);
    // Duplicates must be ignored, so size must be 3 (not 4).
    CHECK(b.size() == 3);
    // Each inserted key must be findable.
    CHECK(b.contains(50));
    CHECK(b.contains(30));
    CHECK(b.contains(70));
    // A value that was never inserted must not be found.
    CHECK_FALSE(b.contains(99));
}

TEST_CASE("BST min / max") {
    // Build a balanced-ish tree of 7 nodes.
    dsa::BST<int> b;
    int vs[] = {50,30,70,20,40,60,80};
    for (int v : vs) b.insert(v);
    // min = leftmost node, max = rightmost node.
    CHECK(b.min() == 20);
    CHECK(b.max() == 80);
}

TEST_CASE("BST inorder gives sorted output") {
    dsa::BST<int> b;
    // Insert in random-ish order.
    int vs[] = {5,3,8,1,4,7,9};
    for (int v : vs) b.insert(v);
    // In-order traversal of a BST always returns keys in SORTED order.
    int out[7];
    b.inorder(out);
    int expected[7] = {1,3,4,5,7,8,9};
    for (int i = 0; i < 7; ++i) CHECK(out[i] == expected[i]);
}

TEST_CASE("BST height (definition: empty=0, leaf=1)") {
    // Build a tree step-by-step and check the height after each insert.
    dsa::BST<int> b;
    b.insert(10);                 // root only
    CHECK(b.height() == 1);
    b.insert(5);                  // 10 with one left child (height 2)
    CHECK(b.height() == 2);
    b.insert(15);                 // 10 with two children (still height 2)
    CHECK(b.height() == 2);
    b.insert(3);                  // adds a level below 5 (height 3)
    CHECK(b.height() == 3);
}

TEST_CASE("BST remove leaf") {
    dsa::BST<int> b;
    int vs[] = {50,30,70};
    for (int v : vs) b.insert(v);
    // 30 is a leaf. remove() returns true and the size shrinks.
    CHECK(b.remove(30));
    CHECK_FALSE(b.contains(30));
    CHECK(b.size() == 2);
}

TEST_CASE("BST remove node with one child") {
    dsa::BST<int> b;
    // 30 only has a left child (20). Removing 30 should pull 20 up.
    int vs[] = {50,30,20};
    for (int v : vs) b.insert(v);
    CHECK(b.remove(30));
    CHECK_FALSE(b.contains(30));
    CHECK(b.contains(20));
    CHECK(b.size() == 2);
}

TEST_CASE("BST remove node with two children") {
    dsa::BST<int> b;
    int vs[] = {50,30,70,20,40,60,80};
    for (int v : vs) b.insert(v);
    // 30 has two children (20, 40). Removal must use the inorder successor.
    CHECK(b.remove(30));
    CHECK_FALSE(b.contains(30));
    // After removal, the remaining 6 keys still come out in sorted order.
    int out[6];
    b.inorder(out);
    int expected[6] = {20,40,50,60,70,80};
    for (int i = 0; i < 6; ++i) CHECK(out[i] == expected[i]);
}

TEST_CASE("BST remove root") {
    dsa::BST<int> b;
    int vs[] = {50,30,70};
    for (int v : vs) b.insert(v);
    // Removing the root is a legitimate case and must work correctly.
    CHECK(b.remove(50));
    CHECK_FALSE(b.contains(50));
    CHECK(b.size() == 2);
}

TEST_CASE("BST remove returns false if not found") {
    dsa::BST<int> b;
    b.insert(1);
    // 99 is not in the tree, so remove() returns false and size stays the same.
    CHECK_FALSE(b.remove(99));
    CHECK(b.size() == 1);
}
