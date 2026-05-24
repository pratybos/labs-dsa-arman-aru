// main.cpp — Week 06 demo: Graph BFS / DFS
//
// Graph (undirected, 6 vertices):
//   0 - 1
//   0 - 2
//   1 - 3
//   2 - 4
//   3 - 5
#include <iostream>
#include "dsa/Graph.hpp"

// Visit callback: just prints the vertex id followed by a space.
static void printVisit(int v) {
    std::cout << v << " ";
}

int main() {
    // Undirected graph with 6 vertices (0..5).
    dsa::Graph g(6, /*directed=*/false);
    // Add the 5 edges shown in the diagram.
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    g.add_edge(2, 4);
    g.add_edge(3, 5);

    // Run BFS starting at vertex 0 and print every visited vertex.
    std::cout << "BFS from 0: ";
    g.bfs(0, printVisit);
    // Then run DFS, also from vertex 0.
    std::cout << "\nDFS from 0: ";
    g.dfs(0, printVisit);
    std::cout << "\n";
    return 0;
}
