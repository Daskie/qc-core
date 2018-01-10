#include <iostream>

#include "QCUTest.hpp"



int main(void) {
    testCore();
    testBits();
    testVector();
    testMatrix();
    testQuaternion();
    testMath();
    testUtils();
    testTime();
    testLog();

    std::cin.get();
    return 0;
}