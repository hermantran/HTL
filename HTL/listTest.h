#ifndef LISTTEST_H
#define LISTTEST_H

#include "list.h"
#include "gtest/gtest.h"

/* ----- Linked List Constructor Tests ----- */
// Tests the default constructor
TEST(LinkedList, defaultConstructorIsEmpty) {
	HTL::list<int> l;
	
	EXPECT_EQ(0, l.size());
}

// Tests the copy constructor
TEST(LinkedList, copyConstructor) {
	const int TESTING_SIZE = 5;
	const int TESTING_VALUES[] = { 3, 2, 5, 4, 6 };
	HTL::list<int> l;

	for (int i = 0; i < TESTING_SIZE; i++) {
		l.push_back(TESTING_VALUES[i]);
	}

	HTL::list<int> l2(l);
	HTL::list<int>::iterator it = l2.begin();

	EXPECT_EQ(TESTING_SIZE, l2.size());
	for (int i = 0; i < TESTING_SIZE; i++) {
		EXPECT_EQ(TESTING_VALUES[i], *it);
		*it++;
	}
}

// Tests the two args constructor which initializes the size and value
TEST(LinkedList, twoArgsConstructorInitSizeAndVal) {
	const int TESTING_SIZE = 20;
	const double TESTING_VALUE = 1.68;
	HTL::list<double> l(TESTING_SIZE, TESTING_VALUE);
	HTL::list<double>::iterator it(l);

	EXPECT_EQ(TESTING_SIZE, l.size());
	for (it = l.begin(); it != l.end(); it++) {
		EXPECT_EQ(TESTING_VALUE, *it);
	}
}


