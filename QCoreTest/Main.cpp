#include <iostream>

#include "QCoreTest.hpp"



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
    testDirectMap();

    std::cout << "All tests complete" << std::endl;
    std::cin.get();
    return 0;
}