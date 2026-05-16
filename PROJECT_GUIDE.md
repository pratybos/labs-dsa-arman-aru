# DSA Lab Project Guide (Personal — for Claude + me)

This file is my permanent project context. Whenever I start a new chat with Claude, I point it here and just say *"do week N"* — Claude reads this and already knows how I work.

---

## Who I am

- **Name:** Abu Salek Arman
- **Email (git + GitHub):** abusalekarman@gmail.com
- **GitHub username:** `arman-aru`
- **University:** Vilniaus Kolegija (VIKO) — 2nd semester
- **Course:** Algorithms and Data Structures
- **Skill level:** 1st-year university student. **Not a pro coder.** I need beginner-friendly explanations and code I can defend in front of my teacher.

## My repo

- **GitHub URL:** `git@github.com:pratybos/labs-dsa-arman-aru.git`
- **Local path:** `/Users/arman88/Desktop/2nd Semester/Algorithms and Data Structures/labs-dsa-arman-aru-main`
- **Auth:** SSH key already on GitHub (`~/.ssh/id_ed25519`)
- **Git identity is already configured globally**
- **CMake:** installed at `/Applications/CMake.app/Contents/bin/cmake`, on PATH via `~/.zshrc`

---

## How the course is structured

10 weekly labs + a final project + an exam.
Final grade = average of 10 labs + project + exam.

Lab folder names follow the pattern `weekNN_<topic>/` inside the repo root.

| Week | Topic |
|------|-------|
| 01 | DynamicArray (C++) |
| 02 | Stack, Queue, Deque |
| 03 | Linked Lists (singly / doubly) |
| 04 | Recursion |
| 05 | Binary Search Tree (BST) |
| 06 | Graphs |
| 07 | Sorting algorithms |
| 08 | Queues (advanced / priority?) |
| 09 | Heap |
| 10 | Hash tables |

Each lab page on Moodle has the full requirements. I will paste the screenshots of the lab page when I start each week — Claude reads them and follows the rules.

---

## Hard rules from the teacher (apply to EVERY week)

1. **Language:** C++
2. **Type:** Console application
3. **No STL containers inside my implementations** — no `std::vector`, `std::list`, `std::deque`, `std::stack`, `std::queue`, `std::set`, `std::map`, etc.
   - Headers like `<iostream>`, `<stdexcept>`, `<cstddef>` are OK.
4. **Use raw memory** (`new`, `delete`, `new[]`, `delete[]`) — I have to manage memory myself.
5. **Each week is its own folder** with this structure:
   ```
   weekNN_<topic>/
     CMakeLists.txt
     main.cpp
     tests.cpp
     include/
       doctest.h
       dsa/
         <DataStructure>.hpp
   ```
