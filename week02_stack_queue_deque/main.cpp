// main.cpp — Week 02 demo: Stack, Queue, Deque
// I print every step so the teacher can SEE the structures work.

// std::cout / std::cin live in <iostream>.
#include <iostream>
// My three data structures from this week.
#include "dsa/Stack.hpp"
#include "dsa/Queue.hpp"
#include "dsa/Deque.hpp"

int main() {
    // -------- Stack demo --------
    // Print a header so the output is easy to read.
    std::cout << "=== Stack demo (LIFO) ===\n";
    // Make a stack of ints.
    dsa::Stack<int> s;
    // Push 10, then 20, then 30 -> 30 ends up on top (LIFO).
    s.push(10); s.push(20); s.push(30);
    // Show how many items are in the stack, and the top value.
    std::cout << "size=" << s.size() << " top=" << s.top() << "\n";
    // Remove the top item (30). The new top must be 20.
    s.pop();
    std::cout << "after pop, top=" << s.top() << " size=" << s.size() << "\n";

    // -------- Queue demo --------
    std::cout << "\n=== Queue demo (FIFO) ===\n";
    // Make an empty queue.
    dsa::Queue<int> q;
    // Add 1, 2, 3 to the back, in that order.
    q.enqueue(1); q.enqueue(2); q.enqueue(3);
    // FIFO -> the very first enqueued item (1) is at the front.
    std::cout << "front=" << q.front() << " size=" << q.size() << "\n";
    // Remove the 1; now 2 is at the front.
    q.dequeue();
    std::cout << "after dequeue, front=" << q.front() << " size=" << q.size() << "\n";

    // -------- Deque demo --------
    std::cout << "\n=== Deque demo (two ends) ===\n";
    // Make an empty deque.
    dsa::Deque<int> d;
    // Build [2, 3] by pushing back twice.
    d.push_back(2);
    d.push_back(3);
    // Push 1 to the front -> [1, 2, 3].
    d.push_front(1);
    // Push 4 to the back -> [1, 2, 3, 4].
    d.push_back(4);
    // Print the two ends and total size.
    std::cout << "front=" << d.front() << " back=" << d.back()
              << " size=" << d.size() << "\n";
    // Remove from both ends.
    d.pop_front();     // [2, 3, 4]
    d.pop_back();      // [2, 3]
    // Print the new state.
    std::cout << "after pop_front/back, front=" << d.front()
              << " back=" << d.back() << " size=" << d.size() << "\n";

    // Program ran successfully.
    return 0;
}
