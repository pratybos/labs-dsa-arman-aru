# labs-dsa-arman-aru

VIKO — Algorithms and Data Structures lab work.
Every data structure / algorithm is written **from scratch** in C++
(no STL containers, raw `new`/`delete`, heavy per-line comments so I can
defend every line to the teacher). Tests use the single-header
[doctest](https://github.com/doctest/doctest) framework.

## How to build & run a week

From inside any `weekNN_*` directory:

```bash
cmake -S . -B build
cmake --build build
./build/weekNN          # demo program (main.cpp)
./build/weekNN_tests    # doctest test suite
```

## Weekly content

| Week | Folder | Topic | What I implemented |
|------|--------|-------|--------------------|
| 01 | `week01_dynamic_array`         | Dynamic Array         | `DynamicArray<T>` — grow-on-push, `push_back`, `pop_back`, `at`, `size`, `capacity` |
| 02 | `week02_stack_queue_deque`     | Stack / Queue / Deque | `Stack<T>` (LIFO on DynamicArray), `Queue<T>` (circular buffer FIFO), `Deque<T>` (two-ended circular buffer) |
| 03 | `week03_linked_list`           | Linked Lists          | `SinglyLinkedList<T>` with manual node memory, plus bonus `DoublyLinkedList<T>` with prev/next pointers |
| 04 | `week04_binary_tree_traversal` | Binary Tree           | `BinaryTree<T>` skeleton, `add_left`/`add_right` by parent lookup, recursive preorder/inorder/postorder, `height`, `contains` |
| 05 | `week05_bst`                   | Binary Search Tree    | `BST<T>` — recursive `insert`, `contains`, `min`, `max`, `height`, inorder (sorted), `remove` (3 cases) |
| 06 | `week06_graphs`                | Graphs                | `Graph<int>` adjacency-list (directed / undirected), BFS using my `Queue`, recursive DFS, full traversals for disconnected graphs |
| 07 | `week07_sorting_basic`         | Basic Sorting         | Bubble sort and Shell sort, with comparison / swap counters for the demo |
| 08 | `week08_quicksort`             | Quicksort             | Quicksort with Lomuto partition (pivot = last element), in-place |
| 09 | `week09_heap`                  | Heap / Heapsort       | Max-`Heap` on top of `DynamicArray` (sift up / sift down), and heap sort |
| 10 | `week10_hash_table`            | Hash Table            | `HashTable` (int → int) with `key % capacity` hashing and separate chaining (per-bucket linked lists), handles negative keys |

## Repo conventions

- One folder per week, self-contained (its own `CMakeLists.txt` and copy of
  `doctest.h`).
- Headers live in `include/dsa/`. Where a later week reuses an earlier
  structure (e.g. `DynamicArray` in week 09, `Queue` in week 06), the file
  is copied into that week's `include/dsa/` so the week can be built on
  its own.
- Each week is delivered in ~4–6 small commits following the same flow:
  *scaffold → implement → demo (`main.cpp`) → tests (`tests.cpp`)*.
- No STL containers; raw pointers and manual memory management.
- Comments explain the *why* line by line for in-class defense.
