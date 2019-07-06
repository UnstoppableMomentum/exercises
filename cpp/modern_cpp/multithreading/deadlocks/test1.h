#ifndef TEST1_H
#define TEST1_H

// C++11
//
// Test1
// Avoiding deadlocks:
// 1. std::lock — a function that can lock two or more mutexes at once without risk of deadlock.
// 2. The std::adopt_lock parameter is supplied in  addition to the mutex to indicate to the std::lock_guard objects that the mutexes are already locked
// 3. Pass parameters to a thread function with std::ref()
void Test1();

#endif // TEST1_H
