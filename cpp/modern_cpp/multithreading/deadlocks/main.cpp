#include <iostream>

#include "test1.h"
#include "test2.h"

// https://sites.google.com/site/softwaredesignlabs2/home/terms-abbreviations/deadlock

// Test1
// Avoiding deadlocks:
// 1. std::lock — a function that can lock two or more mutexes at once without risk of deadlock.
// 2. The std::adopt_lock parameter is supplied in  addition to the mutex to indicate to the std::lock_guard objects that the mutexes are already locked
// 3. Pass parameters to a thread function with std::ref()
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

int main(int , char **) {
    Test1();
    // Test2();
    return 0;
}
