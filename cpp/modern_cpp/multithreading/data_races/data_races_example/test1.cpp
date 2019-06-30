#include "test1.h"

#include "stack_data_races.h"
#include "stack_impl1.h"
#include "stack_impl2.h"
#include "logs.h"

#include <algorithm>
#include <exception>
#include <mutex>
#include <vector>
#include <thread>

namespace {

bool CheckResults(std::vector<int>& res, int size)
{
    bool bRes = true;
    // check the result
    std::cout
            << "Input data size:" << size
            << " Output data size:" << res.size() << std::endl;

    std::sort(res.begin(), res.end());

    for(int i = 0; i < size; ++i) {
        int num_items = std::count(res.begin(), res.end(), i);
        if (num_items != 1) {
            std::cout << " count of " << i << " : " << num_items << std::endl;
            bRes = false;
        }
    }
    return bRes;
}

int GetId() {
    static int glCounter = 0;
    return glCounter++;
}

} // namespace

// class DataRacesTestFunctor
// demonstrates data races
template <typename T>
class DataRacesTestFunctor
{
public:

    DataRacesTestFunctor(StackBadDesign<T>& stack, std::vector<int>& res)
        : stack_(stack)
        , res_(res)
        , id_(GetId())
    {
        LOG_FUNC();
        std::cout << "id" << id_ << std::endl;
    }

    ~DataRacesTestFunctor()
    {
        LOG_FUNC();
        std::cout << "id" << id_ << std::endl;
    }

    void operator()()
    {
        LOG_BEG();
        while (!stack_.Empty()) {
            try {
                // DATA RACES
                // !!! this is where the data race takes place
                // top&pop should be an atomic operation
                auto item = stack_.Top(); // <--
                stack_.Pop(); // <--

                // A possible ordering of operations on a stack from two threads.
                // Let's suppose the top item in the stack is 99
                //Thread A                      |Thread B
                //1.  if(!stack_.empty())       |
                //2.                            | if(!stack_.empty())
                //3.   auto item =stack_.top(); |
                //4.                            |   auto item=stack_.top();
                //5.   stack_.pop();            |
                //6.   res_.push_back(item);    |
                //                              |   stack_.pop();
                //                              |   res_.push_back(item);
                //
                // step 3. : thread A: item = 99
                // step 4. : thread B: item = 99 too!!!
                // 99 will be put in the result array two times.

                res_.push_back(item);
            } catch (const EmptyStackException& ex) {
                static int counter = 1;
                std::cout << __PRETTY_FUNCTION__
                          << " " << ex.what()
                          << " counter:" << counter
                          << std::endl;
                ++counter;
            }
        }
        LOG_END();
    }

private:
    StackBadDesign<T>& stack_;
    std::vector<int>& res_;
    int id_;
};


// class StackThreadSafeImpl1Functor
// test thread safe stack implementation 1
// T:  stack data type
// popSharedPointer = true : use std::shared_ptr<T> Pop()
// popSharedPointer = false: use void Pop(T& value)
template <typename T, bool popSharedPointer>
class StackThreadSafeImpl1Functor
{
public:

    StackThreadSafeImpl1Functor(StackThreadSafeImpl1<T>& stack, std::vector<int>& res)
        : stack_(stack)
        , res_(res)
        , id_(GetId())
        , popSharedPointer_(popSharedPointer)
    {
        LOG_FUNC();
        std::cout << "id" << id_ << std::endl;
    }

    ~StackThreadSafeImpl1Functor()
    {
        LOG_FUNC();
        std::cout << "id" << id_ << std::endl;
    }

    void operator()()
    {
        LOG_BEG();
        if (popSharedPointer_) {
            TestSharedPtrPop();
        } else {
            TestRefValuePop();
        }
        LOG_END();
    }

private:

    void TestSharedPtrPop() {
        LOG_BEG();
        while (!stack_.Empty()) {
            try {
                res_.push_back(*stack_.Pop());
            } catch (const EmptyStackException& ex) {
                static int counter = 1;
                std::cout << __PRETTY_FUNCTION__
                          << " " << ex.what()
                          << " counter:" << counter
                          << std::endl;
                ++counter;
            }
        }
        LOG_END();
    }

    void TestRefValuePop() {
        LOG_BEG();
        while (!stack_.Empty()) {
            try {
                T item;
                stack_.Pop(item);
                res_.push_back(item);
            } catch (const EmptyStackException& ex) {
                static int counter = 1;
                std::cout << __PRETTY_FUNCTION__
                          << " " << ex.what()
                          << " counter:" << counter
                          << std::endl;
                ++counter;
            }
        }
        LOG_END();
    }

    StackThreadSafeImpl1<T>& stack_;
    std::vector<int>& res_;
    int id_;
    bool popSharedPointer_;
};

template <typename TypeStack, typename TypeTestFunc>
void StartDataRacesTest(const TestOptions& testOptions, TypeStack& stack)
{
    LOG_BEG();
    // Vector of threads to read data from the stack
    std::vector<std::thread> threads(testOptions.iThreadsCnt);
    // each thread writes read data into a vector
    std::vector<int> res[testOptions.iThreadsCnt];

    // Read data from the stack in parallel
    for (int i = 0; i < testOptions.iThreadsCnt; ++i) {
        //TODO provide functors for othre tests
        TypeTestFunc f(stack, res[i]);
        threads[i]=std::thread(f);
    }
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

    // Merge results
    std::vector<int> allRes;
    for (int i = 0; i < testOptions.iThreadsCnt; ++i) {
        std::copy(res[i].begin(), res[i].end(), std::back_inserter(allRes));
    }

    // Check results
    bool bRes = CheckResults(allRes, testOptions.iDataSize);
    std::cout
            << "Result: " << (bRes ? "No data races" : "data races detected")
            << std::endl;
    LOG_END();
}

template <typename TypeStack, typename TypeTestFunc>
void TestDataRaces(const TestOptions& testOptions, TypeStack& stack)
{
    // Fill stack with test data
    for (int i = 0; i < testOptions.iDataSize; ++i) {
        stack.Push(i);
    }
    StartDataRacesTest<TypeStack, TypeTestFunc>(testOptions, stack);
}

void Test1(const TestOptions& testOptions)
{
    LOG_BEG();
    switch (testOptions.eTestType) {
    case ETestTypeDataRaces: {
        LOG_FUNC_LINE();
        StackBadDesign<int> stack;
        TestDataRaces<StackBadDesign<int>, DataRacesTestFunctor<int> >
                (testOptions, stack);
        LOG_FUNC_LINE();
    }
    break;

    case ETestTypeNoDataRaces_1_RefVal:{
        LOG_FUNC_LINE();
        StackThreadSafeImpl1<int> stack;
        TestDataRaces<StackThreadSafeImpl1<int>,
                StackThreadSafeImpl1Functor<int, false> >
                (testOptions, stack);
        LOG_FUNC_LINE();
    }
    break;

    case ETestTypeNoDataRaces_1_SharedPtr: {
        LOG_FUNC_LINE();
        StackThreadSafeImpl1<int> stack;
        TestDataRaces<StackThreadSafeImpl1<int>,
                StackThreadSafeImpl1Functor<int, true> >
                (testOptions, stack);
        LOG_FUNC_LINE();
    }
    break;

    case ETestTypeNoDataRaces_2:
    {
        LOG_FUNC_LINE();
        // TODO
        LOG_FUNC_LINE();
    }
    break;

    };
    LOG_END();
}
