#ifndef SETTEST_H
#define SETTEST_H

#include "set.h"
#include "gtest/gtest.h"
#include <algorithm>

/* ----- Binary Search Tree Constructor Tests ----- */
// Tests the default constructor
TEST(BinarySearchTree, defaultConstructorIsEmpty) {
	HTL::set<int> s;
	
	EXPECT_EQ(0, s.size());
}

// Tests the copy constructor
TEST(BinarySearchTree, copyConstructor) {
	const int TESTING_SIZE = 9;
	int TESTING_VALUES[] = { 5, 3, 8, 1, 4, 6, 13, 0, 2 };
	HTL::set<int> s;

	for (int i = 0; i < TESTING_SIZE; i++) {
		s.emplace(TESTING_VALUES[i]);
	}

	std::sort(std::begin(TESTING_VALUES), std::end(TESTING_VALUES));
	HTL::set<int> s2(s);
	HTL::set<int>::iterator it = s2.begin();
	for (int i = 0; i < TESTING_SIZE; i++) { 
		EXPECT_EQ(TESTING_VALUES[i], *it);
		it++;
	}
}


/* ----- Binary Search Tree Operator Tests ----- */
// Tests the = operator to copy another binary search tree
TEST(BinarySearchTree, equalOperator) {
	const int TESTING_SIZE = 9;
	int TESTING_VALUES[] = { 5, 3, 8, 1, 4, 6, 13, 0, 2 };
	HTL::set<int> s, copy;

	for (int i = 0; i < TESTING_SIZE; i++) {
		copy.emplace(TESTING_VALUES[i]);
	}

	std::sort(std::begin(TESTING_VALUES), std::end(TESTING_VALUES));
	s = copy;
	HTL::set<int>::iterator it = s.begin();
	for (int i = 0; i < TESTING_SIZE; i++) { 
		EXPECT_EQ(TESTING_VALUES[i], *it);
		it++;
	}
}

/* ----- Binary Search Tree Iterator Tests ----- */
// Tests the begin() member function to return an iterator to the first node
TEST(BinarySearchTree, begin) {
	const int TESTING_SIZE = 5;
	const double TESTING_VALUES[] = { 3.3, 2.2, 1.1, 0.0, -1.1 };
	HTL::set<double> s;

	for (int i = 0; i < TESTING_SIZE; i++) {
		s.emplace(TESTING_VALUES[i]);
	}

	EXPECT_EQ(TESTING_VALUES[TESTING_SIZE-1], *s.begin());
}

// Tests the end() member function to return an iterator to the last node
TEST(BinarySearchTree, end) {
	const int TESTING_SIZE = 9;
	int TESTING_VALUES[] = { 5, 3, 8, 1, 4, 6, 13, 0, 2 };
	HTL::set<int> s;
	
	for (int i = 0; i < TESTING_SIZE; i++) {
		s.emplace(TESTING_VALUES[i]);
	}

	std::sort(std::begin(TESTING_VALUES), std::end(TESTING_VALUES));
	HTL::set<int>::iterator it;
	int i = 0;
	
	for (it = s.begin(); it != s.end(); it++) {
		EXPECT_EQ(TESTING_VALUES[i], *it);
		i++;
	}
}

// Tests the Binary Search Tree iterator copy constructor function
TEST(BinarySearchTree, iteratorCopyConstructor) {
	const int TESTING_SIZE = 5;
	const int TESTING_INDEX = 3;
	const int TESTING_VALUES[] = { 1, 2, 6, 24, 120 }; 
	HTL::set<int> s;

	for (int i = 0; i < TESTING_SIZE; i++) {
		s.emplace(TESTING_VALUES[i]);
	}

	HTL::set<int>::iterator copy = s.begin() + TESTING_INDEX;
	HTL::set<int>::iterator it(copy);
	EXPECT_EQ(TESTING_VALUES[TESTING_INDEX], *it);
}

