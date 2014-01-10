#ifndef QUEUETEST_H
#define QUEUETEST_H

#include "queue.h"
#include "gtest/gtest.h"

// Tests the default constructor
TEST(Queue, defaultConstructorIsEmpty) {
	HTL::queue<int> q;
	
	EXPECT_EQ(0, q.size());
}

// Tests the copy constructor
TEST(Queue, copyConstructor) {
	const int TESTING_SIZE = 5;
	const int TESTING_VALUES[] = { 3, 2, 5, 4, 6 };
	HTL::queue<int> q;

	for (int i = 0; i < TESTING_SIZE; i++) {
		q.push(TESTING_VALUES[i]);
	}

	HTL::queue<int> q2(q);

	EXPECT_EQ(TESTING_SIZE, q2.size());
	for (int i = 0; i < TESTING_SIZE; i++) {
		EXPECT_EQ(TESTING_VALUES[i], q2.front());
		q2.pop();
	}
}

// Tests the = operator to copy another queue
TEST(Queue, equalOperator) {
	const int TESTING_SIZE = 10;
	const int TESTING_VALUES[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	HTL::queue<int> q, copy;

	for (int i = 0; i < TESTING_SIZE; i++) {
		copy.push(TESTING_VALUES[i]);
	}

	q = copy;
	for (int i = 0; i < TESTING_SIZE; i++) {
		EXPECT_EQ(TESTING_VALUES[i], q.front());
		q.pop();
	}
}


// Tests the empty() member function to return boolean value indicating if the queue is empty
TEST(Queue, empty) {
	const int TESTING_SIZE = 20;
	const double TESTING_VALUE = 1.68;
	HTL::queue<double> q;

	EXPECT_TRUE(q.empty());
	q.push(TESTING_VALUE);
	EXPECT_FALSE(q.empty());
}

// Tests the size() member function to return the size
TEST(Queue, size) {
	const int TESTING_SIZE = 20;
	HTL::queue<int> q;

	for (int i = 0; i < TESTING_SIZE; i++) {
		q.push(i);
	}

	EXPECT_EQ(TESTING_SIZE, q.size());
}

// Tests the front() member function to return reference to first node (front of queue)
TEST(Queue, front) {
	const int TESTING_SIZE = 10;
	const double TESTING_VALUES[] = { 2.3, 2.1, 1.9, 1.7, 1.5, 1.3, 1.1, 0.9, 0.7, 0.5 };
	HTL::queue<double> q;

	for (int i = 0; i < TESTING_SIZE; i++) {
		q.push(TESTING_VALUES[i]);
	}

	EXPECT_EQ(TESTING_VALUES[0], q.front());
}

// Tests the back() member function to return reference to last node (back of queue)
TEST(Queue, back) {
	const int TESTING_SIZE = 10;
	const double TESTING_VALUES[] = { 2.3, 2.1, 1.9, 1.7, 1.5, 1.3, 1.1, 0.9, 0.7, 0.5 };
	HTL::queue<double> q;

	for (int i = 0; i < TESTING_SIZE; i++) {
		q.push(TESTING_VALUES[i]);
	}

	EXPECT_EQ(TESTING_VALUES[TESTING_SIZE - 1], q.back());
}

// Tests the push() member function to add a new node and change tail reference appropriately
TEST(Queue, push) {
	const int TESTING_SIZE = 5;
	const char TESTING_VALUES[] = { 'a', 'c', 'e', 'f', 'h' };
	HTL::queue<char> q;

	for (int i = 0; i < TESTING_SIZE; i++) {
		q.push(TESTING_VALUES[i]);
		EXPECT_EQ(TESTING_VALUES[i], q.back());
	}

	EXPECT_EQ(TESTING_SIZE, q.size());
}

// Tests the pop() member function to remove the head node and decrease the size by one
TEST(Queue, pop) {
	const int TESTING_SIZE = 5;
	const int TESTING_VALUES[] = { 2, 4, 6, 8, 10 };
	HTL::queue<int> q;

	for (int i = 0; i < TESTING_SIZE; i++) {
		q.push(TESTING_VALUES[i]);
	}

	for (int i = 0; i < TESTING_SIZE; i++) {
		EXPECT_EQ(TESTING_VALUES[i], q.front());
		EXPECT_EQ(TESTING_SIZE - i, q.size());
		q.pop();
	}
}
#endif