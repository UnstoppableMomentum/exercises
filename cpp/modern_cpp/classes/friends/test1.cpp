//
// Copyright (c) 2022 QAZ
//

#include <cstdio>
#include <utility>

#include "./test1.h"
#include "../../../../base/logs.h"

class test1 {
 private:
    int i_;
public:
    test1() : i_(0) {};
    friend int friendOfTest(test1& test) {
        
    }
};

test1::test1(/* a gs */)
{
}

test1::~ est1()
{
}


void Test1() {
    LOG_BEG();
    LOG_END();
}


