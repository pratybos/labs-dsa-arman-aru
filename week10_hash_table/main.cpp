// main.cpp — Week 10 demo: HashTable with separate chaining.
// I use capacity 10 on purpose so keys 1, 11, 21 COLLIDE.
#include <iostream>
#include "dsa/HashTable.hpp"

int main() {
    // Hash table with 10 buckets (so 1 % 10 = 11 % 10 = 21 % 10 = 1 — collision!).
    dsa::HashTable t(10);

    // Insert a few keys. The first three all land in bucket 1.
    t.put(1,  100);
    t.put(11, 110);
    t.put(21, 121);
    // Two more keys in different buckets.
    t.put(2,  200);
    t.put(3,  300);
    // A negative key, to demonstrate that hash() handles them.
    t.put(-7, -77);

    // Print basic stats.
    std::cout << "size=" << t.size()
              << " bucket_count=" << t.bucket_count() << "\n";

    // get() returns a POINTER (or nullptr). I check it before dereferencing.
    int* p = t.get(11);
    std::cout << "get(11)=" << (p ? *p : -1) << "\n";
    // contains() returns a bool. true for stored keys, false otherwise.
    std::cout << "contains(21)=" << t.contains(21) << "\n";
    std::cout << "contains(999)=" << t.contains(999) << "\n";
    // get() for a negative key — confirms hash() handled the sign.
    std::cout << "get(-7)=" << (t.get(-7) ? *t.get(-7) : -1) << "\n";

    // Updating an existing key returns false (not a NEW insertion).
    bool inserted = t.put(11, 999);
    std::cout << "put(11,999) -> inserted_new=" << inserted
              << " new_value=" << *t.get(11) << "\n";

    // Remove key 11 from the colliding bucket. The other two stay intact.
    bool removed = t.remove(11);
    std::cout << "remove(11)=" << removed
              << " contains(11)=" << t.contains(11)
              << " contains(1)=" << t.contains(1)
              << " contains(21)=" << t.contains(21)
              << "\n";

    return 0;
}