/* ----- Linked List Operator Tests ----- */
// Tests the = operator to copy another vector
TEST(LinkedList, equalOperator) {
	const int TESTING_SIZE = 10;
	const int TESTING_VALUES[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	HTL::list<int> l, copy;

	for (int i = 0; i < TESTING_SIZE; i++) {
		copy.push_back(TESTING_VALUES[i]);
	}

	l = copy;
	HTL::list<int>::iterator it = l.begin();
	for (int i = 0; i < TESTING_SIZE; i++) { 
		EXPECT_EQ(TESTING_VALUES[i], *it);
		*it++;
	}
}

/* ----- Linked List Iterator Tests ----- */
// Tests the begin() member function to return an iterator to the first node
TEST(LinkedList, begin) {
	const int TESTING_SIZE = 5;
	const int TESTING_VALUES[] = { 0, 1, 1, 2, 3 };
	HTL::list<int> l;

	for (int i = 0; i < TESTING_SIZE; i++) {
		l.push_back(TESTING_VALUES[i]);
	}

	EXPECT_EQ(TESTING_VALUES[0], *l.begin());
}

// Tests the end() member function to return an iterator to the last node
TEST(LinkedList, end) {
	const int TESTING_SIZE = 5;
	const int TESTING_VALUES[] = { 1, 3, 5, 7, 9 };
	HTL::list<int> l;

	for (int i = 0; i < TESTING_SIZE; i++) {
		l.push_back(TESTING_VALUES[i]);
	}
	EXPECT_EQ(TESTING_VALUES[TESTING_SIZE-1], *(l.end() -1));
}

// Tests the one arg linked list iterator constructor function with reference to linked list
TEST(LinkedList, iteratorOneArgConstrcutor) {
	const int TESTING_SIZE = 10;
	const int TESTING_VALUE = 3;
	HTL::list<int> l(TESTING_SIZE, TESTING_VALUE);
	HTL::list<int>::iterator it(l);

	EXPECT_EQ(l.front(), *it);
}

// Tests the two args linked list iterator constructor function with reference to list and starting index
TEST(LinkedList, iteratorTwoArgsConstrcutor) {
	const int TESTING_SIZE = 5;
	const int TESTING_INDEX = 3;
	const int TESTING_VALUES[] = { 1, 2, 6, 24, 120 }; 
	HTL::list<int> l;

	for (int i = 0; i < TESTING_SIZE; i++) {
		l.push_back(TESTING_VALUES[i]);
	}

	HTL::list<int>::iterator it(l, TESTING_INDEX);
	EXPECT_EQ(TESTING_VALUES[TESTING_INDEX], *it);
}

// Tests the linked list iterator copy constructor function
TEST(LinkedList, iteratorCopyConstructor) {
	const int TESTING_SIZE = 5;
	const int TESTING_INDEX = 3;
	const int TESTING_VALUES[] = { 1, 2, 6, 24, 120 }; 
	HTL::list<int> l;

	for (int i = 0; i < TESTING_SIZE; i++) {
		l.push_back(TESTING_VALUES[i]);
	}

	HTL::list<int>::iterator copy = l.begin() + TESTING_INDEX;
	HTL::list<int>::iterator it(copy);
	EXPECT_EQ(TESTING_VALUES[TESTING_INDEX], *it);
}

// Tests the equality operator function to compare two iterators
TEST(LinkedList, iteratorEqualityOperator) {
	const int TESTING_SIZE = 3;
	const char TESTING_VALUES[] = { 'x', 'y', 'z' };
	HTL::list<char> l;

	for (int i = 0; i < TESTING_SIZE; i++) {
		l.push_back(TESTING_VALUES[i]);
	}

	HTL::list<char>::iterator it = l.begin();
	EXPECT_TRUE(it == l.begin());
	for (int i = 1; i < TESTING_SIZE; i++) {
		EXPECT_FALSE(it + i == l.begin());
	}
}

// Tests the inequality operator function to compare two iterators
TEST(LinkedList, iteratorInequalityOperator) {
	const int TESTING_SIZE = 3;
	const char TESTING_VALUES[] = { 'x', 'y', 'z' };
	HTL::list<char> l;

	for (int i = 0; i < TESTING_SIZE; i++) {
		l.push_back(TESTING_VALUES[i]);
	}

	HTL::list<char>::iterator it = l.begin();
	EXPECT_FALSE(it != l.begin());
	for (int i = 1; i < TESTING_SIZE; i++) {
		EXPECT_TRUE(it + i != l.begin());
	}
}

// Tests the dereference operator to return the node value
TEST(LinkedList, iteratorDeferenceOperator) {
	const char TESTING_VALUE = 'a';
	HTL::list<char> l;

	l.push_back(TESTING_VALUE);

	HTL::list<char>::iterator it = l.begin();
	EXPECT_EQ(TESTING_VALUE, *it);
}

// Tests the equal operator to assign the other iterator's node correctly
TEST(LinkedList, iteratorEqualOperator) {
	const int TESTING_SIZE = 5;
	const int TESTING_INDEX = 3;
	const char TESTING_VALUES[] = { 'a', 'b', 'c', 'd', 'e' };
	HTL::list<char> l;

	for (int i = 0; i < TESTING_SIZE; i++) {
		l.push_back(TESTING_VALUES[i]);
	}

	HTL::list<char>::iterator it = l.begin() + TESTING_INDEX;
	HTL::list<char>::iterator it2;
	it2 = it;
	EXPECT_EQ(TESTING_VALUES[TESTING_INDEX], *it2);
}

// Tests the pre-increment operator function to go to next node and return iterator at that node
TEST(LinkedList, iteratorPreIncrementOperator) {
	const int TESTING_SIZE = 10;
	const double TESTING_VALUES[] = { 0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };
	HTL::list<double> l;

	for (int i = 0; i < TESTING_SIZE; i++) {
		l.push_back(TESTING_VALUES[i]);
	}

	HTL::list<double>::iterator it = l.begin();

	for (int i = 0; i < TESTING_SIZE - 1; ++i) {
		EXPECT_EQ(TESTING_VALUES[i+1], *(++it));
	}
}

// Tests the post-increment operator function to go to next node and return iterator at old node 
TEST(LinkedList, iteratorPostIncrementOperator) {
	const int TESTING_SIZE = 10;
	const double TESTING_VALUES[] = { 0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };
	HTL::list<double> l;

	for (int i = 0; i < TESTING_SIZE; i++) {
		l.push_back(TESTING_VALUES[i]);
	}

	HTL::list<double>::iterator it = l.begin();

	for (int i = 0; i < TESTING_SIZE; i++) {
		EXPECT_EQ(TESTING_VALUES[i], *(it++));
	}
}

// Tests the pre-decrement operator function to go to previous node and return iterator at that node
TEST(LinkedList, iteratorPreDecrementOperator) {
	const int TESTING_SIZE = 5;
	const int TESTING_VALUES[] = { 4, 5, 6, 7, 8 };
	HTL::list<int> l;

	for (int i = 0; i < TESTING_SIZE; i++) {
		l.push_back(TESTING_VALUES[i]);
	}

	HTL::list<int>::iterator it = l.end();

	for (int i = TESTING_SIZE - 1; i >= 0; --i) {
		EXPECT_EQ(TESTING_VALUES[i], *(--it));
	}
}

// Tests the post-decrement operator function to go to previous node and return iterator at that node
TEST(LinkedList, iteratorPostDecrementOperator) {
	const int TESTING_SIZE = 5;
	const int TESTING_VALUES[] = { 4, 5, 6, 7, 8 };
	HTL::list<int> l;

	for (int i = 0; i < TESTING_SIZE; i++) {
		l.push_back(TESTING_VALUES[i]);
	}

	HTL::list<int>::iterator it = l.end();
	it--;

	for (int i = TESTING_SIZE - 1; i >= 0; i--) {
		EXPECT_EQ(TESTING_VALUES[i], *(it--));
	}
}


/* ----- Linked List Capacity Tests ----- */
// Tests the size() member function to return the size
TEST(LinkedList, size) {
	const int TESTING_SIZE = 20;
	HTL::list<int> l;

	for (int i = 0; i < TESTING_SIZE; i++) {
		l.push_back(i);
	}

	EXPECT_EQ(TESTING_SIZE, l.size());
}


/* ----- Linked List Element Tests ----- */
// Tests the front() member function to return reference to first element
TEST(LinkedList, front) {
	const int TESTING_SIZE = 10;
	const double TESTING_VALUES[] = { 2.3, 2.1, 1.9, 1.7, 1.5, 1.3, 1.1, 0.9, 0.7, 0.5 };
	HTL::list<double> l;

	for (int i = 0; i < TESTING_SIZE; i++) {
		l.push_back(TESTING_VALUES[i]);
	}

	EXPECT_EQ(TESTING_VALUES[0], l.front());
}

// Tests the back() member function to return reference to last node
TEST(LinkedList, back) {
	const int TESTING_SIZE = 10;
	const double TESTING_VALUES[] = { 2.3, 2.1, 1.9, 1.7, 1.5, 1.3, 1.1, 0.9, 0.7, 0.5 };
	HTL::list<double> l;

	for (int i = 0; i < TESTING_SIZE; i++) {
		l.push_back(TESTING_VALUES[i]);
	}

	EXPECT_EQ(TESTING_VALUES[TESTING_SIZE-1], l.back());
}


/* ----- Linked List Modifier Tests ----- */
// Tests the push_back() member function to add a new node and change tail reference appropriately
TEST(LinkedList, push_back) {
	const int TESTING_SIZE = 5;
	const char TESTING_VALUES[] = { 'a', 'c', 'e', 'f', 'h' };
	HTL::list<int> l;

	for (int i = 0; i < TESTING_SIZE; i++) {
		l.push_back(TESTING_VALUES[i]);
	}

	HTL::list<int>::iterator it = l.begin();

	for (int i = 0; i < TESTING_SIZE; i++) {
		EXPECT_EQ(TESTING_VALUES[i], *it);
		it++;
	}
	EXPECT_EQ(TESTING_SIZE, l.size());
}

// Tests the push_front() member function to add a new node and change head reference appropriately
TEST(LinkedList, push_front) {
	const int TESTING_SIZE = 5;
	const char TESTING_VALUES[] = { 'a', 'c', 'e', 'f', 'h' };
	HTL::list<char> l;

	for (int i = 0; i < TESTING_SIZE; i++) {
		l.push_front(TESTING_VALUES[i]);
	}

	HTL::list<char>::iterator it = l.end() - 1;

	for (int i = 0; i < TESTING_SIZE; i++) {
		EXPECT_EQ(TESTING_VALUES[i], *it);
		it--;
	}
	EXPECT_EQ(TESTING_SIZE, l.size());
}

// Tests the pop_back() member function to remove the tail node and decrease the size by one
TEST(LinkedList, pop_back) {
	const int TESTING_SIZE = 5;
	const int TESTING_VALUES[] = { 2, 4, 6, 8, 10 };
	HTL::list<int> l;

	for (int i = 0; i < TESTING_SIZE; i++) {
		l.push_back(TESTING_VALUES[i]);
	}

	l.pop_back();
	HTL::list<int>::iterator it = l.begin();

	for (int i = 0; i < TESTING_SIZE - 1; i++) {
		EXPECT_EQ(TESTING_VALUES[i], *it);
		*it++;
	}
	EXPECT_EQ(TESTING_SIZE - 1, l.size());
}

// Tests the pop_front() member function to remove the head node and decrease the size by one
TEST(LinkedList, pop_front) {
	const int TESTING_SIZE = 5;
	const int TESTING_VALUES[] = { 2, 4, 6, 8, 10 };
	HTL::list<int> l;

	for (int i = 0; i < TESTING_SIZE; i++) {
		l.push_back(TESTING_VALUES[i]);
	}

	l.pop_front();
	HTL::list<int>::iterator it = l.begin();

	for (int i = 1; i < TESTING_SIZE; i++) {
		EXPECT_EQ(TESTING_VALUES[i], *it);
		*it++;
	}

	EXPECT_EQ(TESTING_SIZE - 1, l.size());
}

// Tests the erase() member function to remove a node and shift later elements accordingly
TEST(LinkedList, erase) {
	const char TESTING_SIZE = 5;
	const char TESTING_VALUES[] = { 'b', 'c', 'd', 'e', 'f' };
	const int ERASE_POSITION = 2;
	HTL::list<char> l;

	for (int i = 0; i < TESTING_SIZE; i++) {
		l.push_back(TESTING_VALUES[i]);
	}

	HTL::list<char>::iterator it = l.erase(l.begin() + ERASE_POSITION);
	EXPECT_EQ(TESTING_VALUES[ERASE_POSITION + 1], *it);

	it = l.begin();
	for (int i = 0; i < ERASE_POSITION; i++) {
		EXPECT_EQ(TESTING_VALUES[i], *it);
		*it++;
	}
	for (int i = ERASE_POSITION; i < TESTING_SIZE - 1; i++) {
		EXPECT_EQ(TESTING_VALUES[i+1], *it);
		*it++;
	}
	EXPECT_EQ(TESTING_SIZE - 1, l.size());
}

// Tests the clear() member function to remove all nodes
TEST(LinkedList, clear) {
	const char TESTING_SIZE = 5;
	const char TESTING_VALUE = 'a';
	HTL::list<char> v(TESTING_SIZE, TESTING_VALUE);

	v.clear();
	EXPECT_EQ(0, v.size());
}

#endif