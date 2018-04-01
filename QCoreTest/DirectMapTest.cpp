#include "QCoreTest.hpp"

#include "QCore/DirectMap.hpp"



enum class Enum { a, b, c };

void testDirectMap() {

    qc::DirectMap<Enum, int> map({{ Enum::a, 1 }, { Enum::b, 2 }, { Enum::c, 3 }});
//    qc::DirectMap<Enum, int> map1(8);
//    qc::DirectMap<Enum, int> map2(map1);
//    qc::DirectMap<Enum, int> map3(std::move(map2));
//    qc::DirectMap<Enum, int> map4(4, 0);
//    qc::DirectMap<Enum, int> map5({{ Enum::a, 1 }}, 0);
//    map2 = map1;
//    map3 = std::move(map2);

//    map[Enum::c] = 4;

}