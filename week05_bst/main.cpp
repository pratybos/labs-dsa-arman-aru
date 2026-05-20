// main.cpp — Week 05 demo: BST
#include <iostream>
#include "dsa/BST.hpp"

int main() {
    // Create an empty BST for ints.
    dsa::BST<int> bst;
    // Insert several keys including one duplicate (30) that must be ignored.
    int values[] = {50, 30, 70, 20, 40, 60, 80, 30 /* dup ignored */};
    for (int v : values) bst.insert(v);

    // Print quick stats about the resulting tree.
    std::cout << "size=" << bst.size()
              << " min=" << bst.min()
              << " max=" << bst.max()
              << " height=" << bst.height() << "\n";

    // Buffer big enough for the 7 unique keys we kept.
    int out[8];
    // In-order traversal of a BST -> sorted output.
    bst.inorder(out);
    std::cout << "inorder (sorted): ";
    for (std::size_t i = 0; i < bst.size(); ++i) std::cout << out[i] << " ";
    std::cout << "\n";

    // Demonstrate contains() for an existing and a missing key.
    std::cout << "contains(40)=" << bst.contains(40)
              << " contains(99)=" << bst.contains(99) << "\n";

    // Exercise the three remove cases: two-children, leaf, then a third remove.
    bst.remove(30);
    bst.remove(80);
    bst.remove(70);
    std::cout << "after remove 30, 80, 70 -> size=" << bst.size() << " inorder: ";
    bst.inorder(out);
    for (std::size_t i = 0; i < bst.size(); ++i) std::cout << out[i] << " ";
    std::cout << "\n";
    return 0;
}
