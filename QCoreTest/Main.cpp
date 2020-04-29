#include <iostream>

#include "QCoreTest.hpp"

int main() {
    testCore();
    testBits();
    testVector();
    testMatrix();
    testQuaternion();
    testMath();
    testUtils();
    testTime();
    testLog();

    std::cout << "All tests complete" << std::endl;
    std::cin.get();
    return 0;
}
