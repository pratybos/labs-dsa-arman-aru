# DSA Lab — Defence Q&A (Bangla, 10 Weeks)

> এই ফাইল পুরোটাই বাংলায়। প্রতিটা সপ্তাহের কোডের পেছনে কী চিন্তা আছে, শিক্ষক
> কী জিজ্ঞেস করতে পারেন, আর কীভাবে উত্তর দিতে হবে — সব একদম সহজ ভাষায়,
> উদাহরণ সহ। ভাবো তুমি একদম নতুন, আমি ছোট বাচ্চার মতো করে বুঝাচ্ছি।

---

## 🔰 শুরু করার আগে — কিছু কমন কথা

**প্রশ্ন: STL কেন ব্যবহার করো নাই?**
উত্তর: ল্যাবের নিয়ম — সব ডেটা স্ট্রাকচার নিজে হাতে বানাতে হবে। `std::vector`,
`std::queue`, এগুলো ব্যবহার করলে আসল শেখা হয় না। তাই raw pointer
(`new` / `delete`) দিয়ে নিজে মেমোরি ম্যানেজ করেছি।

**প্রশ্ন: doctest কী?**
উত্তর: একটা single-header টেস্টিং লাইব্রেরি। শুধু একটা `.h` ফাইল include
করলেই হয়, আলাদা install লাগে না। `CHECK(...)`, `REQUIRE(...)` দিয়ে
assertion লেখা যায়।

**প্রশ্ন: Time complexity মানে কী?**
উত্তর: ইনপুট সাইজ `n` বাড়লে অপারেশনের সময় কত দ্রুত বাড়ে — সেটা।
- `O(1)` = সবসময় এক সময় (যেমন array index access)
- `O(n)` = ইনপুটের সাথে সমান হারে বাড়ে (যেমন একবার লুপ ঘুরা)
- `O(n²)` = nested লুপ
- `O(log n)` = প্রতিবার অর্ধেক করে কমে (যেমন BST search balanced হলে)

---

## 📅 Week 01 — Dynamic Array

### কী বানিয়েছি
`DynamicArray<T>` — এমন একটা অ্যারে যেটার সাইজ নিজে নিজে বড় হয়।

### প্রশ্ন ১: Dynamic array আর সাধারণ array এর পার্থক্য কী?
সাধারণ array এর সাইজ fix — `int a[10];` বানালে ১০টাই থাকবে। Dynamic array
এ জায়গা শেষ হয়ে গেলে নিজেই নতুন বড় জায়গা বানিয়ে পুরোনো ডেটা copy করে নেয়।

### প্রশ্ন ২: capacity আর size এর পার্থক্য?
- **size** = এখন কয়টা ভ্যালু আছে।
- **capacity** = মেমোরিতে কয়টা রাখার জায়গা আছে।

উদাহরণ: capacity = 8, size = 3 মানে ৮টার জায়গা আছে কিন্তু ৩টা ভরা।

### প্রশ্ন ৩: capacity শেষ হলে কী হয়?
আমি নতুন একটা অ্যারে বানাই **দ্বিগুণ সাইজের** (`new T[capacity * 2]`), পুরোনো
সব ভ্যালু copy করি, পুরোনোটা `delete[]` করি, পয়েন্টার update করি।

### প্রশ্ন ৪: দ্বিগুণ কেন? ১+১ করো না কেন?
যদি প্রতিবার ১ করে বাড়াই, তাহলে n বার push করতে O(n²) সময় লাগবে।
দ্বিগুণ করলে amortized O(1) হয় — গড়ে প্রতিটা push প্রায় constant time।

### প্রশ্ন ৫: destructor এ কী করো?
`delete[] data_;` — heap এ যেই memory নিয়েছিলাম `new T[...]` দিয়ে সেটা
ফেরত দেই, না হলে memory leak হবে।

**উদাহরণ:**
```
push 1 → [1]              size=1, cap=1
push 2 → [1,2]            size=2, cap=2  (grow)
push 3 → [1,2,3,_]        size=3, cap=4  (grow)
push 4 → [1,2,3,4]        size=4, cap=4
push 5 → [1,2,3,4,5,_,_,_] size=5, cap=8 (grow)
```

