#ifndef TEST3_H
#define TEST3_H

// C++11
// run pool of threads
// pass data and get results with std::ref
// std::exception
enum ETestType {
    ETestTypeDataRaces               = 0,  // data races test
    ETestTypeNoDataRaces_1_SharedPtr = 1,  // no data races test implementation 1, use Pop() return shared_ptr
    ETestTypeNoDataRaces_1_RefVal    = 2,  // no data races test implementation 1,  use Pop(T&value)
    ETestTypeNoDataRaces_2           = 3,  // no data races test implementation 2
};


struct TestOptions
{
    ETestType eTestType = ETestTypeDataRaces;
    int iDataSize = 100;
    int iThreadsCnt = 4;
};

void Test1(const TestOptions& testOptions);


#endif // TEST3_H
