// Tell doctest to generate main() for us.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dsa/Graph.hpp"
#include <stdexcept>

// Global capture buffer used by my "visit" callback below.
// BFS/DFS take a function pointer, so I cannot capture state easily — I use
// a plain global array to remember the order vertices were visited in.
static int g_order[64];
// Index of the next free slot in g_order.
static int g_idx = 0;
// The visit callback I pass to bfs()/dfs(). It just records the vertex id.
static void capture(int v) { g_order[g_idx++] = v; }
// Reset helper so each test starts from a clean state.
static void resetCapture() { g_idx = 0; }

TEST_CASE("Graph construction + add_edge") {
    // Make a graph with 5 vertices (ids 0..4).
    dsa::Graph g(5);
    CHECK(g.vertex_count() == 5);
    // Adding edges between valid ids is fine.
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    // Adding an edge to a non-existing vertex must throw.
    CHECK_THROWS_AS(g.add_edge(0, 99), std::out_of_range);
    CHECK_THROWS_AS(g.add_edge(-1, 0), std::out_of_range);
}

TEST_CASE("Undirected BFS visits all reachable") {
    // Tree-shaped undirected graph with 6 vertices and 5 edges.
    dsa::Graph g(6);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    g.add_edge(2, 4);
    g.add_edge(3, 5);

    // Reset before each traversal.
    resetCapture();
    g.bfs(0, capture);
    // BFS from 0 should reach every one of the 6 vertices.
    CHECK(g_idx == 6);
    // The very first vertex BFS visits must be the start (0).
    CHECK(g_order[0] == 0);
}

TEST_CASE("Undirected DFS visits all reachable") {
    // Same graph as above, but now testing DFS.
    dsa::Graph g(6);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    g.add_edge(2, 4);
    g.add_edge(3, 5);

    resetCapture();
    g.dfs(0, capture);
    // DFS should also reach all 6 vertices.
    CHECK(g_idx == 6);
    // DFS starts by visiting the source first.
    CHECK(g_order[0] == 0);
}

TEST_CASE("Cycle does not cause infinite loop") {
    // Triangle: 0-1-2-0. If "visited" tracking is wrong we would loop forever.
    dsa::Graph g(3);
    g.add_edge(0,1); g.add_edge(1,2); g.add_edge(2,0);
    // BFS visits each vertex exactly once -> g_idx must end at 3.
    resetCapture();
    g.bfs(0, capture);
    CHECK(g_idx == 3);
    // DFS does the same.
    resetCapture();
    g.dfs(0, capture);
    CHECK(g_idx == 3);
}

TEST_CASE("Disconnected graph: bfs_all / dfs_all visit every vertex") {
    // Graph has 6 vertices and two small components plus two isolated nodes.
    dsa::Graph g(6);
    g.add_edge(0,1);    // component {0,1}
    g.add_edge(2,3);    // component {2,3}
    // Vertices 4 and 5 are completely alone.

    // bfs_all walks ALL vertices, restarting at each unvisited one.
    resetCapture();
    g.bfs_all(capture);
    CHECK(g_idx == 6);

    // dfs_all does the same.
    resetCapture();
    g.dfs_all(capture);
    CHECK(g_idx == 6);
}

TEST_CASE("Directed graph respects direction") {
    // 3 vertices with edges 0->1 and 1->2. There is NO edge back from 2.
    dsa::Graph g(3, /*directed=*/true);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    // From 2 you cannot move anywhere, so BFS visits only the start node.
    resetCapture();
    g.bfs(2, capture);
    CHECK(g_idx == 1);
    CHECK(g_order[0] == 2);
}