---

## 📅 Week 02 — Stack, Queue, Deque

### কী বানিয়েছি
- **Stack** — LIFO (Last In First Out), আমার DynamicArray এর উপর বানানো।
- **Queue** — FIFO (First In First Out), circular buffer দিয়ে।
- **Deque** — দু দিক থেকেই push/pop করা যায়, circular buffer দিয়ে।

### প্রশ্ন ১: Stack এর real life উদাহরণ দাও।
প্লেটের stack — উপরে রাখো, উপর থেকেই নাও। অথবা browser এর Back button —
শেষ ভিজিট করা পেজ আগে আসে।

### প্রশ্ন ২: Queue এর real life উদাহরণ?
দোকানে লাইন — যে আগে আসছে সে আগে service পাবে। অথবা printer queue।

### প্রশ্ন ৩: Circular buffer কী? কেন দরকার?
এটা একটা fix-size array, কিন্তু আমরা **wrap-around** করি — শেষে গেলে আবার
শুরু থেকে। দুইটা index রাখি: `front` আর `back`। নাহলে প্রতি `dequeue` এর
পর সব element shift করতে হতো — O(n) — যা slow।

**উদাহরণ (capacity=5):**
```
enqueue 1,2,3 → [1,2,3,_,_]  front=0, back=3
dequeue       → [_,2,3,_,_]  front=1, back=3
enqueue 4,5,6 → [6,2,3,4,5]  front=1, back=1  ← 6 wrap around করছে!
```

### প্রশ্ন ৪: Deque কেন আলাদা?
Queue শুধু পেছনে add, সামনে remove। Deque দুদিকেই — `push_front`,
`push_back`, `pop_front`, `pop_back`। তাই circular buffer এ `front`
কমাতেও হয় কখনো কখনো (wrap করে শেষের দিকে চলে যায়)।

### প্রশ্ন ৫: Stack কেন DynamicArray এর উপরে বানালে?
Stack এর `push` = array এর `push_back`, `pop` = `pop_back`। দুটোই
amortized O(1)। নতুন করে কোড লেখার দরকার নেই — code reuse।

---

## 📅 Week 03 — Linked List

### কী বানিয়েছি
- **SinglyLinkedList** — প্রতিটা node এ `data` আর `next` pointer।
- **DoublyLinkedList** (bonus) — `data`, `next`, `prev` — দুদিকে চলা যায়।

### প্রশ্ন ১: Linked list আর array এর পার্থক্য?
| | Array | Linked List |
|---|---|---|
| Memory | একসাথে (contiguous) | ছড়ানো (heap এ যেখানে যেখানে) |
| Index access | O(1) | O(n) — head থেকে গণতে হয় |
| Insert at front | O(n) shift | O(1) |
| Size | fix (or grow) | যত খুশি grow |

### প্রশ্ন ২: Node বানাও কীভাবে?
```cpp
struct Node {
    T data;
    Node* next;
};
```
`new Node{value, nullptr}` দিয়ে heap এ বানাই। শেষে destructor এ একে একে
`delete` করি।

### প্রশ্ন ৩: SLL এর শেষে insert করতে কত সময়?
যদি শুধু `head` রাখি — O(n), পুরো list ঘুরতে হয়।
যদি `tail` pointer ও রাখি — O(1)।

### প্রশ্ন ৪: DLL এর সুবিধা কী?
Backward traversal করা যায়। কোনো node এর সামনে/পেছনে insert/delete করতে
পুরো list ঘুরতে হয় না।

### প্রশ্ন ৫: কোনো node delete করার সময় কী খেয়াল রাখো?
১. তার আগের node এর `next` কে এই node এর `next` এ point করাও।
২. তারপর `delete` করো। উল্টো করলে dangling pointer হবে।

**উদাহরণ (SLL মাঝখান থেকে delete):**
```
আগে:  A → B → C → D
B এর next = C, B delete করতে হলে:
A->next = B->next  (অর্থাৎ C)
delete B
পরে:  A → C → D
```