6. **Doctest** lives in `weekNN_<topic>/include/doctest.h` (NOT in dsa/).
7. **Template classes** keep declarations + definitions in the **same .hpp** (templates can't be in .cpp).
8. **Builds with CMake:**
   ```bash
   cd weekNN_<topic>
   cmake -S . -B build
   cmake --build build
   ./build/weekNN_tests   # all doctest tests must pass
   ./build/weekNN         # demo program
   ```
9. **One repo for the whole semester.** Don't overwrite previous weeks — add a new folder each week.
10. **Project (the big one) uses my own implementations from the labs, not STL.**

---

## What "10/10 grade" looks like (grading criteria)

The lab page lists weights that sum to 100%:

| Criterion | Weight |
|---|---|
| Correct use of own data structures | 30% |
| Correct algorithms and logic | 30% |
| Code structure and clarity | 20% |
| Time complexity explanation | 10% |
| README and build instructions | 10% |

Translation: tests passing + clean code + a few sentences about Big-O + a small README per week = 10/10.

---

## How I want Claude to write code FOR ME

These are my locked-in preferences — every week, no exceptions:

- **Comments are mandatory** on basically every meaningful line. I have to be able to read each line out loud to my teacher and explain it.
- Comments should sound **like a human student wrote them**, not like AI. Casual, first-person ("I do this because...", "Here I check if..."), short sentences.
- **No fancy patterns I don't understand.** No move semantics, no iterators I can't explain, no SFINAE, no concepts. Keep it old-school: pointers, loops, simple recursion.
- **Header comment block at the top** of every file explaining what the file does, in simple words.
- **Method-level comment** above every function explaining what it does, the parameters, what it returns, what it throws, and the time complexity if relevant.
- **Variable names** must be readable: `data_`, `size_`, `capacity_` not `d`, `s`, `c`.
- **Tests:** never modify `tests.cpp` — those are the teacher's tests. My code must pass them.
- **Demo `main.cpp`:** print every operation so the teacher can SEE the data structure working live. Use a small `printArray` / `printList` helper that shows the state.

---

## Commit strategy (very important — teacher requires 15–20 commits per week)

For each week:

1. Start from the empty starter the teacher provides (already in the repo or via Classroom).
2. Make **one commit per implemented function**, plus a few for setup / demo / readme.
3. Aim for **18–21 commits per week**.
4. Commit messages format: `weekNN: <short description>` — lowercase, present tense, specific.
   - ✅ `week02: implement Stack push() with capacity doubling`
   - ❌ `update code`, `more changes`, `finished`
5. Never amend or force-push. Always new commits.
6. Push at the end with `git push`.

### Typical 20-commit shape

1. Add the implementation section header comment in the hpp
2. Improve the top doc comment + member field comments
3. Constructor
4. Destructor
5. Each public method, one commit per method
6. (If template) const overloads as separate commits
7. Helper / private methods
8. main.cpp: skeleton with the include
9. main.cpp: print helper
10. main.cpp: each demo block as its own commit
11. README.md for the week
12. .gitignore tweak (if needed)

### Workflow Claude follows when I say "do week N"

1. Read the lab requirement screenshots I paste.
2. Verify the starter folder exists in my repo. If not, fetch it from `origin/main` or guide me to clone the new starter.
3. Save the planned final code to `/tmp/`.
4. **Reset the working files back to the starter state** (so commits build up incrementally, not in one big lump).
5. Make ~20 small commits, each adding one piece.
6. Verify with compile + test run (`clang++ -std=c++20 -I include tests.cpp -o /tmp/test && /tmp/test`) before pushing.
7. Push when everything is green.
8. Tell me the 4 commands to demo to the teacher.

---

## Things I do NOT want

- ❌ Copying my friends' code, or letting them copy mine. Each person writes their own. (Sajedul + Mushfiq have their own starter folders at `../sajedul-islam-dsa/` and `../mushfiq-dsa/` with the teacher's starter only — they implement themselves.)
- ❌ Submitting the `build/` folder to git. `.gitignore` excludes it.
- ❌ Code I can't explain. If Claude writes something fancy, replace with the simple version.
- ❌ One giant commit at the end of the week.
- ❌ Skipping the demo `main.cpp` — the teacher likes seeing it run.

---

## Useful command cheatsheet

```bash
# Build + test
cd weekNN_<topic>
cmake -S . -B build
cmake --build build
./build/weekNN_tests
./build/weekNN

# Quick compile without cmake (for fast iteration)
clang++ -std=c++20 -Iinclude tests.cpp -o /tmp/t && /tmp/t

# Git basics
git status
git add <file>
git commit -m "weekNN: <message>"
git push

# See what I've done this week
git log --oneline

# Compare my work to what's on GitHub
git log --oneline origin/main..HEAD
```

---

## Where the teacher's general info lives

(From the course front page on Moodle.)

- **Final Evaluation** = Practice (avg of 10 labs) + Project + Exam
- **Teacher:** m.gzegozevskis@eif.viko.lt
- **Classroom:** 420A or 208
- **MS Teams:** m.gzegozevskis
- **IDE:** CLion (free with `.surname@stud.viko.lt` email) or Visual Studio Community. I use **VS Code** which is fine.
- **References:**
  - Problem Solving with Algorithms and Data Structures (with C++)
  - Bjarne Stroustrup — The C++ Programming Language
  - https://en.cppreference.com/w/cpp/algorithm/binary_search

---

## My current state

- ✅ Week 01 — DynamicArray — DONE (pushed, 21 commits, 10/10 tests passing)
- ⬜ Week 02 — Stack/Queue/Deque
- ⬜ Week 03 — Linked Lists
- ⬜ Week 04 — Recursion
- ⬜ Week 05 — BST
- ⬜ Week 06 — Graphs
- ⬜ Week 07 — Sorting
- ⬜ Week 08 — Queues (advanced)
- ⬜ Week 09 — Heap
- ⬜ Week 10 — Hash tables
- ⬜ Project — uses my structures from above

When I'm ready for week 2, I'll paste the lab screenshots and say *"do week 2 the same way"*. Claude reads this file + my screenshots and just goes.
