#include <string>
#include <iostream>
#include <chrono>
#include <unordered_map>

#include "QMap.hpp"

using std::string;
using std::cout;
using std::endl;
using std::unordered_map;

using namespace qmu;

namespace {

Map<int> sk_map1;
Map<string> sk_map2;
Map<int *> sk_map3;
Map<char> sk_map4;

void setupMaps() {
	for (int i = 0; i < 10; ++i) {
		sk_map1.addByHash(i, i);
		sk_map2.addByHash(i, "" + i);
		sk_map3.addByHash(i, new int(i));
	}
	for (int i = 0; i < 1000000; ++i) {
		sk_map4.addByHash(i, i % 256);
	}
}

bool testDefaultConstructor() {
	Map<int> m;
	if (m.nSlots() != gk_defNSlots || m.size() != 0) return false;	
	return true;
}

bool testConstructor() {
	cout << "small..." << endl;
	Map<int> m1(10);
	if (m1.nSlots() != 10 || m1.size() != 0) return false;

	cout << "huge..." << endl;
	Map<int> m2(100000);
	if (m2.nSlots() != 100000 || m2.size() != 0) return false;

	cout << "zero..." << endl;
	Map<int> m3(0);
	if (m3.nSlots() != 1 || m3.size() != 0) return false;

	cout << "negative..." << endl;
	Map<int> m4(-1);
	if (m4.nSlots() != 1 || m4.size() != 0) return false;

	return true;
}

bool testCopyConstructor() {
	cout << "int..." << endl;
	Map<int> m1(sk_map1);
	if (&m1 == &sk_map1 || !m1.equals(sk_map1)) return false;

	cout << "string..." << endl;
	Map<string> m2(sk_map2);
	if (&m2 == &sk_map2 || !m2.equals(sk_map2)) return false;

	cout << "int *..." << endl;
	Map<int *> m3(sk_map3);
	if (&m3 == &sk_map3 || !m3.equals(sk_map3)) return false;

	cout << "huge..." << endl;
	Map<char> m4(sk_map4);
	if (&m4 == &sk_map4 || !m4.equals(sk_map4)) return false;

	return true;
}

bool testCopyAssignment() {
	cout << "int..." << endl;
	Map<int> m1 = sk_map1;
	if (&m1 == &sk_map1 || !m1.equals(sk_map1)) return false;

	cout << "string..." << endl;
	Map<string> m2 = sk_map2;
	if (&m2 == &sk_map2 || !m2.equals(sk_map2)) return false;

	cout << "int *..." << endl;
	Map<int *> m3 = sk_map3;
	if (&m3 == &sk_map3 || !m3.equals(sk_map3)) return false;

	cout << "huge..." << endl;
	Map<char> m4 = sk_map4;
	if (&m4 == &sk_map4 || !m4.equals(sk_map4)) return false;

	return true;
}

bool testMoveConstructor() {
	cout << "int..." << endl;
	Map<int> h1(sk_map1);
	Map<int> m1(std::move(h1));
	if (&m1 == &sk_map1 || !m1.equals(sk_map1)) return false;
	if (h1.nSlots() != 0 || h1.size() != 0) return false;

	cout << "string..." << endl;
	Map<string> h2(sk_map2);
	Map<string> m2(std::move(h2));
	if (&m2 == &sk_map2 || !m2.equals(sk_map2)) return false;
	if (h2.nSlots() != 0 || h2.size() != 0) return false;

	cout << "int *..." << endl;
	Map<int *> h3(sk_map3);
	Map<int *> m3(std::move(h3));
	if (&m3 == &sk_map3 || !m3.equals(sk_map3)) return false;
	if (h3.nSlots() != 0 || h3.size() != 0) return false;

	cout << "huge..." << endl;
	Map<char> h4(sk_map4);
	Map<char> m4(std::move(h4));
	if (&m4 == &sk_map4 || !m4.equals(sk_map4)) return false;
	if (h4.nSlots() != 0 || h4.size() != 0) return false;

	return true;
}

bool testMoveAssignment() {
	cout << "int..." << endl;
	Map<int> h1(sk_map1);
	Map<int> m1 = std::move(h1);
	if (&m1 == &sk_map1 || !m1.equals(sk_map1)) return false;
	if (h1.nSlots() != 0 || h1.size() != 0) return false;

	cout << "string..." << endl;
	Map<string> h2(sk_map2);
	Map<string> m2 = std::move(h2);
	if (&m2 == &sk_map2 || !m2.equals(sk_map2)) return false;
	if (h2.nSlots() != 0 || h2.size() != 0) return false;

	cout << "int *..." << endl;
	Map<int *> h3(sk_map3);
	Map<int *> m3 = std::move(h3);
	if (&m3 == &sk_map3 || !m3.equals(sk_map3)) return false;
	if (h3.nSlots() != 0 || h3.size() != 0) return false;

	cout << "huge..." << endl;
	Map<char> h4(sk_map4);
	Map<char> m4 = std::move(h4);
	if (&m4 == &sk_map4 || !m4.equals(sk_map4)) return false;
	if (h4.nSlots() != 0 || h4.size() != 0) return false;

	return true;
}

bool testVariadicConstructor() {
	cout << "uniform..." << endl;
	Map<int> m1(
		0, 5,
		1, 4,
		2, 3,
		3, 2,
		4, 1,
		5, 0
	);
	for (int i = 0; i < 6; ++i) {
		if (m1.get(i) != 5 - i) return false;
	}

	cout << "varying..." << endl;
	Map<int> m2(
		7, 0,
		'd', 2,
		9.9, 3,
		7.0f, 4,
		std::string("five"), 5
	);
	if (m2.get(7) != 0 ||
		m2.get('d') != 2 ||
		m2.get(9.9) != 3 ||
		m2.get(7.0f) != 4 ||
		m2.get(std::string("five")) != 5)
		return false;

	cout << "single pair..." << endl;
	Map<int> m3(77, 777);
	if (m3.get(77) != 777) return false;

	return true;
}

bool testDestructor() {
	Map<long long> * m1 = new Map<long long>(1000);
	for (int i = 0; i < 10000; ++i) {
		m1->addByHash(i, i);
	}
	delete m1;
	return true;
}

bool testAdd() {
	int arr[100];
	for (int i = 0; i < 100; ++i) {
		arr[i] = i;
	}

	Map<int> m1;

	cout << "int *..." << endl;
	for (int i = 0; i < 10; ++i) {
		m1.add(arr + i, 1, arr[i]);
	}
	if (m1.size() != 10) return false;

	cout << "int..." << endl;
	for (int i = 10; i < 20; ++i) {
		m1.add(arr[i], arr[i]);
	}
	if (m1.size() != 20) return false;

	cout << "string..." << endl;
	for (int i = 20; i < 30; ++i) {
		m1.add(string(1, char(i)), arr[i]);
	}
	if (m1.size() != 30) return false;

	cout << "by hash..." << endl;
	for (int i = 30; i < 40; ++i) {
		m1.addByHash(i, arr[i]);
	}
	if (m1.size() != 40) return false;

	return true;
}

bool testGet() {
	int arr[100];
	Map<int> m1;
	for (int i = 0; i < 100; ++i) {
		arr[i] = i;
		m1.add(i, arr[i]);
	}

	cout << "int *..." << endl;
	for (int i = 0; i < 10; ++i) {
		if (m1.get(arr + i, 1) != i) return false;
	}

	cout << "int..." << endl;
	for (int i = 10; i < 20; ++i) {
		if (m1.get(i) != i) return false;
	}

	cout << "string..." << endl;
	int x = 777;
	m1.add("okay", x);
	if (m1.get("okay") != 777) return false;

	cout << "by hash..." << endl;
	m1.addByHash(12345, arr[20]);
	if (m1.getByHash(12345) != arr[20]) return false;

	return true;
}

bool testSet() {
	int arr[100];
	for (int i = 0; i < 100; ++i) {
		arr[i] = i;
	}
	Map<int> m1;

	cout << "int *..." << endl;
	m1.set(arr + 10, 1, arr[10]);
	if (m1.get(arr + 10, 1) != arr[10]) return false;

	cout << "int..." << endl;
	m1.set(arr[20], arr[20]);
	if (m1.get(arr[20]) != arr[20]) return false;

	cout << "string..." << endl;
	m1.set("okay", arr[30]);
	if (m1.get("okay") != arr[30]) return false;

	cout << "by hash..." << endl;
	m1.setByHash(777, arr[50]);
	if (m1.getByHash(777) != arr[50]) return false;

	return true;
}

bool testRemove() {
	int arr[100];
	for (int i = 0; i < 100; ++i) {
		arr[i] = i;
	}

	Map<int> m1;
	for (int i = 0; i < 100; ++i) {
		m1.add(i, arr[i]);
	}

	cout << "int *..." << endl;
	for (int i = 0; i < 10; ++i) {
		if (m1.remove(arr + i, 1) != i) return false;
	}
	if (m1.size() != 90) return false;

	cout << "int..." << endl;
	for (int i = 10; i < 20; ++i) {
		if (m1.remove(i) != i) return false;
	}
	if (m1.size() != 80) return false;

	cout << "string..." << endl;
	m1.add("okay", arr[25]);
	if (m1.remove("okay") != arr[25]) return false;
	if (m1.size() != 80) return false;

	cout << "by hash..." << endl;
	for (int i = 30; i < 40; ++i) {
		if (m1.removeByHash(hash<m1.sk_p>(i, 0)) != i) return false;
	}
	if (m1.size() != 70) return false;

	return true;
}

bool testHas() {
	int arr[100];
	Map<int> m1;
	for (int i = 0; i < 100; ++i) {
		arr[i] = i;
		m1.add(i, arr[i]);
	}

	cout << "int *..." << endl;
	for (int i = 0; i < 10; ++i) {
		if (!m1.has(arr + i, 1)) return false;
	}

	cout << "int..." << endl;
	for (int i = 10; i < 20; ++i) {
		if (!m1.has(i)) return false;
	}

	cout << "string..." << endl;
	int x = 777;
	m1.add("okay", x);
	if (!m1.has("okay")) return false;

	cout << "by hash..." << endl;
	m1.addByHash(12345, arr[20]);
	if (!m1.hasByHash(12345)) return false;

	return true;
}

bool testContains() {
	int arr[100];
	for (int i = 0; i < 100; ++i) {
		arr[i] = i;
	}

	Map<int> m1;

	for (int i = 0; i < 10; ++i) {
		if (m1.contains(arr[i])) return false;
		m1.add(i, arr[i]);
	}
	for (int i = 0; i < 10; ++i) {
		if (!m1.contains(arr[i])) return false;
		m1.remove(i);
	}
	for (int i = 0; i < 10; ++i) {
		if (m1.contains(arr[i])) return false;
	}

	return true;
}

bool testResize() {
	int arr[100];
	for (int i = 0; i < 100; ++i) {
		arr[i] = i;
	}

	cout << "powers of two..." << endl;
	Map<int> m1(10);
	for (int i = 0; i < 10; ++i) {
		m1.add(i, arr[i]);
	}
	if (m1.nSlots() != 10) return false;
	m1.add(10, arr[10]);
	if (m1.nSlots() != 16) return false;
	for (int i = 11; i < 100; ++i) {
		m1.add(i, arr[i]);
	}
	if (m1.nSlots() != 128) return false;

	cout << "larger..." << endl;
	m1.resize(500);
	if (m1.nSlots() != 500 || m1.size() != 100) return false;
	for (int i = 0; i < 100; ++i) {
		if (m1.get(i) != arr[i]) return false;
	}

	cout << "smaller..." << endl;
	m1.resize(10);
	if (m1.nSlots() != 10 || m1.size() != 100) return false;
	for (int i = 0; i < 100; ++i) {
		if (m1.get(i) != arr[i]) return false;
	}

	return true;
}

bool testClear() {
	int arr[100];

	Map<int> m1;
	for (int i = 0; i < 100; ++i) {
		m1.addByHash(i, arr[i]);
	}

	cout << "standard..." << endl;
	m1.clear();
	if (m1.size() != 0) return false;
	for (int i = 0; i < 100; ++i) {
		if (m1.contains(arr[i])) return false;
	}

	cout << "empty..." << endl;
	m1.clear();
	if (m1.size() != 0) return false;

	return true;
}

bool testEquals() {
	int arr[100];
	for (int i = 0; i < 100; ++i) {
		arr[i] = i;
	}
	
	Map<int> m1;
	for (int i = 0; i < 100; ++i) {
		m1.addByHash(i, arr[i]);
	}

	cout << "equality..." << endl;
	Map<int> m2(m1);
	if (!m2.equals(m1)) return false;

	cout << "inequality..." << endl;
	m2.removeByHash(0);
	if (m2.equals(m1)) return false;

	return true;
}

bool testAllPrimitiveTypes() {
	Map<int> m;
	char c = 0;
	unsigned char uc = 1;
	short s = 2;
	unsigned short us = 3;
	int i = 4;
	unsigned int ui = 5;
	long l = 6;
	unsigned long ul = 7;
	long long ll = 8;
	unsigned long long ull = 9;
	float f = 10;
	double d = 11;

	cout << "add..." << endl;
	m.add(c, 0);
	m.add(uc, 0);
	m.add(s, 0);
	m.add(us, 0);
	m.add(i, 0);
	m.add(ui, 0);
	m.add(l, 0);
	m.add(ul, 0);
	m.add(ll, 0);
	m.add(ull, 0);
	m.add(f, 0);
	m.add(d, 0);

	cout << "get..." << endl;
	m.get(c);
	m.get(uc);
	m.get(s);
	m.get(us);
	m.get(i);
	m.get(ui);
	m.get(l);
	m.get(ul);
	m.get(ll);
	m.get(ull);
	m.get(f);
	m.get(d);

	cout << "set..." << endl;
	m.set(c, 0);
	m.set(uc, 0);
	m.set(s, 0);
	m.set(us, 0);
	m.set(i, 0);
	m.set(ui, 0);
	m.set(l, 0);
	m.set(ul, 0);
	m.set(ll, 0);
	m.set(ull, 0);
	m.set(f, 0);
	m.set(d, 0);

	cout << "remove..." << endl;
	m.remove(c);
	m.remove(uc);
	m.remove(s);
	m.remove(us);
	m.remove(i);
	m.remove(ui);
	m.remove(l);
	m.remove(ul);
	m.remove(ll);
	m.remove(ull);
	m.remove(f);
	m.remove(d);

	cout << "has..." << endl;
	m.has(c);
	m.has(uc);
	m.has(s);
	m.has(us);
	m.has(i);
	m.has(ui);
	m.has(l);
	m.has(ul);
	m.has(ll);
	m.has(ull);
	m.has(f);
	m.has(d);

	return true;
}

bool testReferenceNature() {
	Map<int> m1;
	m1.add(777, 7);
	m1.get(777) = 8;
	if (m1.get(777) != 8) {
		return false;
	}
	int * ip = &m1.get(777);
	*ip = 9;
	if (m1.get(777) != 9) {
		return false;
	}

	return true;
}

bool testErrorThrows() {
	Map<int> m1;

	cout << "ElementNotFound..." << endl;
	try {
		m1.get(0);
		return false;
	}
	catch (ElementNotFoundException ex) {}
	try {
		m1.remove(0);
		return false;
	}
	catch (ElementNotFoundException ex) {}

	cout << "PreexistingElement..." << endl;
	try {
		m1.add(0, 0);
		m1.add(0, 1);
		return false;
	}
	catch (PreexistingElementException ex) {}

	return true;
}

bool testSeedNature() {
	Map<int> m1;

	try {
		for (int i = 0; i < 100; ++i) {
			m1.seed(i * i);
			m1.add(0, i);
		}
	}
	catch (PreexistingElementException ex) {
		return false;
	}
	try {
		for (int i = 0; i < 100; ++i) {
			m1.seed(i * i);
			if (m1.get(0) != i) {
				return false;
			}
		}
	}
	catch (ElementNotFoundException ex) {
		return false;
	}

	return true;
}

bool testPrecisions() {
	cout << "x32..." << endl;
	Map<int, 32> m1;
	m1.add(99, 7);
	if (m1.get(99) != 7) return false;
	if (!m1.getByHash(hash<32, int>(99, gk_defSeed))) return false;

	cout << "x64..." << endl;
	Map<int, 64> m2;
	m2.add(99, 7);
	if (m2.get(99) != 7) return false;
	if (!m2.hasByHash(hash<64, int>(99, gk_defSeed))) return false;

	cout << "x128..." << endl;
	Map<int, 128> m3;
	m3.add(99, 7);
	if (m3.get(99) != 7) return false;
	if (!m3.hasByHash(hash<128, int>(99, gk_defSeed))) return false;

	return true;
}

bool testPrintContents() {
	int arr[100];
	for (int i = 0; i < 100; ++i) {
		arr[i] = i;
	}

	cout << "standard..." << endl;
	Map<int> m1;
	for (int i = 0; i < 30; ++i) {
		m1.addByHash(i, arr[i]);
	}
	cout << "value..." << endl;
	m1.printContents(cout, true, false, false);
	cout << "key..." << endl;
	m1.printContents(cout, false, true, false);
	cout << "address..." << endl;
	m1.printContents(cout, false, false, true);
	cout << "value & key..." << endl;
	m1.printContents(cout, true, true, false);
	cout << "key & address..." << endl;
	m1.printContents(cout, false, true, true);
	cout << "value & address..." << endl;
	m1.printContents(cout, true, false, true);
	cout << "all..." << endl;
	m1.printContents(cout, true, true, true);

	cout << "empty..." << endl;
	Map<int> m2;
	m2.printContents(cout, true, true, true);

	cout << "too many elements..." << endl;
	Map<int> m3;
	for (int i = 0; i < 100; ++i) {
		m3.addByHash(i, arr[i]);
	}
	m3.printContents(cout, true, true, true);

	cout << "too many slots..." << endl;
	Map<int> m4(100);
	for (unsigned int i = 0; i < 100; ++i) {
		m4.addByHash(i, arr[i]);
	}
	m4.printContents(cout, true, true, true);

	return true;
}

bool testIterator() {
	struct Test { int v; };
	cout << "standard..." << endl;
	Map<Test> m1;
	for (int i = 0; i < 100; ++i) {
		m1.addByHash(i, { i });
	}
	m1.resize(10);
	int i = 0;
	for (auto it = m1.begin(); it; ++it) {
		if (it->v != i % 10 * 10 + i / 10) return false;
		if ((*it).v != it->v) return false;
		(*it).v *= 2;
		++i;
	}

	cout << "const..." << endl;
	const Map<Test> * mp = &m1;
	i = 0;
	for (auto it = mp->cbegin(); it; ++it) {
		if (it->v != 2 * (i % 10 * 10 + i / 10)) return false;
		if ((*it).v != it->v) return false;
		//(*it).v *= 2;
		++i;
	}

	//cout << "conversion..." << endl;
	Map<Test>::MIterator mit1 = m1.begin();
	Map<Test>::CIterator cit1 = m1.cbegin();
	//mit1 = cit1;

	Map<Test>::MIterator mit2(mit1);
	mit2 = mit1;
	Map<Test>::CIterator cit2(cit1);
	cit2 = cit1;
	Map<Test>::MIterator mit3(std::move(mit1));
	mit3 = std::move(mit1);
	Map<Test>::CIterator cit3(std::move(cit1));
	cit3 = std::move(cit1);

	return true;
}

bool testHashTypeOptimizations() {
	cout << "s08..." <<  endl;
	for (s08 i = 0; i < 100; ++i) {
		if (hash< 32>(i, 0)       != hash< 32>(&i, 1, 0)      ) return false;
		if (hash< 64>(i, 0)       != hash< 64>(&i, 1, 0)      ) return false;
		if (hash<128>(i, 0).u64_1 != hash<128>(&i, 1, 0).u64_1) return false;
		if (hash<128>(i, 0).u64_2 != hash<128>(&i, 1, 0).u64_2) return false;
	}

	cout << "s16..." <<  endl;
	for (s16 i = 0; i < 100; ++i) {
		if (hash< 32>(i, 0)       != hash< 32>(&i, 1, 0)      ) return false;
		if (hash< 64>(i, 0)       != hash< 64>(&i, 1, 0)      ) return false;
		if (hash<128>(i, 0).u64_1 != hash<128>(&i, 1, 0).u64_1) return false;
		if (hash<128>(i, 0).u64_2 != hash<128>(&i, 1, 0).u64_2) return false;
	}

	cout << "s32..." <<  endl;
	for (s32 i = 0; i < 100; ++i) {
		if (hash< 32>(i, 0)       != hash< 32>(&i, 1, 0)      ) return false;
		if (hash< 64>(i, 0)       != hash< 64>(&i, 1, 0)      ) return false;
		if (hash<128>(i, 0).u64_1 != hash<128>(&i, 1, 0).u64_1) return false;
		if (hash<128>(i, 0).u64_2 != hash<128>(&i, 1, 0).u64_2) return false;
	}

	cout << "s64..." <<  endl;
	for (s64 i = 0; i < 100; ++i) {
		if (hash< 32>(i, 0)       != hash< 32>(&i, 1, 0)      ) return false;
		if (hash< 64>(i, 0)       != hash< 64>(&i, 1, 0)      ) return false;
		if (hash<128>(i, 0).u64_1 != hash<128>(&i, 1, 0).u64_1) return false;
		if (hash<128>(i, 0).u64_2 != hash<128>(&i, 1, 0).u64_2) return false;
	}

	return true;
}

bool testStats() {
	cout << "standard..." << endl;
	int arr[1000];
	for (int i = 0; i < 1000; ++i) {
		arr[i] = i;
	}
	Map<int> m1;
	for (int i = 0; i < 1000; ++i) {
		m1.add(i, arr[i]);
	}
	m1.resize(100);

	Map<int>::MapStats stats1 = m1.stats();
	cout << "min:" << stats1.min << ", ";
	cout << "max:" << stats1.max << ", ";
	cout << "median:" << stats1.median << ", ";
	cout << "mean:" << stats1.mean << ", ";
	cout << "stddev:" << stats1.stddev << endl;
	Map<int>::printHisto(stats1, cout);

	cout << "empty..." << endl;
	Map<int> m2(1);
	Map<int>::MapStats stats2 = m2.stats();
	cout << "min:" << stats2.min << ", ";
	cout << "max:" << stats2.max << ", ";
	cout << "median:" << stats2.median << ", ";
	cout << "mean:" << stats2.mean << ", ";
	cout << "stddev:" << stats2.stddev << endl;
	Map<int>::printHisto(stats2, cout);


	/*
	cout << "huge..." << endl;
	Map<char> m3(1000000);
	for (int i = 0; i < 10000000; ++i) {
		m3.add(i, 0);
	}
	Map<char>::MapStats stats3 = m3.stats();
	cout << "min:" << stats3.min << ", ";
	cout << "max:" << stats3.max << ", ";
	cout << "median:" << stats3.median << ", ";
	cout << "mean:" << stats3.mean << ", ";
	cout << "stddev:" << stats3.stddev << endl;
	Map<char>::printHisto(stats3, cout);
	*/

	return true;
}

template <typename T> struct Generator;
template <> struct Generator<s08> {
	s08 v;
	void next() { ++v; }
	void reset() { v = 0; }
};
template <> struct Generator<s16> {
	s16 v;
	void next() { ++v; }
	void reset() { v = 0; }
};
template <> struct Generator<s32> {
	s32 v;
	void next() { ++v; }
	void reset() { v = 0; } };
template <> struct Generator<s64> {
	s64 v;
	void next() { ++v; }
	void reset() { v = 0; }
};
template <> struct Generator<s128> {
	s128 v;
	void next() { v = s128{ ++v.s64_1, ++v.s64_2 }; }
	void reset() { v = { 0, 0 }; }
};
template <> struct Generator<string> {
	unsigned char c;
	string v;
	void next() { ++c; v = string(c, c); }
	void reset() { v = string(); }
};

template <typename T>
bool testPerformance(int n, Generator<T> g) {
	Map<int> m1;
	std::unordered_map<T, int> u1;
	std::chrono::time_point<std::chrono::high_resolution_clock> thenM, thenU;
	std::chrono::duration<double> timeM, timeU;

	cout << "setting..." << endl;
	g.reset();
	thenM = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < n; ++i) {
		m1.set(g.v, i);
		g.next();
	}
	timeM = std::chrono::high_resolution_clock::now() - thenM;
	cout << "switch..." << endl;
	g.reset();
	thenU = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < n; ++i) {
		u1[g.v] = i;
		g.next();
	}
	timeU = std::chrono::high_resolution_clock::now() - thenU;
	cout << timeU.count() / timeM.count() * 100.0 << "% faster" << endl;
	cout << endl;

	cout << "getting..." << endl;
	g.reset();
	thenM = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < n; ++i) {
		m1.get(g.v);
		g.next();
	}
	timeM = std::chrono::high_resolution_clock::now() - thenM;
	cout << "switch..." << endl;
	g.reset();
	thenU = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < n; ++i) {
		u1.at(g.v);
		g.next();
	}
	timeU = std::chrono::high_resolution_clock::now() - thenU;
	cout << timeU.count() / timeM.count() * 100.0 << "% faster" << endl;
	cout << endl;
	timeU = std::chrono::high_resolution_clock::now() - thenU;
	cout << timeU.count() / timeM.count() * 100.0 << "% faster" << endl;
	cout << endl;

	cout << "iterator..." << endl;
	thenM = std::chrono::high_resolution_clock::now();
	for (auto it = m1.begin(); it != m1.end(); ++it) {
	}
	timeM = std::chrono::high_resolution_clock::now() - thenM;
	cout << "switch..." << endl;
	thenU = std::chrono::high_resolution_clock::now();
	for (auto it = u1.begin(); it != u1.end(); ++it) {
	}
	timeU = std::chrono::high_resolution_clock::now() - thenU;
	cout << timeU.count() / timeM.count() * 100.0 << "% faster" << endl;
	cout << endl;

	cout << "checking and removing..." << endl;
	g.reset();
	thenM = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < n; ++i) {
		if (m1.has(g.v)) m1.remove(g.v);
		g.next();
	}
	timeM = std::chrono::high_resolution_clock::now() - thenM;
	cout << "switch..." << endl;
	g.reset();
	thenU = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < n; ++i) {
		if (u1.count(g.v)) u1.erase(g.v);
		g.next();
	}
	timeU = std::chrono::high_resolution_clock::now() - thenU;
	cout << timeU.count() / timeM.count() * 100.0 << "% faster" << endl;
	cout << endl;

	return true;
}

