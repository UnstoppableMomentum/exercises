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

namespace {
int GetId() {
    static int glCounter = 0;
    return glCounter++;
}
}

template <typename T>
class DataRacesTestFunctor
{
public:

    DataRacesTestFunctor(T& stack, std::vector<int>& res)
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

                //A possible ordering of operations on a stack from two threads
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
    T& stack_;
    std::vector<int>& res_;
    int id_;
};

template <typename T>
void StartDataRacesTest(const TestOptions& testOptions, T& stack)
{
    LOG_BEG();
    // Vector of threads to read data from the stack
    std::vector<std::thread> threads(testOptions.iThreadsCnt);
    // each thread writes read data into a vector
    std::vector<int> res[testOptions.iThreadsCnt];

    // Read data from the stack in parallel
    for (int i = 0; i < testOptions.iThreadsCnt; ++i) {
        //TODO provide functors for othre tests
        DataRacesTestFunctor<T> f(stack, res[i]);
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

// Fill stack with test data
template <typename T>
void FillData(T& stack, int size)
{
    for (int i = 0; i < size; ++i) {
        stack.Push(i);
    }
}

template <typename T>
void TestDataRaces(const TestOptions& testOptions, T& stack)
{
    FillData(stack, testOptions.iDataSize);
    // TODO provide functors for other tests
    StartDataRacesTest(testOptions, stack);
}

void Test1(const TestOptions& testOptions)
{
    LOG_BEG();
    switch (testOptions.eTestType) {
    case ETestTypeDataRaces: {
        LOG_FUNC_LINE();
        StackBadDesign<int> stack;
        TestDataRaces(testOptions, stack);
        LOG_FUNC_LINE();
    }
        break;
    case ETestTypeNoDataRaces_1:{
        LOG_FUNC_LINE();
        // TODO
        StackBadDesign<int> stack;
        TestDataRaces(testOptions, stack);
        LOG_FUNC_LINE();
    }
        break;
    case ETestTypeNoDataRaces_2:
    {
        LOG_FUNC_LINE();
        // TODO
        StackBadDesign<int> stack;
        TestDataRaces(testOptions, stack);
        LOG_FUNC_LINE();
    }
        break;
    };
    LOG_END();
}


