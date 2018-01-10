#include <iostream>

#include "QCUTest.hpp"



int main(void) {
    testQCU();
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