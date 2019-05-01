#include "test3.h"
#include "logs.h"
#include <vector>

using DataType = std::vector<int>;

class BigData {
public:
    BigData()
    // 1. Uniform initialization
        : data {1,2,3}
    {
        LOG_FUNC();
    }

    ~BigData()
    {
        LOG_FUNC();
    }

    // 2. for lvalue BigData, return lvalue
    DataType& getData() & {
        LOG_FUNC();
        return data;
    }


    // 3. for rvalue BigData, return rvalue
    DataType getData() && {
        LOG_FUNC();
        return std::move(data);
    }

private:
    DataType data;
};

BigData CreateBigData()
{
    return BigData();
}

void Test3()
{
    LOG_BEG();
    {
        // 4. calls lvalue overload for BigData::getData, copy - constructs data
        BigData d;
        auto data = d.getData();
    }
    LOG_BR();
    {
      // calls rvalue overload for BigData::getData Widget::data, move-constructs vals2
       auto data = CreateBigData().getData();
    }
    LOG_END();

//OUTPUT:
//    BigData::BigData()
//    DataType& BigData::getData() &
//    BigData::~BigData()
//    ----------------
//    BigData::BigData()
//    DataType BigData::getData() &&
//    BigData::~BigData()
}
