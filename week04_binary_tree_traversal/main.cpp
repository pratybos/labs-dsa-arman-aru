// main.cpp — Week 04 demo: BinaryTree traversals
// I build a small tree manually and print each traversal.
//
//          1
//         / \
//        2   3
//       / \   \
//      4   5   6
//
// Pre-order  : 1 2 4 5 3 6
// In-order   : 4 2 5 1 3 6
// Post-order : 4 5 2 6 3 1
// Height     : 3
// contains(5): yes, contains(99): no

#include <iostream>
#include "dsa/BinaryTree.hpp"

int main() {
    // Create an empty integer binary tree.
    dsa::BinaryTree<int> t;
    // Build the tree node by node, matching the diagram in the header comment.
    t.set_root(1);
    t.add_left(1, 2);
    t.add_right(1, 3);
    t.add_left(2, 4);
    t.add_right(2, 5);
    t.add_right(3, 6);

    // Buffer to receive traversal output. Holds up to 10 ints — more than enough.
    int buf[10];

    // Pre-order traversal.
    std::cout << "Pre-order : ";
    t.preorder(buf);
    // Print exactly size() values from buf.
    for (std::size_t i = 0; i < t.size(); ++i) std::cout << buf[i] << " ";
    std::cout << "\n";

    // In-order traversal.
    std::cout << "In-order  : ";
    t.inorder(buf);
    for (std::size_t i = 0; i < t.size(); ++i) std::cout << buf[i] << " ";
    std::cout << "\n";

    // Post-order traversal.
    std::cout << "Post-order: ";
    t.postorder(buf);
    for (std::size_t i = 0; i < t.size(); ++i) std::cout << buf[i] << " ";
    std::cout << "\n";

    // Show the height and a couple of contains() checks on the same line.
    std::cout << "height=" << t.height()
              << " contains(5)=" << t.contains(5)
              << " contains(99)=" << t.contains(99) << "\n";
    return 0;
}
