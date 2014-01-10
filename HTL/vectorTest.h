#ifndef VECTORTEST_H
#define VECTORTEST_H

#include "vector.h"
#include "gtest/gtest.h"

/* ----- Vector Constructor Tests ----- */
// Tests the default constructor
TEST(Vector, defaultConstructorIsEmpty) {
	HTL::vector<int> v;

    EXPECT_EQ(0, v.size());
	EXPECT_EQ(0, v.capacity());
}

// Tests the copy constructor
TEST(Vector, copyConstructor) {
	const int TESTING_SIZE = 5;
	const int TESTING_VALUES[] = { 3, 2, 5, 4, 6 };
	HTL::vector<int> v(TESTING_SIZE);

	for (int i = 0; i < TESTING_SIZE; i++) {
		v[i] = TESTING_VALUES[i];
	}

	HTL::vector<int> v2(v);

	EXPECT_EQ(TESTING_SIZE, v2.size());
	EXPECT_EQ(v.capacity(), v2.capacity());
	for (int i = 0; i < TESTING_SIZE; i++) {
		EXPECT_EQ(TESTING_VALUES[i], v2[i]);
	}
}

// Tests the one arg constructor which initalizes the size (and capacity)
TEST(Vector, oneArgConstructorInitsSize) {
	const int TESTING_SIZE = 15;
	HTL::vector<float> v(TESTING_SIZE);

	EXPECT_EQ(TESTING_SIZE, v.size());
	EXPECT_EQ(TESTING_SIZE, v.capacity());
}

// Tests the two args constructor which initializes the size (and capacity) and value
TEST(Vector, twoArgsConstructorInitSizeAndVal) {
	const int TESTING_SIZE = 20;
	const double TESTING_VALUE = 1.68;
	HTL::vector<double> v(TESTING_SIZE, TESTING_VALUE);

	EXPECT_EQ(TESTING_SIZE, v.size());
	EXPECT_EQ(TESTING_SIZE, v.capacity());
	for (int i = 0; i < TESTING_SIZE; i++) {
		EXPECT_EQ(TESTING_VALUE, v[i]);
	}
}


/* ----- Vector Operator Tests ----- */
// Tests the [] operator getter/setter methods
TEST(Vector, squareBracketsOperator) {
	const int TESTING_SIZE = 5;
	const int TESTING_VALUES[] = { 1, 1, 2, 3, 5 }; 
	HTL::vector<int> v(TESTING_SIZE);

	for (int i = 0; i < TESTING_SIZE; i++) {
		v[i] = TESTING_VALUES[i];
		EXPECT_EQ(TESTING_VALUES[i], v[i]); 
	}
}

