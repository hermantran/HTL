#ifndef MAPTEST_H
#define MAPTEST_H

#include "map.h"
#include "gtest/gtest.h"

/* ----- Hash Table Constructor Tests ----- */
// Tests the default constructor
TEST(HashTable, defaultConstructorIsEmpty) {
	HTL::map<int, int> m;
	
	EXPECT_EQ(0, m.size());
}

// Tests the copy constructor
TEST(HashTable, copyConstructor) {
	const int TESTING_SIZE = 5;
	const char TESTING_KEYS[] = { 'e', 'd', 'f', 'g', 'h' };
	const int TESTING_VALUES[] = { 87, 89, 91, 93, 95 };
	HTL::map<char, int> m;

	for (int i = 0; i < TESTING_SIZE; i++) {
		m[TESTING_KEYS[i]] = TESTING_VALUES[i];
	}

	HTL::map<char, int> m2(m);

	EXPECT_EQ(TESTING_SIZE, m2.size());
	for (int i = 0; i < TESTING_SIZE; i++) {
		EXPECT_EQ(TESTING_VALUES[i], m2[TESTING_KEYS[i]]);
	}
}


/* ----- Hash Table Operator Tests ----- */
// Tests the = operator to copy another hash table
TEST(HashTable, equalOperator) {
	const int TESTING_SIZE = 10;
	const int TESTING_KEYS[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	const int TESTING_VALUES[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	HTL::map<int, int> m, copy;

	for (int i = 0; i < TESTING_SIZE; i++) {
		copy[TESTING_KEYS[i]] = TESTING_VALUES[i];
	}

	m = copy;
	for (int i = 0; i < TESTING_SIZE; i++) { 
		EXPECT_EQ(TESTING_VALUES[i], m[TESTING_KEYS[i]]);
	}
}

// Tests the [] operator function to return a pair value given the key
TEST(HashTable, squareBracketsOperator) {
	const int TESTING_KEY = 2;
	const std::string TESTING_VALUE = "test";
	HTL::map<int, std::string> m;

	m[TESTING_KEY] = TESTING_VALUE;
	EXPECT_EQ(TESTING_VALUE, m[TESTING_KEY]);
}


/* ----- Hash Table Iterator Tests ----- */
// Tests the begin() member function to return an iterator to the first node
TEST(HashTable, begin) {
	const int TESTING_KEY = 7;
	const char TESTING_VALUE = 'e';
	HTL::map<int, char> m;
	HTL::map<int, char>::iterator it;

	m[TESTING_KEY] = TESTING_VALUE;
	it = m.begin();
	
	EXPECT_EQ(TESTING_VALUE, (*it).value);
}

// Tests the end() member function to return an iterator to the last node
TEST(HashTable, end) {
	const int TESTING_SIZE = 4;
	const int TESTING_KEYS[] = {234, 435, 453, 123 };
	const char TESTING_VALUES[] = { 'C', 'B', 'A', 'B' };
	bool isInHashTable[TESTING_SIZE];
	HTL::map<int, char> m;
	HTL::map<int, char>::iterator it;

	for (int i = 0; i < TESTING_SIZE; i++) {
		m[TESTING_KEYS[i]] = TESTING_VALUES[i];
	}

	for (it = m.begin(); it != m.end(); it++) {
		for (int i = 0; i < TESTING_SIZE; i++) {
			if ((*it).key == TESTING_KEYS[i]) {
				isInHashTable[i] = true;
				break;
			}
		}
	}

	for (int i = 0; i < TESTING_SIZE; i++) {
		EXPECT_TRUE(isInHashTable[i]);
	}

	EXPECT_EQ(TESTING_SIZE, m.size());
}

// Tests the Hash Table iterator copy constructor function
TEST(HashTable, iteratorCopyConstructor) {
	const int TESTING_SIZE = 5;
	const char TESTING_KEYS[] = { 'a', 'b', 'c', 'd', 'e' };
	const int TESTING_VALUES[] = { 1, 2, 6, 24, 120 }; 
	HTL::map<char, int> m;

	for (int i = 0; i < TESTING_SIZE; i++) {
		m[TESTING_KEYS[i]] = TESTING_VALUES[i];
	}

	HTL::map<char, int>::iterator copy = m.begin();
	HTL::map<char, int>::iterator it(copy);
	EXPECT_EQ((*copy).key, (*it).key);
	EXPECT_EQ((*copy).value, (*it).value);
}

// Tests the equality operator function to compare two iterators
TEST(HashTable, iteratorEqualityOperator) {
	const int TESTING_SIZE = 5;
	const char TESTING_KEYS[] = { 'a', 'b', 'c', 'd', 'e' };
	const int TESTING_VALUES[] = { 1, 2, 6, 24, 120 }; 
	HTL::map<char, int> m;

	for (int i = 0; i < TESTING_SIZE; i++) {
		m[TESTING_KEYS[i]] = TESTING_VALUES[i];
	}

	HTL::map<char, int>::iterator it = m.begin();
	EXPECT_TRUE(it == m.begin());
	for (it++; it != m.end(); it++) {
		EXPECT_FALSE(it == m.begin());
	}
}

// Tests the inequality operator function to compare two iterators
TEST(HashTable, iteratorInequalityOperator) {
	const int TESTING_SIZE = 5;
	const char TESTING_KEYS[] = { 'a', 'b', 'c', 'd', 'e' };
	const int TESTING_VALUES[] = { 1, 2, 6, 24, 120 }; 
	HTL::map<char, int> m;

	for (int i = 0; i < TESTING_SIZE; i++) {
		m[TESTING_KEYS[i]] = TESTING_VALUES[i];
	}

	HTL::map<char, int>::iterator it = m.begin();
	EXPECT_FALSE(it != m.begin());
	for (it++; it != m.end(); it++) {
		EXPECT_TRUE(it != m.begin());
	}
}

// Tests the dereference operator to return the pair
TEST(HashTable, iteratorDeferenceOperator) {
	const char TESTING_KEY = 'c';
	const std::string TESTING_VALUE = "test";
	HTL::map<char, std::string> m;

	m[TESTING_KEY] = TESTING_VALUE;

	HTL::map<char, std::string>::iterator it = m.begin();
	EXPECT_EQ(TESTING_KEY, (*it).key);
	EXPECT_EQ(TESTING_VALUE, (*it).value);
}

// Tests the equal operator to assign the other iterator's pair correctly
TEST(HashTable, iteratorEqualOperator) {
	const char TESTING_KEY = 'a';
	const int TESTING_VALUE = 6;
	HTL::map<char, int> m;

	m[TESTING_KEY] = TESTING_VALUE;

	HTL::map<char, int>::iterator copy = m.begin();
	HTL::map<char, int>::iterator it;
	it = copy;
	EXPECT_EQ((*it).key, TESTING_KEY);
	EXPECT_EQ((*it).value, TESTING_VALUE);
}

// Tests the pre-increment operator function to go to next node and return iterator at that node
TEST(HashTable, iteratorPreIncrementOperator) {
	const int TESTING_SIZE = 10;
	const char TESTING_KEYS[] = { 'z', 'y', 'x', 'w', 'v', 'u', 't', 's', 'r', 'q' };
	const double TESTING_VALUES[] = { 0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };
	bool isInHashTable[TESTING_SIZE];
	HTL::map<char, double> m;

	for (int i = 0; i < TESTING_SIZE; i++) {
		m[TESTING_KEYS[i]] = TESTING_VALUES[i];
	}

	HTL::map<char, double>::iterator it;

	for (it = m.begin(); it != m.end(); it++) {
		for (int i = 0; i < TESTING_SIZE; i++) {
			if (TESTING_KEYS[i] == (*it).key &&
				TESTING_VALUES[i] == (*it).value)
			{
				isInHashTable[i] = true;
				break;
			}
		}
	}

	for (int i = 0; i < TESTING_SIZE; i++) {
		EXPECT_TRUE(isInHashTable[i]);
	}
}

// Tests the post-increment operator function to go to next node and return iterator at old node 
TEST(HashTable, iteratorPostIncrementOperator) {
	const int TESTING_SIZE = 10;
	const char TESTING_KEYS[] = { 'z', 'y', 'x', 'w', 'v', 'u', 't', 's', 'r', 'q' };
	const double TESTING_VALUES[] = { 0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };
	bool isInHashTable[TESTING_SIZE];
	HTL::map<char, double> m;

	for (int i = 0; i < TESTING_SIZE; i++) {
		m[TESTING_KEYS[i]] = TESTING_VALUES[i];
	}

	HTL::map<char, double>::iterator it;

	for (it = m.begin(); it != m.end(); ++it) {
		for (int i = 0; i < TESTING_SIZE; i++) {
			if (TESTING_KEYS[i] == (*it).key &&
				TESTING_VALUES[i] == (*it).value)
			{
				isInHashTable[i] = true;
				break;
			}
		}
	}

	for (int i = 0; i < TESTING_SIZE; i++) {
		EXPECT_TRUE(isInHashTable[i]);
	}
}

/* ----- Hash Table Capacity Tests ----- */
// Tests the empty() member function to return bool value indicating if there are no elements
TEST(HashTable, empty) {
	HTL::map<int, char> m;
	const int TESTING_KEY = 3;
	const int TESTING_VALUE = 'c';

	EXPECT_TRUE(m.empty());
	m.emplace(TESTING_KEY, TESTING_VALUE);
	EXPECT_FALSE(m.empty());
}

// Tests the size() member function to return the size
TEST(HashTable, size) {
	const int TESTING_SIZE = 700;
	HTL::map<int, int> m;

	for (int i = 0; i < TESTING_SIZE; i++) {
		m.emplace(i, i*2);
	}

	EXPECT_EQ(TESTING_SIZE, m.size());
}


/* ----- Hash Table Modifier Tests ----- */
// Tests the erase() member function to remove an element
TEST(HashTable, erase) {
	const int TESTING_SIZE = 5;
	const int TESTING_KEYS[] = { 1, 2, 3, 4, 5 };
	const char TESTING_VALUES[] = { 'b', 'c', 'd', 'e', 'f' };
	HTL::map<int, char> m;

	for (int i = 0; i < TESTING_SIZE; i++) {
		m.emplace(TESTING_KEYS[i], TESTING_VALUES[i]);
	}

	HTL::map<int, char>::iterator it = m.begin();
	m.erase(it);
	EXPECT_EQ(TESTING_SIZE - 1, m.size());
}

// Tests the clear() member function to empty out all buckets
TEST(HashTable, clear) {
	const int TESTING_SIZE = 50;
	HTL::map<int, int> m;

	for (int i = 0; i < TESTING_SIZE; i++) {
		m.emplace(i, i*2);
	}

	m.clear();
	EXPECT_EQ(0, m.size());
}

// Tests the emplace() member function to add an element
TEST(HashTable, emplace) {
	const int TESTING_SIZE = 50;
	HTL::map<int, int> m;

	for (int i = 0; i < TESTING_SIZE; i++) {
		m.emplace(i, i*2);
		EXPECT_EQ(i*2, m[i]);
	}
}


/* ----- Hash Table Operation Tests ----- */
// Tests the find() member function to return iterator to an element
TEST(HashTable, find) {
	const int TESTING_KEY = 3;
	const int TESTING_VALUE = 'c';
	HTL::map<int, char> m;
	HTL::map<int, char>::iterator it;

	m[TESTING_KEY] = TESTING_VALUE;
	it = m.find(TESTING_KEY);
	EXPECT_EQ(TESTING_VALUE, (*it).value);
}
#endif