---

## 📅 Week 04 — Binary Tree (Traversal)

### কী বানিয়েছি
`BinaryTree<T>` — প্রতিটা node এর সর্বোচ্চ ২টা child। তিন রকম traversal +
height + contains।

### প্রশ্ন ১: Binary tree আর BST এর পার্থক্য?
Binary tree এ child placement এর কোনো নিয়ম নেই। BST এ left < parent < right।

### প্রশ্ন ২: Preorder, Inorder, Postorder মানে কী?
- **Preorder**: Root → Left → Right
- **Inorder**: Left → Root → Right
- **Postorder**: Left → Right → Root

**উদাহরণ:**
```
        1
       / \
      2   3
     / \
    4   5
```
- Preorder: 1, 2, 4, 5, 3
- Inorder: 4, 2, 5, 1, 3
- Postorder: 4, 5, 2, 3, 1

### প্রশ্ন ৩: Recursive কেন?
Tree নিজেই recursive structure — প্রতিটা subtree আবার একটা tree। তাই
recursion দিয়ে কোড ছোট আর সহজ হয়।

### প্রশ্ন ৪: Height কীভাবে বের করো?
```
height(node):
   যদি node == nullptr → return -1 (অথবা 0, convention অনুযায়ী)
   return 1 + max(height(left), height(right))
```

### প্রশ্ন ৫: add_left/add_right কীভাবে কাজ করে?
আমি parent value খুঁজি (recursive search), পেলে সেই node এর left/right এ
নতুন node বসাই। যদি ওই side এ আগে থেকে কিছু থাকে → error / skip।

---

## 📅 Week 05 — Binary Search Tree (BST)

### কী বানিয়েছি
`BST<T>` — insert, contains, min, max, height, inorder (sorted output), remove।

### প্রশ্ন ১: BST এর rule কী?
প্রতিটা node এর জন্য: **বাঁ পাশের সব node < node < ডান পাশের সব node**।

### প্রশ্ন ২: Insert কীভাবে?
Root থেকে শুরু, value ছোট হলে left, বড় হলে right এ যাই, যেখানে `nullptr`
পাই সেখানে নতুন node বসাই। Duplicate ignore করি।

**উদাহরণ:** insert 5,3,7,1,4 →
```
        5
       / \
      3   7
     / \
    1   4
```

### প্রশ্ন ৩: Inorder traversal করলে কী পাবো?
**Sorted ascending order!** এটাই BST এর সবচেয়ে সুন্দর property।
উপরের tree → 1, 3, 4, 5, 7।

### প্রশ্ন ৪: Min/Max কীভাবে বের করো?
- **Min**: বাঁ দিকে যত যাওয়া যায়।
- **Max**: ডান দিকে যত যাওয়া যায়।

### প্রশ্ন ৫: Remove এর ৩টা case কী কী?
১. **Leaf** (কোনো child নেই) → সরাসরি delete।
২. **এক child** → child কে parent এর সাথে যুক্ত করো, node delete।
৩. **দুই child** → ডান subtree এর min খুঁজো (inorder successor), তার value
   কপি করো, তারপর সেই successor কে remove করো।

### প্রশ্ন ৬: BST এর search complexity?
- Balanced হলে: O(log n)
- Worst case (chain হয়ে গেলে, যেমন sorted order এ insert): O(n)

---

## 📅 Week 06 — Graphs

### কী বানিয়েছি
`Graph<int>` — adjacency list, directed/undirected option, BFS (Queue
দিয়ে), DFS (recursive)।

### প্রশ্ন ১: Adjacency list আর adjacency matrix এর পার্থক্য?
- **Matrix**: `V × V` 2D array, `m[i][j]=1` মানে edge আছে। Memory O(V²)।
- **List**: প্রতিটা vertex এর জন্য একটা list — শুধু neighbors রাখি।
  Memory O(V + E)। Sparse graph এ অনেক efficient।

আমি list use করেছি কারণ memory সাশ্রয়।

