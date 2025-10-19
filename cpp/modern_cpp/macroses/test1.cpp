/*
 * Copyright 2025 <QQQ>
 */

#include <iostream>

#define max(a, b) (a > b ? a : b)
#define max2(a, b) ((a) > (b) ? (a) : (b))

void Test1()
{
  {
    int m = max(1, 2);
    std::cout << "m: " << m << std::endl;
  }
  {
    int m = max2(1, 2);
    std::cout << "m: " << m << std::endl;
  }


  {
    int a =3 , b = 4;
    int m = max2(a, b);
    std::cout << "m: " << m << std::endl;
  }

  {
    int a = 3 , b = 2;
    int m = max2(++a, b);
    std::cout << "m: " << m << std::endl;
    // OUTPUT : 
    // m:5
    // a is incremented TWICE!
  }

  {
    int a = 3 , b = 2;
    int m = max2(++a, b+10);
    std::cout << "m: " << m << std::endl;
    // OUTPUT : 
    // m:12
    // a is incremented ONCE!
  }
}
