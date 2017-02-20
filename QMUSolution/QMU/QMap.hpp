//==============================================================================
// QMap ////////////////////////////////////////////////////////////////////////
//==============================================================================
// Austin Quick, 2017
//------------------------------------------------------------------------------



#pragma once



#include "QHash.hpp"
#include "QUtils.hpp"



namespace qmu {



constexpr u32 gk_defSeed = 0;
constexpr nat gk_defNSlots = 8;



//======================================================================================================================
// Map /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================
// Basic unsorted hash map implementation using the murmur3 hashing algorithm.
// Setup as a vector of slots, each a linked list (not std::list) of nodes.
// Each node contains a pointer to the element, the hashkey, and a pointer
// to the next node.
// Can store only a single type, but data can be accessed with any type of key
// or a pointer to any raw data.
// std::string comes implemented using c_str.
// Will always have a minimum of 1 slot, but may have 0 size.
//
// t_p indicates the precision of the hash. 32, 64, and 128 bit hash precision
// is supported.
//------------------------------------------------------------------------------

template <typename E, nat t_p = gk_nat_p>
class Map {



	//--------------------------------------------------------------------------
	// Special Types

	private:

	using H = precision_ut<t_p>; // unsigned integral type of appropriate precision used for hash values



	//--------------------------------------------------------------------------
	// Static Variables

	public:

	static constexpr nat sk_p = t_p; // precision of the map



	//==========================================================================
	// Slot
	//--------------------------------------------------------------------------
	// Otherwise known as "bucket". A bare-bones linked-list used to store any
	// number of elements whose hashkey % nSlots == its index.
	//--------------------------------------------------------------------------

	private:

	class Slot;



	//==========================================================================
	// Iterator
	//--------------------------------------------------------------------------
	// Used to iterate through the map. Comes in mutable and const varieties.
	//--------------------------------------------------------------------------

	public:

	template <typename I_E = E> //E_ may be E or const E
	class Iterator;

	using MIterator = Iterator<E>;
	using CIterator = Iterator<const E>;

	// Creates an iterator at the beginning of the map.
	MIterator begin();
	// Creates a const iterator at the beginning of the map.
	CIterator cbegin() const;
	// Creates an iterator at one past the end of the map.
	MIterator end();
	// Creates a const iterator at one past the end of map.
	CIterator cend() const;



	//--------------------------------------------------------------------------
	// Instance Variables

	private:

	nat m_size;							// total number of elements
	nat m_nSlots;						// number of slots
	std::unique_ptr<Slot[]> m_slots;	// the slots
	nat m_seed;							// the seed to use for hashing operations
	bool m_resizing;					// the map is currently resizing



	//==========================================================================
	// Map
	//--------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------

	public:

	Map();
	Map(const Map & other);
	Map(Map && other);
	explicit Map(nat nSlots);
	template <typename K, typename... Pairs>
	Map(const K & key, const E & element, const Pairs &... pairs);



	//==========================================================================
	// ~Map
	//--------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------

	public:

	~Map();



	//==========================================================================
	// operator=
	//--------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------

	public:

	Map & operator=(const Map & other);
	Map & operator=(Map && other);



	//==========================================================================
	// add
	//--------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------

	public:

	template <typename K>
	void add(const K & key, const E & element);
	template <typename K>
	void add(const K * key, nat nElements, const E & element);
	void add(const std::string & key, const E & element);

	void addByHash(H hashKey, const E & element);



	//==========================================================================
	// get
	//--------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------

	public:

	template <typename K>
	E & get(const K & key) const;
	template <typename K>
	E & get(const K * key, nat nElements) const;
	E & get(const std::string & key) const;

	E & getByHash(H hashKey) const;



	//==========================================================================
	// set
	//--------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------

	public:

	template <typename K>
	void set(const K & key, const E & element);
	template <typename K>
	void set(const K * key, nat nElements, const E & element);
	void set(const std::string & key, const E & element);

	void setByHash(H hashKey, const E & element);



	//==========================================================================
	// remove
	//--------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------

	public:

	template <typename K>
	E remove(const K & key);
	template <typename K>
	E remove(const K * key, nat nElements);
	E remove(const std::string & key);

	E removeByHash(H hashKey);



	//==========================================================================
	// has
	//--------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------

	public:

	template <typename K>
	bool has(const K & key) const;
	template <typename K>
	bool has(const K * key, nat nElements) const;
	bool has(const std::string & key) const;

	bool hasByHash(H hashKey) const;



	//==========================================================================
	// contains
	//--------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------

	public:

	// Returns if the map contains the element, and sets keyDest to the hashkey.
	bool contains(const E & element, H * keyDest = nullptr) const;



	//==========================================================================
	// resize
	//--------------------------------------------------------------------------
	// Resizes the map so that there are nSlots slots.
	// All elements are re-organized.
	// Relatively expensive method.
	//--------------------------------------------------------------------------

	public:
	void resize(nat nSlots);



	//==========================================================================
	// clear
	//--------------------------------------------------------------------------
	// clears the map. all slots are cleared. when finished, size = 0
	//--------------------------------------------------------------------------

	public:

	void clear();



