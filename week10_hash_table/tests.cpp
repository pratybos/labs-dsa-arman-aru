// Make doctest generate main() for us.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dsa/HashTable.hpp"

TEST_CASE("HashTable empty") {
    // Fresh table with 8 buckets and no elements.
    dsa::HashTable t(8);
    CHECK(t.size() == 0);
    CHECK(t.bucket_count() == 8);
    // A key that was never inserted must not be reported as contained.
    CHECK_FALSE(t.contains(7));
    // get() returns nullptr when the key is missing.
    CHECK(t.get(7) == nullptr);
}

TEST_CASE("HashTable put inserts new key returns true") {
    // put() returns TRUE when a brand-new key is inserted.
    dsa::HashTable t(8);
    CHECK(t.put(1, 100));
    CHECK(t.put(2, 200));
    CHECK(t.size() == 2);
    // get() returns a pointer to the stored value.
    CHECK(*t.get(1) == 100);
    CHECK(*t.get(2) == 200);
}

TEST_CASE("HashTable put updates existing returns false") {
    // The second put() with the same key should UPDATE, not insert,
    // and return FALSE (no new key was inserted).
    dsa::HashTable t(8);
    CHECK(t.put(5, 50));
    CHECK_FALSE(t.put(5, 99));
    // Size stays at 1, and the value has changed to 99.
    CHECK(t.size() == 1);
    CHECK(*t.get(5) == 99);
}

TEST_CASE("HashTable handles collisions correctly") {
    // Capacity = 10. Keys 1, 11, 21 all map to bucket 1 (1 % 10, 11 % 10, 21 % 10).
    dsa::HashTable t(10);
    t.put(1,  10);
    t.put(11, 110);
    t.put(21, 210);
    // All three are stored despite sharing a bucket.
    CHECK(t.size() == 3);
    CHECK(*t.get(1)  == 10);
    CHECK(*t.get(11) == 110);
    CHECK(*t.get(21) == 210);
}

TEST_CASE("HashTable remove head/middle/tail") {
    // Three keys in the same bucket -> tests head/middle/tail removal.
    dsa::HashTable t(10);
    t.put(1, 10); t.put(11, 110); t.put(21, 210);
    // Remove one of them -> the other two must still be findable.
    CHECK(t.remove(11));
    CHECK_FALSE(t.contains(11));
    CHECK(t.contains(1));
    CHECK(t.contains(21));
    // Remove the remaining two as well.
    CHECK(t.remove(1));
    CHECK(t.remove(21));
    CHECK(t.size() == 0);
}

TEST_CASE("HashTable remove not-found returns false") {
    // Removing a missing key returns false and does NOT change size.
    dsa::HashTable t(8);
    t.put(3, 30);
    CHECK_FALSE(t.remove(999));
    CHECK(t.size() == 1);
}

TEST_CASE("HashTable works with negative keys") {
    // Negative keys are tricky because key % capacity may be negative.
    // My hash() shifts the result by +capacity when it is negative so
    // the bucket index is always valid.
    dsa::HashTable t(7);
    t.put(-1, 10);
    t.put(-8, 20);
    CHECK(t.contains(-1));
    CHECK(t.contains(-8));
    CHECK(*t.get(-1) == 10);
    CHECK(*t.get(-8) == 20);
}
