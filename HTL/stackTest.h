#ifndef STACKTEST_H
#define STACKTEST_H

#include "stack.h"
#include "gtest/gtest.h"

// Tests the default constructor
TEST(Stack, defaultConstructorIsEmpty) {
	HTL::stack<int> s;
	
	EXPECT_EQ(0, s.size());
}

// Tests the copy constructor
TEST(Stack, copyConstructor) {
	const int TESTING_SIZE = 5;
	const int TESTING_VALUES[] = { 3, 2, 5, 4, 6 };
	HTL::stack<int> s;

	for (int i = 0; i < TESTING_SIZE; i++) {
		s.push(TESTING_VALUES[i]);
	}

	HTL::stack<int> s2(s);

	EXPECT_EQ(TESTING_SIZE, s2.size());
	for (int i = TESTING_SIZE - 1; i >= 0; i--) {
		EXPECT_EQ(TESTING_VALUES[i], s2.top());
		s2.pop();
	}
}

// Tests the = operator to copy another stack
TEST(Stack, equalOperator) {
	const int TESTING_SIZE = 10;
	const int TESTING_VALUES[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	HTL::stack<int> s, copy;

	for (int i = 0; i < TESTING_SIZE; i++) {
		copy.push(TESTING_VALUES[i]);
	}

	s = copy;
	for (int i = TESTING_SIZE - 1; i >= 0; i--) {
		EXPECT_EQ(TESTING_VALUES[i], s.top());
		s.pop();
	}
}


// Tests the empty() member function to return boolean value indicating if the stack is empty
TEST(Stack, empty) {
	const int TESTING_SIZE = 20;
	const double TESTING_VALUE = 1.68;
	HTL::stack<double> s;

	EXPECT_TRUE(s.empty());
	s.push(TESTING_VALUE);
	EXPECT_FALSE(s.empty());
}

// Tests the size() member function to return the size
TEST(Stack, size) {
	const int TESTING_SIZE = 20;
	HTL::stack<int> s;

	for (int i = 0; i < TESTING_SIZE; i++) {
		s.push(i);
	}

	EXPECT_EQ(TESTING_SIZE, s.size());
}

// Tests the top() member function to return reference to last node (top of stack)
TEST(Stack, top) {
	const int TESTING_SIZE = 10;
	const double TESTING_VALUES[] = { 2.3, 2.1, 1.9, 1.7, 1.5, 1.3, 1.1, 0.9, 0.7, 0.5 };
	HTL::stack<double> s;

	for (int i = 0; i < TESTING_SIZE; i++) {
		s.push(TESTING_VALUES[i]);
	}

	EXPECT_EQ(TESTING_VALUES[TESTING_SIZE - 1], s.top());
}

// Tests the push() member function to add a new node and change tail reference appropriately
TEST(Stack, push) {
	const int TESTING_SIZE = 5;
	const char TESTING_VALUES[] = { 'a', 'c', 'e', 'f', 'h' };
	HTL::stack<char> s;

	for (int i = 0; i < TESTING_SIZE; i++) {
		s.push(TESTING_VALUES[i]);
		EXPECT_EQ(TESTING_VALUES[i], s.top());
	}

	EXPECT_EQ(TESTING_SIZE, s.size());
}

// Tests the pop() member function to remove the tail node and decrease the size by one
TEST(Stack, pop) {
	const int TESTING_SIZE = 5;
	const int TESTING_VALUES[] = { 2, 4, 6, 8, 10 };
	HTL::stack<int> s;

	for (int i = 0; i < TESTING_SIZE; i++) {
		s.push(TESTING_VALUES[i]);
	}

	for (int i = TESTING_SIZE - 1; i >= 0; i--) {
		EXPECT_EQ(TESTING_VALUES[i], s.top());
		EXPECT_EQ(i+1, s.size());
		s.pop();
	}
}
#endif