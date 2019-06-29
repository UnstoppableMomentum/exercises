#ifndef TEST3_H
#define TEST3_H

// C++11
// run pool of threads
// pass data and get results with std::ref
// std::exception

enum ETestType {
    ETestTypeDataRaces     = 0,  // data races test
    ETestTypeNoDataRaces_1 = 1,  // no data races test (implementation 1)
    ETestTypeNoDataRaces_2 = 2,  // no data races test (implementation 2)
};

struct TestOptions
{
    ETestType eTestType = ETestTypeDataRaces;
    int iDataSize = 100;
    int iThreadsCnt = 4;
};

// Test1 demonstrates the data races problem happens as a consequence
// of the design of the interface.
// See explanation in DataRacesTestFunctor::operator()
// The solution is to change the interface:
// OPTION 1: PASS IN A REFERENCE
// OPTION 2: REQUIRE A NO - THROW COPY CONSTRUCTOR OR MOVE CONSTRUCTOR
// OPTION 3: RETURN A POINTER TO THE POPPED ITEM
// OPTION 4: PROVIDE BOTH OPTION 1 AND EITHER OPTION 2 OR 3
void Test1(const TestOptions& testOptions);


#endif // TEST3_H
