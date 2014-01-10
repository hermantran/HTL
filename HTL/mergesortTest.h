#ifndef MERGESORTTEST_H
#define MERGESORTTEST_H

#include <iostream>
#include <algorithm>
#include "mergesort.h"
#include "gtest/gtest.h"
#include "vector.h"
#include "list.h"

TEST(MergeSort, vector) {
	HTL::vector<int> v;
	int TESTING_VALUES[] = { 45, 44, 43, 42, 41, 40 };
	int TESTING_LENGTH = 6;
	for (int i = 0; i < TESTING_LENGTH; i++) {
		v.push_back(TESTING_VALUES[i]);
	}

	v = HTL::merge_sort(v);
	std::sort(std::begin(TESTING_VALUES), std::end(TESTING_VALUES));
	for (int i = 0; i < TESTING_LENGTH; i++) {
		EXPECT_EQ(TESTING_VALUES[i], v[i]);
	}

}

TEST(MergeSort, linkedList) {
	HTL::list<int> l;
	int TESTING_VALUES[] = { 45, 44, 43, 42, 41, 40 };
	int TESTING_LENGTH = 6;
	for (int i = 0; i < TESTING_LENGTH; i++) {
		l.push_back(TESTING_VALUES[i]);
	}

	l = HTL::merge_sort(l);
	std::sort(std::begin(TESTING_VALUES), std::end(TESTING_VALUES));
	for (int i = 0; i < TESTING_LENGTH; i++) {
		EXPECT_EQ(TESTING_VALUES[i], *(l.begin() + i));
	}
}
#endif