	//==========================================================================
	// equals
	//--------------------------------------------------------------------------
	// Returns whether the two maps are equivalent in size and content
	//--------------------------------------------------------------------------

	public:

	bool equals(const Map<E, t_p> & other) const;



	//--------------------------------------------------------------------------
	// Accessors

	public:

	nat size() const;
	bool empty() const;

	nat nSlots() const;

	nat seed() const;
	void seed(nat seed);



	//==========================================================================
	// operator<<
	//--------------------------------------------------------------------------
	// Mainly used for cout << map;
	// generates string with nSlots and size.
	//
	// *note: defined here because linking errors
	//--------------------------------------------------------------------------

	public:

	friend std::ostream & operator<<(std::ostream & os, const Map & hashMap) {
		return os << "nSlots:" << hashMap.m_nSlots << ", nElements:" << hashMap.m_size;
	}



	//==========================================================================
	// printContents
	//--------------------------------------------------------------------------
	// Calls slot.printContents for each slot, to in effect print the entire
	// contents of the map. NOT RECOMMENDED FOR LARGE MAPS
	//--------------------------------------------------------------------------

	void printContents(std::ostream & os, bool value, bool hash, bool address) const;



	//==========================================================================
	// stats
	//--------------------------------------------------------------------------
	// Run a basic statistical analysis on the map, filling up a juicy MapStats
	// struct.
	//--------------------------------------------------------------------------

	public:
	struct MapStats {
		nat min, max, median;
		fnat mean, stddev;
		std::shared_ptr<std::unique_ptr<nat[]>> histo;
	};

	MapStats stats() const;



	//==========================================================================
	// printHisto
	//--------------------------------------------------------------------------
	// Prints a statistical analysis of the map including nSlots, size, and
	// in regards to the size of each slot, the mean, upper and lower 10% mean,
	// median, max, min, standard deviation, variance, and a histogram.
	//--------------------------------------------------------------------------

	static void printHisto(const MapStats & stats, std::ostream & os);


};



//======================================================================================================================
// Slot ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================
// A linked-list bucket for the hashmap.
//------------------------------------------------------------------------------

template <typename E, nat t_p>
class Map<E, t_p>::Slot {

	friend Map;



	//==========================================================================
	// Node
	//--------------------------------------------------------------------------
	// Serves as a node for Slot as a basic linked list.
	//--------------------------------------------------------------------------

	private:

	struct Node {
		H hashKey;
		E element;
		Node * next;
	};

	//--------------------------------------------------------------------------
	// Instance Variables

	private:

	Node * m_first;
	nat m_size;



	//==========================================================================
	// Slot
	//--------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------

	private:

	Slot();

	Slot(const Slot & other);



	//==========================================================================
	// ~Slot
	//--------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------

	public:

	~Slot();



	//==========================================================================
	// operator=
	//--------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------

	private:

	Slot & operator=(const Slot & o);



	//==========================================================================
	// push
	//--------------------------------------------------------------------------
	// Creates a new node for element and stores it in ascending order by
	// hashkey if an element already exists, does nothing and returns false.
	//--------------------------------------------------------------------------

	bool push(H hashKey, const E & element);



	//==========================================================================
	// peek
	//--------------------------------------------------------------------------
	// Transverses node sequence and sets dest to element at hashkey.
	// Returns false if no element is found.
	//--------------------------------------------------------------------------

	bool peek(H hashKey, E ** dest) const;



	//==========================================================================
	// pop
	//--------------------------------------------------------------------------
	// Transverses node sequence until it finds node with hashkey.
	// "Removes" node by assigning its successor as the successor of its
	// predecessor. Sets dest to element replaced and returns false if no
	// element is found with hashkey.
	//--------------------------------------------------------------------------

	bool pop(H hashKey, E * dest);



	//==========================================================================
	// set
	//--------------------------------------------------------------------------
	// Transverses node sequence...
	// ...if it finds a corresponding node, replaces that node with a new node
	// with element and hashkey, then sets dest to element that was replaced and
	// returns true. If it does not find a node with hashkey, it adds the
	// element and returns false.
	//--------------------------------------------------------------------------

	bool set(H hashKey, const E & element, E * dest);



	//==========================================================================
	// contains
	//--------------------------------------------------------------------------
	// Returns if the slot contains the element, and sets *keyDest to the
	// hashkey.
	//--------------------------------------------------------------------------

	bool contains(const E & element, H * keyDest) const;



	//==========================================================================
	// clear
	//--------------------------------------------------------------------------
	// Empties the slot. Afterwards, m_first == nullptr and size == 0.
	//--------------------------------------------------------------------------

	void clear();



	//==========================================================================
	// equals
	//--------------------------------------------------------------------------
	// Returns whether the two slots are equivalent, with the same number of
	// elements, and the same objects stored.
	//--------------------------------------------------------------------------

	bool equals(const Slot & other) const;



	//==========================================================================
	// printContents
	//--------------------------------------------------------------------------
	// Will attempt to os << *element, hashkey, and address based on bool keys.
	//--------------------------------------------------------------------------

	void printContents(std::ostream & os, bool value, bool hash, bool address) const;

};



//======================================================================================================================
// Iterator ////////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================
// Basic iterator used to iterate forwards over the map.
// iterates forward over the slot, then moves to the next slot.
//------------------------------------------------------------------------------

template <typename E, nat t_p>
template <typename I_E> // may be E or const E
class Map<E, t_p>::Iterator {