// Tests the equality operator function to compare two iterators
TEST(BinarySearchTree, iteratorEqualityOperator) {
	const int TESTING_SIZE = 3;
	const int TESTING_VALUES[] = { 1, 2, 3 };
	HTL::set<int> s;

	for (int i = 0; i < TESTING_SIZE; i++) {
		s.emplace(TESTING_VALUES[i]);
	}

	HTL::set<int>::iterator it = s.begin();
	EXPECT_TRUE(it == s.begin());
	for (int i = 1; i < TESTING_SIZE; i++) {
		EXPECT_FALSE(it + i == s.begin());
	}
}

// Tests the inequality operator function to compare two iterators
TEST(BinarySearchTree, iteratorInequalityOperator) {
	const int TESTING_SIZE = 3;
	const int TESTING_VALUES[] = { 1, 2, 3 };
	HTL::set<int> s;

	for (int i = 0; i < TESTING_SIZE; i++) {
		s.emplace(TESTING_VALUES[i]);
	}

	HTL::set<int>::iterator it = s.begin();
	EXPECT_FALSE(it != s.begin());
	for (int i = 1; i < TESTING_SIZE; i++) {
		EXPECT_TRUE(it + i != s.begin());
	}
}

// Tests the dereference operator to return the node value
TEST(BinarySearchTree, iteratorDeferenceOperator) {
	const int TESTING_VALUE = 5;
	HTL::set<int> s;

	s.emplace(TESTING_VALUE);

	HTL::set<int>::iterator it = s.begin();
	EXPECT_EQ(TESTING_VALUE, *it);
}

// Tests the equal operator to assign the other iterator's node correctly
TEST(BinarySearchTree, iteratorEqualOperator) {
	const int TESTING_SIZE = 5;
	double TESTING_VALUES[] = { 4.4, 3.3, 2.2, 1.1, 0.0 };
	HTL::set<double> s;

	for (int i = 0; i < TESTING_SIZE; i++) {
		s.emplace(TESTING_VALUES[i]);
	}

	std::sort(std::begin(TESTING_VALUES), std::end(TESTING_VALUES));

	HTL::set<double>::iterator it = s.begin();
	HTL::set<double>::iterator it2;
	it2 = it;
	EXPECT_EQ(TESTING_VALUES[0], *it2);
}

// Tests the plus operator function to increment the iterator by a given integer
TEST(BinarySearchTree, iteratorPlusOperator) {
	const int TESTING_SIZE = 10;
	double TESTING_VALUES[] = { 8.8, 4.4, 12.1, 1.1, 5.5, 9.9, 16.1, 11.1, 15.1, 10.0 };
	const int TESTING_INDEX = 3;
	HTL::set<double> s;

	for (int i = 0; i < TESTING_SIZE; i++) {
		s.emplace(TESTING_VALUES[i]);
	}

	std::sort(std::begin(TESTING_VALUES), std::end(TESTING_VALUES));
	EXPECT_EQ(TESTING_VALUES[TESTING_INDEX], *(s.begin() + TESTING_INDEX));
}

// Tests the pre-increment operator function to go to next node and return iterator at that node
TEST(BinarySearchTree, iteratorPreIncrementOperator) {
	const int TESTING_SIZE = 10;
	double TESTING_VALUES[] = { 8.8, 4.4, 12.1, 1.1, 5.5, 9.9, 16.1, 11.1, 15.1, 10.0 };
	HTL::set<double> s;

	for (int i = 0; i < TESTING_SIZE; i++) {
		s.emplace(TESTING_VALUES[i]);
	}

	std::sort(std::begin(TESTING_VALUES), std::end(TESTING_VALUES));
	HTL::set<double>::iterator it;
	int i = 0;
	
	for (it = s.begin(); it != s.end(); ++it) {
		EXPECT_EQ(TESTING_VALUES[i], *it);
		i++;
	}
}

