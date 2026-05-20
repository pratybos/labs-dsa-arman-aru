// This special define tells the doctest header to also create a main() function
// for me so I do NOT have to write `int main()` myself in this file.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
// Include the single-header testing library (lives in include/doctest.h).
#include "doctest.h"

// My own data structures that I am about to test.
#include "dsa/Stack.hpp"
#include "dsa/Queue.hpp"
#include "dsa/Deque.hpp"
// std::out_of_range — the exception type my classes throw on bad input.
#include <stdexcept>

// ---------------- Stack ----------------
// TEST_CASE is a doctest macro. Each TEST_CASE is one independent test.
TEST_CASE("Stack basic push/top/pop") {
    // Create a brand-new empty stack of integers.
    dsa::Stack<int> s;
    // A new stack must report itself as empty.
    CHECK(s.empty());
    // Push three values on top, one after another. Order will be 3 on top.
    s.push(1); s.push(2); s.push(3);
    // size() should now be exactly 3.
    CHECK(s.size() == 3);
    // top() returns the most recently pushed item, which is 3.
    CHECK(s.top() == 3);
    // pop() removes the top item (3). After this, top must be 2.
    s.pop();
    CHECK(s.top() == 2);
    // Pop the remaining two items so the stack ends up empty again.
    s.pop();
    s.pop();
    // Confirm the stack is empty after popping everything.
    CHECK(s.empty());
}

TEST_CASE("Stack pop/top on empty throws") {
    // Empty stack — calling pop() or top() on it must throw.
    dsa::Stack<int> s;
    // CHECK_THROWS_AS expects the given expression to throw the given exception type.
    CHECK_THROWS_AS(s.pop(), std::out_of_range);
    CHECK_THROWS_AS(s.top(), std::out_of_range);
}

// ---------------- Queue ----------------
TEST_CASE("Queue basic enqueue/front/dequeue") {
    // Build an empty FIFO queue.
    dsa::Queue<int> q;
    // Empty queue check.
    CHECK(q.empty());
    // Enqueue three numbers in order: 10, 20, 30.
    q.enqueue(10); q.enqueue(20); q.enqueue(30);
    // size() must report 3 items inside the queue.
    CHECK(q.size() == 3);
    // FIFO -> the FIRST inserted (10) must be at the front.
    CHECK(q.front() == 10);
    // Remove the 10 — now the next front is 20.
    q.dequeue();
    CHECK(q.front() == 20);
    // Continue dequeuing in order.
    q.dequeue();
    CHECK(q.front() == 30);
    q.dequeue();
    // Queue must now be empty.
    CHECK(q.empty());
}

TEST_CASE("Queue grows correctly and preserves order across wrap") {
    // This test stresses the circular-buffer logic and the grow() resize.
    dsa::Queue<int> q;
    // Push 0..4 — fills the buffer at least once.
    for (int i = 0; i < 5; ++i) q.enqueue(i);
    // Remove the first 3 elements (0,1,2) — front_ moves forward.
    for (int i = 0; i < 3; ++i) q.dequeue();
    // Push 10 more elements (100..109). This will force the ring to wrap
    // around and probably trigger a grow().
    for (int i = 100; i < 110; ++i) q.enqueue(i);

    // The two leftovers from the original push (3 and 4) must come out first.
    CHECK(q.front() == 3); q.dequeue();
    CHECK(q.front() == 4); q.dequeue();
    // Then 100..109 in the order I enqueued them.
    for (int i = 100; i < 110; ++i) {
        CHECK(q.front() == i);
        q.dequeue();
    }
    // After removing everything the queue must be empty.
    CHECK(q.empty());
}

TEST_CASE("Queue throws when empty") {
    // Empty queue: dequeue() and front() must throw std::out_of_range.
    dsa::Queue<int> q;
    CHECK_THROWS_AS(q.dequeue(), std::out_of_range);
    CHECK_THROWS_AS(q.front(), std::out_of_range);
}

// ---------------- Deque ----------------
TEST_CASE("Deque push_front / push_back / front / back") {
    // A deque can grow on both ends.
    dsa::Deque<int> d;
    CHECK(d.empty());
    // push_back puts 2 at the right end -> [2]
    d.push_back(2);
    // push_front puts 1 at the left end -> [1, 2]
    d.push_front(1);
    // push_back again -> [1, 2, 3]
    d.push_back(3);
    // Size and the two ends should match the picture above.
    CHECK(d.size() == 3);
    CHECK(d.front() == 1);
    CHECK(d.back() == 3);
}

TEST_CASE("Deque pop_front / pop_back") {
    // Build [1, 2, 3] by push_back-ing 1, 2, 3.
    dsa::Deque<int> d;
    d.push_back(1); d.push_back(2); d.push_back(3);
    // pop_front removes the 1 -> [2, 3]
    d.pop_front();
    CHECK(d.front() == 2);
    // pop_back removes the 3 -> [2]
    d.pop_back();
    CHECK(d.back() == 2);
    CHECK(d.size() == 1);
    // pop_back the only remaining element -> empty.
    d.pop_back();
    CHECK(d.empty());
}

TEST_CASE("Deque grows correctly when wrapped") {
    // Pushing only at the front forces front_ to wrap around several times.
    dsa::Deque<int> d;
    for (int i = 0; i < 6; ++i) d.push_front(i);
    // After pushing 0,1,2,3,4,5 to FRONT, the deque looks like: [5,4,3,2,1,0]
    CHECK(d.front() == 5);
    CHECK(d.back() == 0);
    CHECK(d.size() == 6);
}

TEST_CASE("Deque throws on empty pop / front / back") {
    // Every "read or remove" operation on an empty deque must throw.
    dsa::Deque<int> d;
    CHECK_THROWS_AS(d.pop_front(), std::out_of_range);
    CHECK_THROWS_AS(d.pop_back(), std::out_of_range);
    CHECK_THROWS_AS(d.front(), std::out_of_range);
    CHECK_THROWS_AS(d.back(), std::out_of_range);
}
