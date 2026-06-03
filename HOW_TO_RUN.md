# How to Run — Weeks 01–10 and the Final Project

This repository contains my weekly DSA labs (`week01` … `week10`) and the final
**Algorithm Playground** project (`project/`). Every folder builds the same way
with **CMake**. This guide explains how to build and run each one.

## What you need

- A C++ compiler (g++, clang, or MSVC)
- **CMake** version 3.16 or newer

Check they are installed:

```bash
cmake --version
g++ --version      # or: clang++ --version
```

---

## The 3-step pattern (works for EVERY folder)

Every week folder and the project use the exact same three commands. Only the
folder name and the executable name change.

```bash
cd <folder>            # 1. go into the week or project folder
cmake -S . -B build    # 2. configure (creates a build/ folder)
cmake --build build    # 3. compile
```

Then run the program or the tests from inside that folder:

```bash
./build/<executable>          # Linux / macOS
build\<executable>.exe        # Windows
```

> **Tip:** After the first build you only need to re-run step 3
> (`cmake --build build`) when you change the code, then run the executable
> again. To start completely fresh, delete the build folder first:
> `rm -rf build` (Windows: `rmdir /s /q build`).

---

## Weeks 01–10 — exact commands

Each week produces two executables: the **demo** program (`weekNN`) and the
**tests** (`weekNN_tests`). Run the tests to confirm everything passes.

### Week 01 — DynamicArray
```bash
cd week01_dynamic_array
cmake -S . -B build
cmake --build build
./build/week01            # demo
./build/week01_tests      # tests
```

### Week 02 — Stack, Queue, Deque
```bash
cd week02_stack_queue_deque
cmake -S . -B build
cmake --build build
./build/week02
./build/week02_tests
```

### Week 03 — Linked List
```bash
cd week03_linked_list
cmake -S . -B build
cmake --build build
./build/week03
./build/week03_tests
```

### Week 04 — Binary Tree Traversals
```bash
cd week04_binary_tree_traversal
cmake -S . -B build
cmake --build build
./build/week04
./build/week04_tests
```

### Week 05 — Binary Search Tree (BST)
```bash
cd week05_bst
cmake -S . -B build
cmake --build build
./build/week05
./build/week05_tests
```

### Week 06 — Graphs (BFS & DFS)
```bash
cd week06_graphs
cmake -S . -B build
cmake --build build
./build/week06
./build/week06_tests
```

### Week 07 — Sorting (Bubble, Shell)
```bash
cd week07_sorting_basic
cmake -S . -B build
cmake --build build
./build/week07
./build/week07_tests
```

### Week 08 — Quicksort
```bash
cd week08_quicksort
cmake -S . -B build
cmake --build build
./build/week08
./build/week08_tests
```

### Week 09 — Heap & Heapsort
```bash
cd week09_heap
cmake -S . -B build
cmake --build build
./build/week09
./build/week09_tests
```

### Week 10 — Hash Table
```bash
cd week10_hash_table
cmake -S . -B build
cmake --build build
./build/week10
./build/week10_tests
```

> On **Windows**, replace `./build/week01` with `build\week01.exe`
> and `./build/week01_tests` with `build\week01_tests.exe`, and so on.

---

## Final Project — Algorithm Playground

The project is a single **menu-driven** console app that reuses my own lab
data structures (no STL). It has no separate test executable.

```bash
cd project
cmake -S . -B build
cmake --build build
./build/playground            # Windows: build\playground.exe
```

When it starts you will see the menu:

```
========= Algorithm Playground =========
 1. DynamicArray  (push/insert/erase)
 2. Stack         (reverse a word)
 3. Queue         (waiting line)
 4. Linked List   (find/reverse)
 5. BST           (sorted insert/search)
 6. Sort numbers  (Quicksort)
 7. Traverse graph(BFS & DFS)
 0. Exit
========================================
Choose an option:
```

Type a number and press **Enter** to run that demo. Type `0` to quit.
See [project/README.md](project/README.md) for the full description and the
time-complexity discussion.

---

## Quick troubleshooting

| Problem | Fix |
|---|---|
| `cmake: command not found` | Install CMake (`brew install cmake` on macOS). |
| Build fails after editing code | Delete `build/` and rebuild: `rm -rf build` then repeat the 3 steps. |
| `./build/weekNN: No such file` | You are in the wrong folder, or the build step failed — re-run step 3 and read the error. |
| Windows: `./build/...` not working | Use backslashes and `.exe`: `build\weekNN.exe`. |