// Tests the = operator to copy another vector
TEST(Vector, equalOperator) {
	const int TESTING_SIZE = 10;
	const int TESTING_VALUES[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	HTL::vector<int> v, copy(10);

	for (int i = 0; i < TESTING_SIZE; i++) {
		copy[i] = TESTING_VALUES[i];
	}

	v = copy;
	for (int i = 0; i < TESTING_SIZE; i++) {
		EXPECT_EQ(TESTING_VALUES[i], v[i]);
	}
}


/* ----- Vector Iterator Tests ----- */
// Tests the begin() member function to return an iterator to the first element
TEST(Vector, begin) {
	const int TESTING_SIZE = 5;
	const int TESTING_VALUES[] = { 0, 1, 1, 2, 3 };
	HTL::vector<int> v(TESTING_SIZE);

	for (int i = 0; i < TESTING_SIZE; i++) {
		v[i] = TESTING_VALUES[i];
	}

	EXPECT_EQ(TESTING_VALUES[0], *v.begin());
}

// Tests the end() member function to return an iterator to the last element
TEST(Vector, end) {
	const int TESTING_SIZE = 5;
	const int TESTING_VALUES[] = { 1, 3, 5, 7, 9 };
	HTL::vector<int> v(TESTING_SIZE);

	for (int i = 0; i < TESTING_SIZE; i++) {
		v[i] = TESTING_VALUES[i];
	}
	
	EXPECT_EQ(TESTING_VALUES[TESTING_SIZE-1], *v.end());
}

// Tests the one arg vector iterator constructor function with reference to vector
TEST(Vector, iteratorOneArgConstrcutor) {
	const int TESTING_SIZE = 10;
	const int TESTING_VALUE = 3;
	HTL::vector<int> v(TESTING_SIZE, TESTING_VALUE);
	HTL::vector<int>::iterator it(v);

	EXPECT_EQ(v[0], *it);
}

// Tests the two arg vector iterator constructor function with reference to vector and starting index
TEST(Vector, iteratorTwoArgsConstrcutor) {
	const int TESTING_SIZE = 5;
	const int TESTING_VALUES[] = { 1, 2, 6, 24, 120 }; 
	HTL::vector<int> v(TESTING_SIZE);
	HTL::vector<int>::iterator it(v);

	for (int i = 0; i < TESTING_SIZE; i++) {
		v[i] = TESTING_VALUES[i];
	}

	EXPECT_EQ(v[TESTING_SIZE - 1], *(it + TESTING_SIZE - 1));
}

// Tests the equality operator function to compare two iterators
TEST(Vector, iteratorEqualityOperator) {
	const int TESTING_SIZE = 3;
	const char TESTING_VALUES[] = { 'x', 'y', 'z' };
	HTL::vector<char> v(TESTING_SIZE);

	for (int i = 0; i < TESTING_SIZE; i++) {
		v[i] = TESTING_VALUES[i];
	}

	HTL::vector<char>::iterator it = v.begin();
	EXPECT_TRUE(it == v.begin());
	for (int i = 1; i < TESTING_SIZE; i++) {
		EXPECT_FALSE(it + i == v.begin());
	}
}

// Tests the inequality operator function to compare two iterators
TEST(Vector, iteratorInequalityOperator) {
	const int TESTING_SIZE = 3;
	const char TESTING_VALUES[] = { 'x', 'y', 'z' };
	HTL::vector<char> v(TESTING_SIZE);

	for (int i = 0; i < TESTING_SIZE; i++) {
		v[i] = TESTING_VALUES[i];
	}

	HTL::vector<char>::iterator it = v.begin();
	EXPECT_FALSE(it != v.begin());
	for (int i = 1; i < TESTING_SIZE; i++) {
		EXPECT_TRUE(it + i != v.begin());
	}
}

// Tests the pre-increment operator function to increase index by 1 and return iterator at new index 
TEST(Vector, iteratorPreIncrementOperator) {
	const int TESTING_SIZE = 10;
	const double TESTING_VALUES[] = { 0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };
	HTL::vector<double> v(TESTING_SIZE);

	for (int i = 0; i < TESTING_SIZE; i++) {
		v[i] = TESTING_VALUES[i];
	}

	HTL::vector<double>::iterator it = v.begin();

	for (int i = 0; i < TESTING_SIZE - 1; ++i) {
		EXPECT_EQ(TESTING_VALUES[i+1], *(++it));
	}
}

// Tests the post-increment operator function to increase index by 1 and return iterator at old index 
TEST(Vector, iteratorPostIncrementOperator) {
	const int TESTING_SIZE = 10;
	const double TESTING_VALUES[] = { 0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };
	HTL::vector<double> v(TESTING_SIZE);

	for (int i = 0; i < TESTING_SIZE; i++) {
		v[i] = TESTING_VALUES[i];
	}

	HTL::vector<double>::iterator it = v.begin();

	for (int i = 0; i < TESTING_SIZE; i++) {
		EXPECT_EQ(TESTING_VALUES[i], *(it++));
	}
}

// Tests the pre-decrement operator function to decrease index by 1 and return iterator at new index 
TEST(Vector, iteratorPreDecrementOperator) {
	const int TESTING_SIZE = 5;
	const int TESTING_VALUES[] = { 4, 5, 6, 7, 8 };
	HTL::vector<int> v(TESTING_SIZE);

	for (int i = 0; i < TESTING_SIZE; i++) {
		v[i] = TESTING_VALUES[i];
	}

	HTL::vector<int>::iterator it = v.end();

	for (int i = TESTING_SIZE - 1; i > 0; --i) {
		EXPECT_EQ(TESTING_VALUES[i-1], *(--it));
	}
}

// Tests the post-decrement operator function to decrease index by 1 and return iterator at old index 
TEST(Vector, iteratorPostDecrementOperator) {
	const int TESTING_SIZE = 5;
	const int TESTING_VALUES[] = { 4, 5, 6, 7, 8 };
	HTL::vector<int> v(TESTING_SIZE);

	for (int i = 0; i < TESTING_SIZE; i++) {
		v[i] = TESTING_VALUES[i];
	}

	HTL::vector<int>::iterator it = v.end();

	for (int i = TESTING_SIZE - 1; i > 0; i--) {
		EXPECT_EQ(TESTING_VALUES[i], *(it--));
	}
}


/* ----- Vector Capacity Tests ----- */
// Tests the size() member function to return the size
TEST(Vector, size) {
	const int TESTING_SIZE = 20;
	HTL::vector<int> v(TESTING_SIZE);

	EXPECT_EQ(TESTING_SIZE, v.size());
}

// Tests the capacity() member function to return the capacity
TEST(Vector, capacity) {
	const int TESTING_SIZE = 10;
	HTL::vector<int> v(TESTING_SIZE);

	EXPECT_EQ(TESTING_SIZE, v.capacity());
}

// Tests the resize() member function to decrease the vector size
TEST(Vector, resizeSmaller) {
	const int TESTING_SIZE = 5, RESIZE_SIZE = 3;
	const double TESTING_VALUES[] = { 0.1, 0.3, 0.5, 0.7, 0.9 };
	HTL::vector<double> v(TESTING_SIZE);

	for (int i = 0; i < TESTING_SIZE; i++) {
		v[i] = TESTING_VALUES[i];
	}

	v.resize(RESIZE_SIZE);
	EXPECT_EQ(RESIZE_SIZE, v.size());
	for (int i = 0; i < RESIZE_SIZE; i++) {
		EXPECT_EQ(TESTING_VALUES[i], v[i]);
	}
}

// Tests the resize() member function to increase the vector size
TEST(Vector, resizeLarger) {
	const int TESTING_SIZE = 5, RESIZE_SIZE = 9;
	const char TESTING_VALUES[] = { 'a', 'c', 'e', 'f', 'h', 'j', 'l', 'n', 'p'};
	HTL::vector<char> v(TESTING_SIZE);

	for (int i = 0; i < TESTING_SIZE; i++) {
		v[i] = TESTING_VALUES[i];
	}

	// Use push_back() to have capacity larger than both TESTING_SIZE and RESIZE_SIZE
	// Want the vector to have _capcity > _size before using resize()
	v.push_back(TESTING_VALUES[TESTING_SIZE]);

	// Ensure capacity is larger than RESIE_VALUE after push_back()
	EXPECT_LT(RESIZE_SIZE, v.capacity());

	v.resize(RESIZE_SIZE);
	for (int i = TESTING_SIZE + 1; i < RESIZE_SIZE; i++) {
		v[i] = TESTING_VALUES[i];
	}

	EXPECT_EQ(RESIZE_SIZE, v.size());
	for (int i = 0; i < RESIZE_SIZE; i++) {
		EXPECT_EQ(TESTING_VALUES[i], v[i]);
	}
}

// Tests the resize() member function to increase both size and capacity
TEST(Vector, resizeLargerThanCapacity) {
	const int TESTING_SIZE = 5, RESIZE_SIZE = 10;
	const int TESTING_VALUES[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	HTL::vector<int> v(TESTING_SIZE);

	for (int i = 0; i < TESTING_SIZE; i++) {
		v[i] = TESTING_VALUES[i];
	}

	EXPECT_GT(RESIZE_SIZE, v.capacity());

	v.resize(RESIZE_SIZE);
	for (int i = TESTING_SIZE; i < RESIZE_SIZE; i++) {
		v[i] = TESTING_VALUES[i];
	}

	EXPECT_EQ(RESIZE_SIZE, v.size());
	for (int i = 0; i < RESIZE_SIZE; i++) {
		EXPECT_EQ(TESTING_VALUES[i], v[i]);
	}
}


/* ----- Vector Element Tests ----- */
// Tests the front() member function to return reference to first element
TEST(Vector, front) {
	const int TESTING_SIZE = 10;
	const double TESTING_VALUES[] = { 2.3, 2.1, 1.9, 1.7, 1.5, 1.3, 1.1, 0.9, 0.7, 0.5 };
	HTL::vector<double> v(TESTING_SIZE);

	for (int i = 0; i < TESTING_SIZE; i++) {
		v[i] = TESTING_VALUES[i];
	}

	EXPECT_EQ(TESTING_VALUES[0], v.front());
}

// Tests the back() member function to return reference to last element
TEST(Vector, back) {
	const int TESTING_SIZE = 10;
	const double TESTING_VALUES[] = { 2.3, 2.1, 1.9, 1.7, 1.5, 1.3, 1.1, 0.9, 0.7, 0.5 };
	HTL::vector<double> v(TESTING_SIZE);

	for (int i = 0; i < TESTING_SIZE; i++) {
		v[i] = TESTING_VALUES[i];
	}

	EXPECT_EQ(TESTING_VALUES[TESTING_SIZE-1], v.back());
}


/* ----- Vector Modifier Tests ----- */
// Tests the push_back() member function to preserve the old elements, increase capacity, and add the new element
TEST(Vector, push_back) {
	const int TESTING_SIZE = 5;
	const char TESTING_VALUES[] = { 'a', 'c', 'e', 'f', 'h' };
	const char TESTING_VALUE = 'j';
	HTL::vector<int> v(TESTING_SIZE);

	for (int i = 0; i < TESTING_SIZE; i++) {
		v[i] = TESTING_VALUES[i];
	}

	v.push_back(TESTING_VALUE);

	for (int i = 0; i < TESTING_SIZE; i++) {
		EXPECT_EQ(TESTING_VALUES[i], v[i]);
	}
	EXPECT_EQ(TESTING_SIZE * 2, v.capacity());
	EXPECT_EQ(TESTING_VALUE, v[TESTING_SIZE]);
	EXPECT_EQ(TESTING_SIZE+1, v.size());
}


// Tests the pop_back() member function to remove the last element and decrease the size by one
TEST(Vector, pop_back) {
	const int TESTING_SIZE = 5;
	const int TESTING_VALUES[] = { 2, 4, 6, 8, 10 };
	HTL::vector<int> v(TESTING_SIZE);

	for (int i = 0; i < TESTING_SIZE; i++) {
		v[i] = TESTING_VALUES[i];
	}

	v.pop_back();

	for (int i = 0; i < TESTING_SIZE - 1; i++) {
		EXPECT_EQ(TESTING_VALUES[i], v[i]);
	}
	EXPECT_EQ(TESTING_SIZE - 1, v.size());
}

// Tests the erase() member function to remove an element and shift later elements accordingly
TEST(Vector, erase) {
	const char TESTING_SIZE = 5;
	const char TESTING_VALUES[] = { 'b', 'c', 'd', 'e', 'f' };
	const int ERASE_POSITION = 3;
	HTL::vector<char> v(TESTING_SIZE);

	for (int i = 0; i < TESTING_SIZE; i++) {
		v[i] = TESTING_VALUES[i];
	}

	v.erase(v.begin() + ERASE_POSITION);
	for (int i = 0; i < ERASE_POSITION; i++) {
		EXPECT_EQ(TESTING_VALUES[i], v[i]);
	}
	for (int i = ERASE_POSITION; i < TESTING_SIZE - 1; i++) {
		EXPECT_EQ(TESTING_VALUES[i+1], v[i]);
	}
	EXPECT_EQ(TESTING_SIZE - 1, v.size());
}

// Tests the clear() member function to remove all elements
TEST(Vector, clear) {
	const char TESTING_SIZE = 5;
	const char TESTING_VALUE = 'a';
	HTL::vector<char> v(TESTING_SIZE, TESTING_VALUE);

	v.clear();
	EXPECT_EQ(0, v.capacity());
	EXPECT_EQ(0, v.size());
}

#endif