### প্রশ্ন ২: Directed আর undirected graph এর পার্থক্য?
- **Directed**: edge এর direction আছে (one-way road)। `add_edge(u,v)` শুধু
  `u → v` যোগ করে।
- **Undirected**: দু দিকেই যাওয়া যায়। `add_edge(u,v)` দুটোই যোগ করে: `u→v`
  আর `v→u`।

### প্রশ্ন ৩: BFS কী? কীভাবে কাজ করে?
**Breadth First Search** — শুরু node থেকে level-by-level ঘুরি।
- একটা **Queue** আর `visited[]` array লাগে।
- Start node enqueue + visited mark।
- Loop: dequeue করো → তার unvisited neighbors enqueue করো।

**উদাহরণ:**
```
1 — 2 — 4
|   |
3 — 5
```
BFS from 1: 1, 2, 3, 4, 5

### প্রশ্ন ৪: DFS কী?
**Depth First Search** — যত গভীরে যাওয়া যায় ততদূর যাই, তারপর backtrack।
আমি recursion দিয়ে করেছি (call stack নিজেই Stack এর কাজ করে)।

উপরের graph এ DFS from 1: 1, 2, 4, 5, 3 (অথবা order ভেদে অন্যরকম)।

### প্রশ্ন ৫: BFS এ Queue, DFS এ Stack — কেন?
BFS এ পুরোনো জিনিস আগে process করতে চাই (FIFO) → Queue।
DFS এ সবশেষ পাওয়া neighbor আগে process করতে চাই (LIFO) → Stack
(recursion এ implicit)।

### প্রশ্ন ৬: Disconnected graph হলে কী করো?
`bfs_all` / `dfs_all` — সব vertex এর উপর loop চালাই, যেটা এখনো `visited`
না সেটা থেকে আবার traversal শুরু করি।

### প্রশ্ন ৭: BFS এর complexity?
O(V + E) — প্রতিটা vertex ১বার, প্রতিটা edge ১বার দেখা হয়।

---

## 📅 Week 07 — Basic Sorting (Bubble + Shell)

### কী বানিয়েছি
Bubble sort আর Shell sort, comparison/swap counter সহ।

### প্রশ্ন ১: Bubble sort কীভাবে কাজ করে?
পাশাপাশি দুটো element compare করি, ভুল order এ থাকলে swap। বারবার পুরো
array পার হই। বড় element প্রতি pass এ "বুদবুদের" মতো শেষে চলে যায়।

**উদাহরণ:** [5, 3, 4, 1]
```
Pass 1: 3,5,4,1 → 3,4,5,1 → 3,4,1,5
Pass 2: 3,4,1,5 → 3,1,4,5
Pass 3: 1,3,4,5
```

### প্রশ্ন ২: Bubble sort এর complexity?
- Worst & average: O(n²)
- Best (already sorted, flag optimization দিলে): O(n)
- Stable: হ্যাঁ (equal element এর order বদলায় না)
- In-place: হ্যাঁ

### প্রশ্ন ৩: Shell sort কী?
Insertion sort এর উন্নত version। `gap` দূরে দূরে থাকা element compare ও
swap করি। gap কমতে কমতে ১ এ আসে — তখন এটা সাধারণ insertion sort।

**উদাহরণ** (gap=4, n=8): index 0 আর 4, 1 আর 5, 2 আর 6, 3 আর 7 — এদের
compare/swap। তারপর gap=2, তারপর gap=1।

### প্রশ্ন ৪: Shell sort কেন bubble এর চেয়ে fast?
দূরের element আগেই জায়গায় চলে আসে, তাই শেষে অল্প কাজ বাকি থাকে।
সাধারণত O(n^1.5) এর কাছাকাছি (gap sequence ভেদে)।

### প্রশ্ন ৫: Comparison আর swap কেন count করো?
দুই algorithm এর performance practically compare করার জন্য। বইয়ের theory
+ আমার নিজের measurement মিলে কিনা দেখি।

