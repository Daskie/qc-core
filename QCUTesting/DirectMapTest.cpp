#include "QCUTest.hpp"

#include "QCU/DirectMap.hpp"



enum class Enum { a, b, c };

void testDirectMap() {

    qcu::DirectMap<Enum, int> map({{ Enum::a, 1 }, { Enum::b, 2 }, { Enum::c, 3 }});
//    qcu::DirectMap<Enum, int> map1(8);
//    qcu::DirectMap<Enum, int> map2(map1);
//    qcu::DirectMap<Enum, int> map3(std::move(map2));
//    qcu::DirectMap<Enum, int> map4(4, 0);
//    qcu::DirectMap<Enum, int> map5({{ Enum::a, 1 }}, 0);
//    map2 = map1;
//    map3 = std::move(map2);

//    map[Enum::c] = 4;

}