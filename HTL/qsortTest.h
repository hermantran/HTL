#ifndef QSORTTEST_H
#define QSORTTEST_H

#include <iostream>
#include "qsort.h"
#include "gtest/gtest.h"
#include "vector.h"
#include "list.h"
#include "map.h"

TEST(QuickSort, vectorComplete) {
	HTL::vector<int> v;
	int TESTING_VALUES[] = { 45, 44, 43, 42, 41, 40 };
	int TESTING_LENGTH = 6;
	for (int i = 0; i < TESTING_LENGTH; i++) {
		v.push_back(TESTING_VALUES[i]);
	}

	HTL::quicksort(v, 0, TESTING_LENGTH - 1);
	std::sort(std::begin(TESTING_VALUES), std::end(TESTING_VALUES));
	for (int i = 0; i < TESTING_LENGTH; i++) {
		EXPECT_EQ(TESTING_VALUES[i], v[i]);
	}

}

TEST(QuickSort, vectorPartial) {
	HTL::vector<int> v;
	const int TESTING_LENGTH = 30;
	const int TESTING_INDEX = 10;
	for (int i = 0; i < TESTING_LENGTH; i++) {
		v.push_back(-i);
	}

	HTL::quicksort(v, 0, TESTING_INDEX);
	for (int i = 0; i < TESTING_INDEX; i++) {
		EXPECT_EQ(-(TESTING_INDEX - i), v[i]);
	}
	for (int i = TESTING_INDEX + 1; i < TESTING_LENGTH; i++) {
		EXPECT_EQ(-i, v[i]);
	}
}

TEST(QuickSort, linkedListComplete) {
	HTL::list<int> l;
	int TESTING_VALUES[] = { 45, 44, 43, 42, 41, 40 };
	int TESTING_LENGTH = 6;
	for (int i = 0; i < TESTING_LENGTH; i++) {
		l.push_back(TESTING_VALUES[i]);
	}

	HTL::quicksort(l, 0, TESTING_LENGTH - 1);
	std::sort(std::begin(TESTING_VALUES), std::end(TESTING_VALUES));
	for (int i = 0; i < TESTING_LENGTH; i++) {
		EXPECT_EQ(TESTING_VALUES[i], *(l.begin() + i));
	}
}

TEST(QuickSort, linkedListPartial) {
	HTL::vector<int> l;
	const int TESTING_LENGTH = 30;
	const int TESTING_INDEX = 10;
	for (int i = 0; i < TESTING_LENGTH; i++) {
		l.push_back(-i);
	}

	HTL::quicksort(l, 0, TESTING_INDEX);
	for (int i = 0; i < TESTING_INDEX; i++) {
		EXPECT_EQ(-(TESTING_INDEX - i), *(l.begin() + i));
	}
	for (int i = TESTING_INDEX + 1; i < TESTING_LENGTH; i++) {
		EXPECT_EQ(-i, *(l.begin() + i));
	}
}
#endif