	friend Map<E, t_p>;

	//--------------------------------------------------------------------------
	// Special Types

	using I_E_ref = typename std::add_lvalue_reference<I_E>::type;
	using I_E_ptr = typename std::add_pointer<I_E>::type;

	//--------------------------------------------------------------------------
	// Instance Variables

	private:

	const Map<E, t_p> * m_map;
	nat m_slot;
	typename Map<E, t_p>::Slot::Node * m_node;



	//==========================================================================
	// Iterator
	//--------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------

	public:

	Iterator(const Map<E, t_p> & map);
	
	private:

	Iterator(const Map<E, t_p> & map, nat slot, typename Map<E, t_p>::Slot::Node * node);

	public:

	Iterator(const Iterator<I_E> & iterator);



	//==========================================================================
	// ~Iterator
	//--------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------

	~Iterator() = default;



	//==========================================================================
	// operator=
	//--------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------

	Iterator & operator=(const Iterator & o);



	//==========================================================================
	// operator bool
	//--------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------

	operator bool() const;



	//==========================================================================
	// operator++
	//--------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------

	Iterator & operator++();



	//==========================================================================
	// operator++ int
	//--------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------

	Iterator operator++(int);



	//==========================================================================
	// operator==
	//--------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------

	bool operator==(const Iterator & o) const;



	//==========================================================================
	// operator!=
	//--------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------

	bool operator!=(const Iterator & o) const;



	//==========================================================================
	// operator*
	//--------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------

	I_E_ref operator*() const;



	//==========================================================================
	// operator->
	//--------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------

