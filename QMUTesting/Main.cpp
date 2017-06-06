#include <iostream>

#include "QMUTest.hpp"



int main(void) {
    testQMU();
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