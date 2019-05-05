#include <iostream>

int main(int argc, char *argv[])
{
    static_assert(sizeof(long) == 4, "Size of int must be 4 bytes");
    return 0;
}