bool testPerformanceSuite() {
	cout << "k:    s08, n: 1000000" << endl;
	if (!testPerformance<   s08>(1000000, Generator<   s08>())) return false;
	cout << endl;
	cout << "k:    s16, n:  500000" << endl;
	if (!testPerformance<   s16>( 500000, Generator<   s16>())) return false;
	cout << endl;
	cout << "k:    s32, n:  250000" << endl;
	if (!testPerformance<   s32>( 250000, Generator<   s32>())) return false;
	cout << endl;
	cout << "k:    s64, n:  125000" << endl;
	if (!testPerformance<   s64>( 125000, Generator<   s64>())) return false;
	cout << endl;
	cout << "k: string, n: 100000" << endl;
	if (!testPerformance<string>( 100000, Generator<string>())) return false;
	cout << endl;

	return true;
}

bool runTests() {

	cout << "Testing Default Constructor..." << endl << endl;
	if (!testDefaultConstructor()) {
		cout << "Default Constructor Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing Constructor..." << endl << endl;
	if (!testConstructor()) {
		cout << "Constructor Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing Copy Constructor..." << endl << endl;
	if (!testCopyConstructor()) {
		cout << "Copy Constructor Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing Copy Assignment..." << endl << endl;
	if (!testCopyAssignment()) {
		cout << "Copy Assignment Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing Move Constructor..." << endl << endl;
	if (!testMoveConstructor()) {
		cout << "Move Constructor Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing Move Assignment..." << endl << endl;
	if (!testMoveAssignment()) {
		cout << "Move Assignment Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing Variadic Constructor..." << endl << endl;
	if (!testVariadicConstructor()) {
		cout << "Variadic Constructor Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing Destructor..." << endl << endl;
	if (!testDestructor()) {
		cout << "Destructor Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing Add..." << endl << endl;
	if (!testAdd()) {
		cout << "Add Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing Get..." << endl << endl;
	if (!testGet()) {
		cout << "Get Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing Set..." << endl << endl;
	if (!testSet()) {
		cout << "Set Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing Remove..." << endl << endl;
	if (!testRemove()) {
		cout << "Remove Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing Has..." << endl << endl;
	if (!testHas()) {
		cout << "Has Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing Contains..." << endl << endl;
	if (!testContains()) {
		cout << "Contains Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing Resize..." << endl << endl;
	if (!testResize()) {
		cout << "Resize Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing Clear..." << endl << endl;
	if (!testClear()) {
		cout << "Clear Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing Equals..." << endl << endl;
	if (!testEquals()) {
		cout << "Equals Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing All Primitive Types..." << endl << endl;
	if (!testAllPrimitiveTypes()) {
		cout << "All Primitive Types Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing Reference Nature..." << endl << endl;
	if (!testReferenceNature()) {
		cout << "Reference Nature Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing Error Throws..." << endl << endl;
	if (!testErrorThrows()) {
		cout << "Error Throws Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing Seed Nature..." << endl << endl;
	if (!testSeedNature()) {
		cout << "Seed Nature Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing Precisions..." << endl << endl;
	if (!testPrecisions()) {
		cout << "Precisions Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing Iterator..." << endl << endl;
	if (!testIterator()) {
		cout << "Iterator Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing Hash Type Optimizations..." << endl << endl;
	if (!testHashTypeOptimizations()) {
		cout << "Hash Type Optimizations Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing PrintContents..." << endl << endl;
	if (!testPrintContents()) {
		cout << "PrintContents Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing Stats..." << endl << endl;
	if (!testStats()) {
		cout << "Stats Test Failed!" << endl;
		return false;
	}
	cout << endl;

	cout << "Testing Performance..." << endl << endl;
	if (!testPerformanceSuite()) {
		cout << "Performance Test Failed!" << endl;
		return false;
	}
	cout << endl;

	return true;
}

}

int main() {
	setupMaps();

	if (runTests()) {
		cout << "All Tests Passed" << endl;
	}
	else {
		cout << "Testing Failed" << endl;
	}

	cout << endl;
	system("pause");
	return 0;
}