	I_E_ptr operator->() const;

};



//==============================================================================
// ElementNotFoundException
//------------------------------------------------------------------------------
// Cosmetic exception to be thrown when an element can not be found with given
// hash. Equivalent of index-out-of-bounds exception.
//------------------------------------------------------------------------------

class ElementNotFoundException : public std::exception {};



//==============================================================================
// PreexistingElementException
//------------------------------------------------------------------------------
// Cosmetic exception to be thrown when trying to add an element with a hashkey
// already in use.
//------------------------------------------------------------------------------

class PreexistingElementException : public std::exception {};



//==============================================================================
// HashKeyCollisionException
//------------------------------------------------------------------------------
// Cosmetic exception to be thrown when two data keys generate the same
// hashKey. Should be an extremely rare scenario. Not currently implemented.
//------------------------------------------------------------------------------

class HashKeyCollisionException : public std::exception {};



//======================================================================================================================
// TECH ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



namespace tech {



//==============================================================================
// hashMod
//------------------------------------------------------------------------------
// 
//------------------------------------------------------------------------------

template <typename T>
constexpr nat hashMod(const T & h, nat v);
constexpr nat hashMod(const u128 & h, nat v);



//==============================================================================
// hashEqual
//------------------------------------------------------------------------------
// 
//------------------------------------------------------------------------------

template <typename T>
constexpr bool hashEqual(const T & h1, const T & h2);
constexpr bool hashEqual(const u128 & h1, const u128 & h2);



//==============================================================================
// hashLess
//------------------------------------------------------------------------------
// 
//------------------------------------------------------------------------------

template <typename T>
constexpr bool hashLess(const T & h1, const T & h2);
constexpr bool hashLess(const u128 & h1, const u128 & h2);



//==============================================================================
// hashGreater
//------------------------------------------------------------------------------
// 
//------------------------------------------------------------------------------

template <typename T>
constexpr bool hashGreater(const T & h1, const T & h2);
constexpr bool hashGreater(const u128 & h1, const u128 & h2);



}



//==============================================================================================================================================================
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION ==============================================================================================================================================
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//==============================================================================================================================================================



//======================================================================================================================
// MAP IMPLEMENTATION //////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



//==============================================================================
// Map
//------------------------------------------------------------------------------

template <typename E, nat t_p>
Map<E, t_p>::Map() :
	m_size(0),
	m_nSlots(gk_defNSlots),
	m_slots(new Slot[m_nSlots]),
	m_resizing(false)
{}

template <typename E, nat t_p>
Map<E, t_p>::Map(nat nSlots) :
	m_size(0),
	m_nSlots(nSlots < 1 ? 1 : nSlots),
	m_slots(new Slot[m_nSlots]),
	m_resizing(false)
{}

template <typename E, nat t_p>
Map<E, t_p>::Map(const Map<E, t_p> & other) :
	m_size(other.m_size),
	m_nSlots(other.m_nSlots),
	m_slots(new Slot[m_nSlots]),
	m_resizing(false)
{
	for (nat i = 0; i < m_nSlots; ++i) {
		m_slots[i] = other.m_slots[i];
	}
}

template <typename E, nat t_p>
Map<E, t_p>::Map(Map<E, t_p> && other) :
	m_size(other.m_size),
	m_nSlots(other.m_nSlots),
	m_slots(std::move(other.m_slots)),
	m_resizing(false)
{
	other.m_size = 0;
	other.m_nSlots = 0;
}

//helpers for variadic constructor
template <typename E, nat t_p, typename K>
void setMany(Map<E, t_p> & ht, const K & key, const E & element) {
	ht.set(key, element);
}
template <typename E, nat t_p, typename K, typename... Pairs>
void setMany(Map<E, t_p> & ht, const K & key, const E & element, const Pairs &... pairs) {
	ht.set(key, element);
	setMany(ht, pairs...);
}

template <typename E, nat t_p>
template <typename K, typename... Pairs>
Map<E, t_p>::Map(const K & key, const E & element, const Pairs &... pairs) :
	m_size(0),
	m_nSlots((2 + sizeof...(Pairs) + 1) / 2),
	m_slots(new Slot[m_nSlots]),
	m_resizing(false)
{
	setMany(*this, key, element, pairs...);
}



//==============================================================================
// ~Map
//------------------------------------------------------------------------------

template <typename E, nat t_p>
Map<E, t_p>::~Map() {
	m_slots.reset();
}



//==============================================================================
// operatator=
//------------------------------------------------------------------------------

template <typename E, nat t_p>
Map<E, t_p> & Map<E, t_p>::operator=(const Map<E, t_p> & other) {
	if (&other == this) {
		return *this;
	}

	m_size = other.m_size;
	m_nSlots = other.m_nSlots;
	m_slots = std::make_unique<Slot[]>(m_nSlots);
	for (nat i = 0; i < m_nSlots; ++i) {
		m_slots[i] = other.m_slots[i];
	}

	return *this;
}

template <typename E, nat t_p>
Map<E, t_p> & Map<E, t_p>::operator=(Map<E, t_p> && other) {
	m_size = other.m_size;
	m_nSlots = other.m_nSlots;
	m_slots = std::move(other.m_slots);

	other.m_size = 0;
	other.m_nSlots = 0;

	return *this;
}



//==============================================================================
// add
//------------------------------------------------------------------------------

template <typename E, nat t_p> template <typename K>
void Map<E, t_p>::add(const K & key, const E & element) {
	addByHash(hash<t_p>(key, m_seed), element);
}

template <typename E, nat t_p> template <typename K>
void Map<E, t_p>::add(const K * key, nat nElements, const E & element) {
	addByHash(hash<t_p>(key, nElements, m_seed), element);
}

template <typename E, nat t_p>
void Map<E, t_p>::add(const std::string & key, const E & element) {
	addByHash(hash<t_p>(key, m_seed), element);
}



//==============================================================================
// addByHash
//------------------------------------------------------------------------------

template <typename E, nat t_p>
void Map<E, t_p>::addByHash(H hashKey, const E & element) {
	if (!m_resizing && m_size + 1 > m_nSlots) {
		resize(floor2(m_nSlots * 2));
	}
	if (m_slots[tech::hashMod(hashKey, m_nSlots)].push(hashKey, element)) {
		++m_size;
	}
	else {
		throw PreexistingElementException();
	}
}



//==============================================================================
// get
//------------------------------------------------------------------------------

template <typename E, nat t_p> template <typename K>
E & Map<E, t_p>::get(const K & key) const {
	return getByHash(hash<t_p>(key, m_seed));
}

template <typename E, nat t_p> template <typename K>
E & Map<E, t_p>::get(const K * key, nat nElements) const {
	return getByHash(hash<t_p>(key, nElements, m_seed));
}

template <typename E, nat t_p>
E & Map<E, t_p>::get(const std::string & key) const {
	return getByHash(hash<t_p>(key, m_seed));
}



//==============================================================================
// getByHash
//------------------------------------------------------------------------------

template <typename E, nat t_p>
E & Map<E, t_p>::getByHash(H hashKey) const {
	E * element;
	if (!m_slots[tech::hashMod(hashKey, m_nSlots)].peek(hashKey, &element)) {
		throw ElementNotFoundException();
	}
	return *element;
}



//==============================================================================
// set
//------------------------------------------------------------------------------

template <typename E, nat t_p> template <typename K>
void Map<E, t_p>::set(const K & key, const E & element) {
	setByHash(hash<t_p>(key, m_seed), element);
}

template <typename E, nat t_p> template <typename K>
void Map<E, t_p>::set(const K * key, nat nElements, const E & element) {
	setByHash(hash<t_p>(key, nElements, m_seed), element);
}

template <typename E, nat t_p>
void Map<E, t_p>::set(const std::string & key, const E & element) {
	setByHash(hash<t_p>(key, m_seed), element);
}



//==============================================================================
// setByHash
//------------------------------------------------------------------------------

template <typename E, nat t_p>
void Map<E, t_p>::setByHash(H hashKey, const E & element) {
	if (!m_resizing && m_size + 1 > m_nSlots) {
		resize(floor2(m_nSlots * 2));
	}
	E replaced;
	if (!m_slots[tech::hashMod(hashKey, m_nSlots)].set(hashKey, element, &replaced)) {
		++m_size;
	}
}



//==============================================================================
// remove
//------------------------------------------------------------------------------

template <typename E, nat t_p> template <typename K>
E Map<E, t_p>::remove(const K & key) {
	return removeByHash(hash<t_p>(key, m_seed));
}

template <typename E, nat t_p> template <typename K>
E Map<E, t_p>::remove(const K * key, nat nElements) {
	return removeByHash(hash<t_p>(key, nElements, m_seed));
}

template <typename E, nat t_p>
E Map<E, t_p>::remove(const std::string & key) {
	return removeByHash(hash<t_p>(key, m_seed));
}



//==============================================================================
// removeByHash
//------------------------------------------------------------------------------

template <typename E, nat t_p>
E Map<E, t_p>::removeByHash(H hashKey) {
	E element;
	if (m_slots[tech::hashMod(hashKey, m_nSlots)].pop(hashKey, &element)) {
		m_size--;
	}
	else {
		throw ElementNotFoundException();
	}
	return element;
}



//==============================================================================
// has
//------------------------------------------------------------------------------

template <typename E, nat t_p> template <typename K>
bool Map<E, t_p>::has(const K & key) const {
	return hasByHash(hash<t_p>(key, m_seed));
}

template <typename E, nat t_p> template <typename K>
bool Map<E, t_p>::has(const K * key, nat nElements) const {
	return hasByHash(hash<t_p>(key, nElements, m_seed));
}

template <typename E, nat t_p>
bool Map<E, t_p>::has(const std::string & key) const {
	return hasByHash(hash<t_p>(key, m_seed));
}



//==============================================================================
// hasByHash
//------------------------------------------------------------------------------

template <typename E, nat t_p>
bool Map<E, t_p>::hasByHash(H hashKey) const {
	E * element;
	return m_slots[tech::hashMod(hashKey, m_nSlots)].peek(hashKey, &element);
}



//==============================================================================
// contains
//------------------------------------------------------------------------------

template <typename E, nat t_p>
bool Map<E, t_p>::contains(const E & element, H * keyDest) const {
	for (nat i = 0; i < m_nSlots; ++i) {
		if (m_slots[i].contains(element, keyDest)) {
			return true;
		}
	}
	return false;
}



//==============================================================================
// resize
//------------------------------------------------------------------------------

template <typename E, nat t_p>
void Map<E, t_p>::resize(nat nSlots) {
	if (m_resizing) {
		return;
	}
	if (nSlots == m_nSlots) {
		return;
	}
	if (nSlots < 1) {
		nSlots = 1;
	}


	Map<E, t_p> map(nSlots);
	m_resizing = true;
	map.m_resizing = true;

	const Slot::Node * node;
	for (nat i = 0; i < m_nSlots; ++i) {
		node = m_slots[i].m_first;
		while (node) {
			map.addByHash(node->hashKey, node->element);
			node = node->next;
		}
	}

	map.m_resizing = false;
	m_resizing = false;
	*this = std::move(map);
}



//==============================================================================
// clear
//------------------------------------------------------------------------------

template <typename E, nat t_p>
void Map<E, t_p>::clear() {
	if (m_size == 0) {
		return;
	}

	for (nat i = 0; i < m_nSlots; ++i) {
		m_slots[i].clear();
	}

	m_size = 0;
}



//==============================================================================
// equals
//------------------------------------------------------------------------------

template <typename E, nat t_p>
bool Map<E, t_p>::equals(const Map<E, t_p> & other) const {
	if (&other == this) {
		return true;
	}

	if (other.m_nSlots != m_nSlots || other.m_size != m_size) {
		return false;
	}

	for (nat i = 0; i < m_nSlots; ++i) {
		if (!m_slots[i].equals(other.m_slots[i])) {
			return false;
		}
	}

	return true;
}



//==============================================================================
// begin
//------------------------------------------------------------------------------

template <typename E, nat t_p>
typename Map<E, t_p>::MIterator Map<E, t_p>::begin() {
	return MIterator(*this);
}



//==============================================================================
// cbegin
//------------------------------------------------------------------------------

template <typename E, nat t_p>
typename Map<E, t_p>::CIterator Map<E, t_p>::cbegin() const {
	return CIterator(*this);
}



//==============================================================================
// end
//------------------------------------------------------------------------------

template <typename E, nat t_p>
typename Map<E, t_p>::MIterator Map<E, t_p>::end() {
	return MIterator(*this, m_nSlots, nullptr);
}



//==============================================================================
// cend
//------------------------------------------------------------------------------

template <typename E, nat t_p>
typename Map<E, t_p>::CIterator Map<E, t_p>::cend() const {
	return CIterator(*this, m_nSlots, nullptr);
}



//==============================================================================
// size
//------------------------------------------------------------------------------

template <typename E, nat t_p>
nat Map<E, t_p>::size() const {
	return m_size;
}



//==============================================================================
// empty
//------------------------------------------------------------------------------

template <typename E, nat t_p>
bool Map<E, t_p>::empty() const {
	return m_size == 0;
}



//==============================================================================
// nSlots
//------------------------------------------------------------------------------

template <typename E, nat t_p>
nat Map<E, t_p>::nSlots() const {
	return m_nSlots;
}



//==============================================================================
// seed
//------------------------------------------------------------------------------

template <typename E, nat t_p>
nat Map<E, t_p>::seed() const {
	return m_seed;
}

template <typename E, nat t_p>
void Map<E, t_p>::seed(nat seed) {
	m_seed = seed;
}



//==============================================================================
// printContents
//------------------------------------------------------------------------------

template <typename E, nat t_p>
void Map<E, t_p>::printContents(std::ostream & os, bool value, bool hash, bool address) const {
	static const nat k_nSlotsThreshold = 50;

	if (m_nSlots > k_nSlotsThreshold) {
		os << "[S:" << m_nSlots << "][N:" << m_size << "](too large to print)";
		return;
	}

	for (nat s = 0; s < m_nSlots; ++s) {
		os << "[" << s << "]";
		m_slots[s].printContents(os, value, hash, address);
		os << std::endl;
	}
}



//==============================================================================
// stats
//------------------------------------------------------------------------------

template <typename E, nat t_p>
typename Map<E, t_p>::MapStats Map<E, t_p>::stats() const {
	nat min = m_slots[0].m_size;
	nat max = m_slots[0].m_size;
	nat median = m_slots[0].m_size;
	fnat mean = fnat(m_slots[0].m_size);
	fnat stddev = 0.0f;

	nat total = 0;
	for (nat i = 0; i < m_nSlots; ++i) {
		if (m_slots[i].m_size < min) {
			min = m_slots[i].m_size;
		}
		else if (m_slots[i].m_size > max) {
			max = m_slots[i].m_size;
		}

		total += m_slots[i].m_size;
	}
	mean = (fnat)total / m_nSlots;

	nat * sizeCounts = new nat[max - min + 1];
	memset(sizeCounts, 0, (max - min + 1) * sizeof(nat));
	for (nat i = 0; i < m_nSlots; ++i) {
		++sizeCounts[m_slots[i].m_size - min];

		stddev += (m_slots[i].m_size - mean) * (m_slots[i].m_size - mean);
	}
	stddev /= m_nSlots;
	stddev = sqrt(stddev);

	median = min;
	for (nat i = 1; i < max - min + 1; ++i) {
		if (sizeCounts[i] > sizeCounts[median - min]) {
			median = i + min;
		}
	}

	return{
		min, max, median,
		mean, stddev,
		std::make_shared<std::unique_ptr<nat[]>>(sizeCounts)
	};
}



//==============================================================================
// printHisto
//------------------------------------------------------------------------------

template <typename E, nat t_p>
void Map<E, t_p>::printHisto(const MapStats & stats, std::ostream & os) {
	nat sizeDigits = stats.max ? (nat)log10(stats.max) + 1 : 1;
	nat maxCount = (*stats.histo)[stats.median - stats.min];
	nat countDigits = maxCount ? (nat)log10(maxCount) + 1 : 1;
	nat maxLength = 80 - sizeDigits - countDigits - 5; // 5 is for "[][]" & \n
	nat length;
	for (nat i = stats.min; i < stats.max + 1; ++i) {
		os << "[";
		os.width(sizeDigits);
		os << i << "][";
		os.width(countDigits);
		os << (*stats.histo)[i - stats.min];
		os << "]";
		length = nat((fnat)maxLength * (*stats.histo)[i - stats.min] / maxCount + 0.5f);
		for (nat j = 0; j < length; ++j) {
			os << '-';
		}
		os << endl;
	}
}



//======================================================================================================================
// SLOT IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



//==============================================================================
// Slot
//------------------------------------------------------------------------------

template <typename E, nat t_p>
Map<E, t_p>::Slot::Slot() :
	m_first(nullptr),
	m_size(0)
{}

template <typename E, nat t_p>
Map<E, t_p>::Slot::Slot(const Slot & other) {
	if (&other == this) {
		return;
	}

	m_size = other.m_size;
	if (other.m_first) {
		m_first = new Node(*other.m_first);

		Node * node = m_first;
		while (node->next) {
			node->next = new Node(*node->next);
			node = node->next;
		}
	}
	else {
		m_first = nullptr;
	}
}



//==============================================================================
// ~Slot
//------------------------------------------------------------------------------

template <typename E, nat t_p>
Map<E, t_p>::Slot::~Slot() {
	Node * node = m_first, * next;
	while (node) {
		next = node->next;
		delete node;
		node = next;
	}
}



//==============================================================================
// operator=
//------------------------------------------------------------------------------

template <typename E, nat t_p>
typename Map<E, t_p>::Slot & Map<E, t_p>::Slot::operator=(const Slot & other) {
	if (&other == this) {
		return *this;
	}

	m_size = other.m_size;
	if (other.m_first) {
		m_first = new Node(*other.m_first);

		Node * node = m_first;
		while (node->next) {
			node->next = new Node(*node->next);
			node = node->next;
		}
	}
	else {
		m_first = nullptr;
	}

	return *this;
}



//==============================================================================
// push
//------------------------------------------------------------------------------

template <typename E, nat t_p>
bool Map<E, t_p>::Slot::push(H hashKey, const E & element) {
	if (!m_first) {
		m_first = new Node{ hashKey, element, nullptr };
		++m_size;
		return true;
	}

	if (tech::hashLess(hashKey, m_first->hashKey)) {
		m_first = new Node{ hashKey, element, m_first };
		++m_size;
		return true;
	}
	if (tech::hashEqual(hashKey, m_first->hashKey)) {
		return false;
	}

	Node * node = m_first;
	while (node->next && tech::hashLess(node->next->hashKey, hashKey)) {
		node = node->next;
	}

	if (node->next) {
		if (tech::hashEqual(node->next->hashKey, hashKey)) {
			return false;
		}
		node->next = new Node{ hashKey, element, node->next };
	}
	else {
		node->next = new Node{ hashKey, element };
	}

	++m_size;
	return true;
}



//==============================================================================
// peek
//------------------------------------------------------------------------------

template <typename E, nat t_p>
bool Map<E, t_p>::Slot::peek(H hashKey, E ** dest) const {
	Node * node = m_first;
	while (node && tech::hashLess(node->hashKey, hashKey)) {
		node = node->next;
	}
	if (node && tech::hashEqual(node->hashKey, hashKey)) {
		*dest = &node->element;
		return true;
	}
	return false;
}



//==============================================================================
// pop
//------------------------------------------------------------------------------

template <typename E, nat t_p>
bool Map<E, t_p>::Slot::pop(H hashKey, E * dest) {
	if (!m_first) {
		return false;
	}

	if (tech::hashEqual(m_first->hashKey, hashKey)) {
		*dest = m_first->element;
		Node * temp = m_first;
		m_first = m_first->next;
		delete temp;
		--m_size;
		return true;
	}

	Node * node = m_first;
	while (node->next && tech::hashLess(node->next->hashKey, hashKey)) {
		node = node->next;
	}
	if (node->next && tech::hashEqual(node->next->hashKey, hashKey)) {
		*dest = node->next->element;
		Node * temp = node->next;
		node->next = node->next->next;
		delete temp;
		--m_size;
		return true;
	}

	return false;
}



//==============================================================================
// set
//------------------------------------------------------------------------------

template <typename E, nat t_p>
bool Map<E, t_p>::Slot::set(H hashKey, const E & element, E * dest) {
	if (!m_first) {
		m_first = new Node{ hashKey, element };
		++m_size;
		return false;
	}

	if (tech::hashEqual(m_first->hashKey, hashKey)) {
		*dest = m_first->element;
		Node * tempN = m_first->next;
		delete m_first;
		m_first = new Node{ hashKey, element, tempN };
		return true;
	}

	if (tech::hashGreater(m_first->hashKey, hashKey)) {
		m_first = new Node{ hashKey, element, m_first };
		++m_size;
		return false;
	}

	Node * node = m_first;
	while (node->next && tech::hashLess(node->next->hashKey, hashKey)) {
		node = node->next;
	}
	if (node->next) {
		if (tech::hashEqual(node->next->hashKey, hashKey)) {
			*dest = node->next->element;
			Node * tempN = node->next->next;
			delete node->next;
			node->next = new Node{ hashKey, element, tempN };
			return true;
		}
		node->next = new Node{ hashKey, element, node->next };
		++m_size;
		return false;
	}
	node->next = new Node{ hashKey, element, nullptr };
	++m_size;
	return false;
}



//==============================================================================
// contains
//------------------------------------------------------------------------------

template <typename E, nat t_p>
bool Map<E, t_p>::Slot::contains(const E & element, H * keyDest) const {
	Node * node = m_first;
	while (node) {
		if (node->element == element) {
			if (keyDest) {
				*keyDest = node->hashKey;
			}
			return true;
		}
		node = node->next;
	}
	return false;
}



//==============================================================================
// clear
//------------------------------------------------------------------------------

template <typename E, nat t_p>
void Map<E, t_p>::Slot::clear() {
	if (!m_first) {
		return;
	}

	Node * node = m_first, * temp;
	while (node) {
		temp = node->next;
		delete node;
		node = temp;
	}

	m_first = nullptr;
	m_size = 0;
}



//==============================================================================
// equals
//------------------------------------------------------------------------------

template <typename E, nat t_p>
bool Map<E, t_p>::Slot::equals(const Slot & other) const {
	if (&other == this) {
		return true;
	}

	if (other.m_size != m_size) {
		return false;
	}

	Node * next1 = m_first;
	Node * next2 = other.m_first;
	while (next1 && next2) {
		if (next1->element != next2->element) {
			return false;
		}
		next1 = next1->next;
		next2 = next2->next;
	}
	if (next1 != next2) {
		return false;
	}
	return true;
}



//==============================================================================
// printContents
//------------------------------------------------------------------------------

template <typename E, nat t_p>
void Map<E, t_p>::Slot::printContents(std::ostream & os, bool value, bool hash, bool address) const {
	static const nat PHRESHOLD = 10;

	Node * node = m_first;

	os << "[N:" << m_size << "]";

	if (m_size > PHRESHOLD) {
		os << "(too large to print)";
		return;
	}

	while (node) {
		os << "(";
		if (value) {
			os << node->element;
		}
		if (hash) {
			if (value) {
				os << ", ";
			}
			os << node->hashKey;
		}
		if (address) {
			if (value || hash) {
				os << ", ";
			}
			os << std::hex << &node->element << std::dec;
		}
		os << ")";

		node = node->next;
	}
}



//======================================================================================================================
// Iterator Implementation /////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================



//==============================================================================
// Iterator
//------------------------------------------------------------------------------

template <typename E, nat t_p>
template <typename I_E>
Map<E, t_p>::Iterator<I_E>::Iterator(const Map<E, t_p> & map) :
	m_map(&map),
	m_slot(0),
	m_node(nullptr)
{
	while (!m_map->m_slots[m_slot].m_first) ++m_slot;
	if (m_slot < m_map->m_nSlots) m_node = m_map->m_slots[m_slot].m_first;
}

template <typename E, nat t_p>
template <typename I_E>
Map<E, t_p>::Iterator<I_E>::Iterator(const Map<E, t_p> & map, nat slot, typename Map<E, t_p>::Slot::Node * node) :
	m_map(&map),
	m_slot(slot),
	m_node(node)
{}

template <typename E, nat t_p>
template <typename I_E>
Map<E, t_p>::Iterator<I_E>::Iterator(typename const Map<E, t_p>::Iterator<I_E> & iterator) :
	m_map(iterator.m_map),
	m_slot(iterator.m_slot),
	m_node(iterator.m_node)
{}



//==============================================================================
// operator=
//------------------------------------------------------------------------------

template <typename E, nat t_p>
template <typename I_E>
typename Map<E, t_p>::Iterator<I_E> & Map<E, t_p>::Iterator<I_E>::operator=(typename const Map<E, t_p>::Iterator<I_E> & o) {
	m_map = o.m_map;
	m_slot = o.m_slot;
	m_node = o.m_node;
	return *this;
}



//==============================================================================
// operator bool
//------------------------------------------------------------------------------

template <typename E, nat t_p>
template <typename I_E>
Map<E, t_p>::Iterator<I_E>::operator bool() const {
	return m_node != nullptr;
}



//==============================================================================
// operator++
//------------------------------------------------------------------------------

template <typename E, nat t_p>
template <typename I_E>
typename Map<E, t_p>::Iterator<I_E> & Map<E, t_p>::Iterator<I_E>::operator++() {
	m_node = m_node->next;
	if (!m_node) {
		while (++m_slot < m_map->m_nSlots) {
			if (m_map->m_slots[m_slot].m_size > 0) {
				m_node = m_map->m_slots[m_slot].m_first;
				break;
			}
		}
	}
	return *this;
}



//==============================================================================
// operator++ int
//------------------------------------------------------------------------------

template <typename E, nat t_p>
template <typename I_E>
typename Map<E, t_p>::Iterator<I_E> Map<E, t_p>::Iterator<I_E>::operator++(int) {
	Map<E, t_p>::Iterator<I_E> temp(*this);
	operator++();
	return temp;
}



//==============================================================================
// operator==
//------------------------------------------------------------------------------

template <typename E, nat t_p>
template <typename I_E>
bool Map<E, t_p>::Iterator<I_E>::operator==(typename const Map<E, t_p>::Iterator<I_E> & o) const {
	return m_node == o.m_node;
}



//==============================================================================
// operator!=
//------------------------------------------------------------------------------

template <typename E, nat t_p>
template <typename I_E>
bool Map<E, t_p>::Iterator<I_E>::operator!=(typename const Map<E, t_p>::Iterator<I_E> & o) const {
	return m_node != o.m_node;
}



//==============================================================================
// operator*
//------------------------------------------------------------------------------

template <typename E, nat t_p>
template <typename I_E>
typename Map<E, t_p>::Iterator<I_E>::I_E_ref Map<E, t_p>::Iterator<I_E>::operator*() const {
	return m_node->element;
}



//==============================================================================
// operator->
//------------------------------------------------------------------------------

template <typename E, nat t_p>
template <typename I_E>
typename Map<E, t_p>::Iterator<I_E>::I_E_ptr Map<E, t_p>::Iterator<I_E>::operator->() const {
	return &m_node->element;
}



//======================================================================================================================
// TECH IMPLEMENTATION /////////////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================================================

namespace tech {



//==============================================================================
// hashMod
//------------------------------------------------------------------------------

template <typename T>
constexpr nat hashMod(const T & h, nat v) {
	return h % v;
}

constexpr nat hashMod(const u128 & h, nat v) {
	return (h.u64_1 ^ h.u64_2) % v;
}



//==============================================================================
// hashEqual
//------------------------------------------------------------------------------

template <typename T>
constexpr bool hashEqual(const T & h1, const T & h2) {
	return h1 == h2;
}

constexpr bool hashEqual(const u128 & h1, const u128 & h2) {
	return h1.u64_1 == h2.u64_1 && h1.u64_2 == h2.u64_2;
}



//==============================================================================
// hashLess
//------------------------------------------------------------------------------

template <typename T>
constexpr bool hashLess(const T & h1, const T & h2) {
	return h1 < h2;
}

constexpr bool hashLess(const u128 & h1, const u128 & h2) {
	return (h1.u64_1 ^ h1.u64_2) < (h2.u64_1 ^ h2.u64_2);
}



//==============================================================================
// hashGreater
//------------------------------------------------------------------------------

template <typename T>
constexpr bool hashGreater(const T & h1, const T & h2) {
	return h1 > h2;
}

constexpr bool hashGreater(const u128 & h1, const u128 & h2) {
	return (h1.u64_1 ^ h1.u64_2) > (h2.u64_1 ^ h2.u64_2);
}



}



}



//==============================================================================