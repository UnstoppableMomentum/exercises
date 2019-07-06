#ifndef TEST2_H
#define TEST2_H

// C++11
//
// Test2
// Avoiding deadlocks: deferred locking
// 1. std::unique_lock
// 2. std::defer_lock
// 3. Pass parameters to a thread function with std::ref()
//
// See
// https://sites.google.com/site/softwaredesignlabs2/home/modern-c/c-11-threads/protect-data-mutexes-locks/lock_guard
// https://sites.google.com/site/softwaredesignlabs2/home/modern-c/c-11-threads/protect-data-mutexes-locks/stdunique_lock
void Test2();

#endif // TEST1_H