### প্রশ্ন ৬: Stable sort কী?
যেই sort এ equal value এর relative order রক্ষা হয়। যেমন `[(1,a), (1,b)]`
— sort এর পরও `a` `b` এর আগেই থাকবে। Shell sort stable **না**, Bubble
stable।

---

## 📅 Week 08 — Quicksort

### কী বানিয়েছি
Lomuto partition দিয়ে quicksort। Pivot = last element।

### প্রশ্ন ১: Quicksort এর মূল idea?
**Divide and conquer**:
১. একটা pivot বাছো।
২. Pivot এর ছোট সব বাঁয়ে, বড় সব ডানে রাখো (partition)।
৩. বাঁ আর ডান অংশকে আলাদা ভাবে recursively sort করো।

### প্রশ্ন ২: Lomuto partition কীভাবে কাজ করে?
- Pivot = `arr[high]`।
- `i = low - 1` (এর বামে সব ≤ pivot থাকবে)।
- `j = low → high-1` লুপ:
  - `arr[j] <= pivot` হলে `i++`, `swap(arr[i], arr[j])`।
- শেষে `swap(arr[i+1], arr[high])` — pivot তার final জায়গায়।
- Return `i+1`।

**উদাহরণ:** [3, 1, 4, 1, 5], pivot=5 → সবাই ≤5, swap শেষে 5 যথাস্থানে।

### প্রশ্ন ৩: Quicksort এর complexity?
- Average: **O(n log n)** — array প্রায় অর্ধেক ভাগ হয়।
- Worst: **O(n²)** — pivot সবসময় সবচেয়ে ছোট/বড় হলে (যেমন already sorted
  array তে last-element pivot)।
- Space: O(log n) recursion stack এ।
- In-place: হ্যাঁ। Stable: না।

### প্রশ্ন ৪: Last element pivot কেন? এর ঝুঁকি কী?
Lomuto সবচেয়ে সহজ implementation। ঝুঁকি — sorted/reverse sorted input এ
O(n²)। Random pivot বা median-of-three দিয়ে fix করা যায়।

### প্রশ্ন ৫: Merge sort vs Quicksort?
| | Merge | Quick |
|---|---|---|
| Worst | O(n log n) | O(n²) |
| Space | O(n) extra | O(log n) |
| Stable | হ্যাঁ | না |
| Practical speed | slower (memory copy) | usually faster |

---

## 📅 Week 09 — Heap (Max-Heap + Heap Sort)

### কী বানিয়েছি
Max-heap, DynamicArray এর উপর flat array এ রাখা। Push, pop, heap sort।

### প্রশ্ন ১: Heap কী?
একটা special binary tree যেটা **complete** (একদম last level ছাড়া সব ভরা,
last level বাঁ থেকে ভরা) আর **heap property** মানে — Max-heap এ parent ≥
সব child।

### প্রশ্ন ২: Array তে কীভাবে রাখো?
Index 0 root। কোনো index `i` এর জন্য:
- **parent** = `(i - 1) / 2`
- **left child** = `2*i + 1`
- **right child** = `2*i + 2`

**উদাহরণ:** Array [90, 50, 70, 20, 30, 60] →
```
        90
       /  \
      50   70
     / \   /
    20 30 60
```

### প্রশ্ন ৩: Push কীভাবে?
১. শেষে যোগ করো।
২. **Sift up**: parent এর সাথে compare, বড় হলে swap, উপরের দিকে যাও।
   Root এ পৌঁছালে বা parent বড় হলে থামো।

Complexity: O(log n) — tree height সমান।

### প্রশ্ন ৪: Pop (max remove) কীভাবে?
১. Top (index 0) এর value সংগ্রহ করো — এটাই return হবে।
২. শেষ element কে index 0 তে বসাও, size একটা কমাও।
৩. **Sift down**: দুই child এর মধ্যে বড়টার সাথে compare, যদি ছোট হই তাহলে
   swap, নিচে যাও। যতক্ষণ heap property ঠিক না হয়।

Complexity: O(log n)।