// Tests the post-increment operator function to go to next node and return iterator at old node 
TEST(BinarySearchTree, iteratorPostIncrementOperator) {
	const int TESTING_SIZE = 10;
	double TESTING_VALUES[] = { 8.8, 4.4, 12.1, 1.1, 5.5, 9.9, 16.1, 11.1, 15.1, 10.0 };
	HTL::set<double> s;

	for (int i = 0; i < TESTING_SIZE; i++) {
		s.emplace(TESTING_VALUES[i]);
	}

	std::sort(std::begin(TESTING_VALUES), std::end(TESTING_VALUES));
	HTL::set<double>::iterator it;
	int i = 0;
	
	for (it = s.begin(); it != s.end(); it++) {
		EXPECT_EQ(TESTING_VALUES[i], *it);
		i++;
	}
}


/* ----- Binary Search Tree Capacity Tests ----- */
// Tests the empty() member function to return bool value indicating if there are no elements
TEST(BinarySearchTree, empty) {
	HTL::set<double> s;
	const double TESTING_VALUE = 3.3;

	EXPECT_TRUE(s.empty());
	s.emplace(TESTING_VALUE);
	EXPECT_FALSE(s.empty());
}

// Tests the size() member function to return the size
TEST(BinarySearchTree, size) {
	const int TESTING_SIZE = 20;
	HTL::set<int> s;

	for (int i = 0; i < TESTING_SIZE; i++) {
		s.emplace(i);
	}

	EXPECT_EQ(TESTING_SIZE, s.size());
}

/* ----- Binary Search Tree Modifier Tests ----- */
// Tests the erase() member function to remove an element
TEST(BinarySearchTree, erase) {
	const int TESTING_SIZE = 10;
	double TESTING_VALUES[] = { 8.8, 4.4, 12.1, 1.1, 5.5, 9.9, 16.1, 11.1, 15.1, 10.0 };
	HTL::set<double> s;

	for (int i = 0; i < TESTING_SIZE; i++) {
		s.emplace(TESTING_VALUES[i]);
	}

	std::sort(std::begin(TESTING_VALUES), std::end(TESTING_VALUES));
	HTL::set<double>::iterator it;
	int i = 1;
	
	s.erase(s.begin());
	EXPECT_EQ(TESTING_SIZE - 1, s.size());

	for (it = s.begin(); it != s.end(); it++) {
		EXPECT_EQ(TESTING_VALUES[i], *it);
		i++;
	}
}

// Tests the clear() member function to empty out all the nodes
TEST(BinarySearchTree, clear) {
	const int TESTING_SIZE = 10;
	const double TESTING_VALUES[] = { 8.8, 4.4, 12.1, 1.1, 5.5, 9.9, 16.1, 11.1, 15.1, 10.0 };
	HTL::set<double> s;

	for (int i = 0; i < TESTING_SIZE; i++) {
		s.emplace(TESTING_VALUES[i]);
	}
	
	s.clear();
	EXPECT_EQ(0, s.size());
}

// Tests the emplace() member function to add an element
TEST(BinarySearchTree, emplace) {
	const int TESTING_SIZE = 50;
	int TESTING_VALUES[TESTING_SIZE];
	HTL::set<int> s;

	for (int i = 0; i < TESTING_SIZE; i++) {
		int value = i * (int)pow(-1, i);
		s.emplace(value);
		TESTING_VALUES[i] = value;
	}

	std::sort(std::begin(TESTING_VALUES), std::end(TESTING_VALUES));
	HTL::set<int>::iterator it;
	int i = 0;
	
	for (it = s.begin(); it != s.end(); it++) {
		EXPECT_EQ(TESTING_VALUES[i], *it);
		i++;
	}
}

/* ----- Binary Search Tree Operation Tests ----- */
// Tests the find() member function to return iterator to a given value
TEST(BinarySearchTree, find) {
	const int TESTING_SIZE = 5;
	const int TESTING_VALUES[] = { 5, 2, 7, 3, 6 };
	HTL::set<int> s;

	for (int i = 0; i < TESTING_SIZE; i++) {
		s.emplace(TESTING_VALUES[i]);
	}

	for (int i = 0; i < TESTING_SIZE; i++) {
		EXPECT_EQ(TESTING_VALUES[i], *(s.find(TESTING_VALUES[i])));
	}
}
#endif