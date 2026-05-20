// Generate the main() function automatically from doctest.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dsa/BinaryTree.hpp"
#include <stdexcept>

// Helper that builds this specific tree for many tests below:
//          1
//         / \
//        2   3
//       / \   \
//      4   5   6
static void buildTree(dsa::BinaryTree<int>& t) {
    // Create the root with value 1.
    t.set_root(1);
    // Attach 2 as the left child of 1.
    t.add_left(1, 2);
    // Attach 3 as the right child of 1.
    t.add_right(1, 3);
    // Attach 4 as left child of 2.
    t.add_left(2, 4);
    // Attach 5 as right child of 2.
    t.add_right(2, 5);
    // Attach 6 as right child of 3.
    t.add_right(3, 6);
}

TEST_CASE("empty tree") {
    // A tree with no root must be empty, have size 0 and height 0.
    dsa::BinaryTree<int> t;
    CHECK(t.empty());
    CHECK(t.size() == 0);
    CHECK(t.height() == 0);
    // Nothing can be inside, so contains() must return false.
    CHECK_FALSE(t.contains(1));
}

TEST_CASE("set_root twice throws") {
    // Setting the root once is fine.
    dsa::BinaryTree<int> t;
    t.set_root(1);
    // Setting it again must throw a logic_error (root already exists).
    CHECK_THROWS_AS(t.set_root(2), std::logic_error);
}

TEST_CASE("add_left on missing parent throws") {
    // I create a root, then try to add a child under a parent that does not exist.
    dsa::BinaryTree<int> t;
    t.set_root(1);
    // Parent 99 is not in the tree -> std::out_of_range.
    CHECK_THROWS_AS(t.add_left(99, 2), std::out_of_range);
}

TEST_CASE("add_left twice throws") {
    // I can only set ONE left child per node. The second call must throw.
    dsa::BinaryTree<int> t;
    t.set_root(1);
    t.add_left(1, 2);
    CHECK_THROWS_AS(t.add_left(1, 3), std::logic_error);
}

TEST_CASE("size + height") {
    // Build the standard test tree (6 nodes, height 3).
    dsa::BinaryTree<int> t;
    buildTree(t);
    CHECK(t.size() == 6);
    CHECK(t.height() == 3);
}

TEST_CASE("contains") {
    dsa::BinaryTree<int> t;
    buildTree(t);
    // Every value I inserted must be found.
    CHECK(t.contains(1));
    CHECK(t.contains(4));
    CHECK(t.contains(6));
    // A value that was never inserted must NOT be found.
    CHECK_FALSE(t.contains(99));
}

TEST_CASE("preorder") {
    dsa::BinaryTree<int> t; buildTree(t);
    // Buffer for the 6 values (in pre-order: root, left subtree, right subtree).
    int out[6];
    t.preorder(out);
    // The classic pre-order of this tree.
    int expected[6] = {1,2,4,5,3,6};
    // Compare element by element.
    for (int i = 0; i < 6; ++i) CHECK(out[i] == expected[i]);
}

TEST_CASE("inorder") {
    dsa::BinaryTree<int> t; buildTree(t);
    int out[6];
    // In-order: left subtree, node, right subtree.
    t.inorder(out);
    int expected[6] = {4,2,5,1,3,6};
    for (int i = 0; i < 6; ++i) CHECK(out[i] == expected[i]);
}

TEST_CASE("postorder") {
    dsa::BinaryTree<int> t; buildTree(t);
    int out[6];
    // Post-order: left subtree, right subtree, node.
    t.postorder(out);
    int expected[6] = {4,5,2,6,3,1};
    for (int i = 0; i < 6; ++i) CHECK(out[i] == expected[i]);
}

TEST_CASE("clear leaves empty tree") {
    dsa::BinaryTree<int> t; buildTree(t);
    // clear() must free every node and reset size back to 0.
    t.clear();
    CHECK(t.empty());
    CHECK(t.size() == 0);
}