### প্রশ্ন ৫: Heap sort কীভাবে?
১. সব element heap এ push করো (O(n log n))।
২. একে একে pop করো — descending order আসবে।
৩. উল্টে দিলে ascending।
Total: O(n log n)। In-place: হ্যাঁ (যদি input array কেই heap বানাও)।
Stable: না।

### প্রশ্ন ৬: Heap এর ব্যবহার কী?
- **Priority queue** (highest priority আগে process)।
- **Top-K problem**, scheduling, Dijkstra's algorithm।

---

## 📅 Week 10 — Hash Table (Separate Chaining)

### কী বানিয়েছি
`HashTable` (int → int), hash = `key % capacity`, collision handle =
separate chaining (প্রতি bucket এ linked list)।

### প্রশ্ন ১: Hash table কী? কেন দরকার?
Key থেকে সরাসরি index বের করে data এ পৌঁছায় — average O(1) এ
insert/find/remove। Array তে O(n) search, BST তে O(log n) — hash table
আরও fast।

### প্রশ্ন ২: Hash function কী?
Key কে একটা index এ convert করার নিয়ম। আমার ক্ষেত্রে:
```
index = key % capacity
```
যেমন capacity=10, key=23 → index=3।

### প্রশ্ন ৩: Negative key handle কীভাবে?
C++ এ `-7 % 10` হতে পারে `-7` — array index negative হবে না। তাই আমি
প্রথমে absolute value নিই (অথবা `((key % cap) + cap) % cap`)। ফলে index
সবসময় `[0, cap-1]` এর মধ্যে।

### প্রশ্ন ৪: Collision কী?
দুটো ভিন্ন key এর একই index। যেমন capacity=10, key=3 আর key=13 দুটোরই
index=3।

### প্রশ্ন ৫: Separate chaining কীভাবে কাজ করে?
প্রতিটা bucket এ একটা **linked list** রাখি। Collision হলে list এর শেষে
নতুন pair যোগ। Find করতে hash → তারপর সেই list ঘুরে key match করি।

**উদাহরণ** (capacity=5):
```
insert (3, "a"), (8, "b"), (13, "c")  — সবার index 3
bucket[3]: (3,"a") → (8,"b") → (13,"c")
```

### প্রশ্ন ৬: Open addressing এর সাথে পার্থক্য?
- **Separate chaining**: collision হলে আলাদা list এ যোগ।
- **Open addressing**: collision হলে অন্য খালি bucket খুঁজি (linear/quadratic
  probing)।
Chaining সহজ implement করতে, load factor 1 এর বেশি হলেও কাজ করে।

### প্রশ্ন ৭: Complexity কী?
- Average (ভালো hash, কম collision): **O(1)** insert/find/remove।
- Worst (সব key একই bucket এ): **O(n)** — একটাই বড় list হয়ে যায়।

### প্রশ্ন ৮: Load factor কী?
`load_factor = size / capacity`। অনেক বড় হলে collision বাড়ে → rehash
করতে হয় (capacity দ্বিগুণ, সব key re-insert)। আমার simple version এ
rehash করিনি।

### প্রশ্ন ৯: Remove কীভাবে?
১. hash → bucket।
২. List ঘুরে key খুঁজি।
৩. পেলে linked list থেকে node সরিয়ে delete।

---

## 🎯 শেষ কথা — Defence এর সময় টিপস

1. **শান্ত থাকো** — শিক্ষক "কেন এই লাইন?" বললে confidence এ উত্তর দাও।
2. **Code এর comment পড়ো** — আমি ইচ্ছা করে heavy comment লিখেছি, এগুলো
   কাজে লাগবে।
3. **Complexity মুখস্থ রাখো** — প্রতিটা operation এর Big-O।
4. **উদাহরণ আঁকতে পারো** — কাগজে ছোট tree/graph/array এঁকে দেখাও।
5. **"আমি জানি না" বলা ঠিক আছে** — guess করার চেয়ে ভালো। তারপর বলো
   "চিন্তা করে দেখি"।
6. **নিজের শব্দে বলো** — মুখস্থ না, বোঝা চাই।

শুভ কামনা ভাই! 🤲
