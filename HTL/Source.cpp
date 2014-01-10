#include <iostream>
#include "vectorTest.h"
#include "listTest.h"
#include "stackTest.h"
#include "queueTest.h"
#include "mapTest.h"
#include "setTest.h"
#include "qsortTest.h"
#include "mergesortTest.h"

// Set up Google Test: http://stackoverflow.com/questions/531941/how-to-setup-google-c-testing-framework-gtest-on-visual-studio-2005
// Fix Google Test for VS 2012: http://stackoverflow.com/questions/12558327/google-test-in-visual-studio-2012
// Google Test Primer: https://code.google.com/p/googletest/wiki/Primer

int promptUser();
void runGoogleTest(int argc, char** argv, std::string testSuite);

int main(int argc, char** argv) {
	int input = 1;
	enum TestSuite { Vector = 1, LinkedList, Stack, Queue, HashTable, BinarySearchTree, QuickSort, MergeSort };

	std::cout << "HTL supports the following data structures / algorithms." << std::endl;

	while (input != 0) {
		input = promptUser();

		if (input == Vector) {
			runGoogleTest(argc, argv, "Vector*");
		}
		else if (input == LinkedList) {
			runGoogleTest(argc, argv, "LinkedList*");
		}
		else if (input == Stack) {
			runGoogleTest(argc, argv, "Stack*");
		}
		else if (input == Queue) {
			runGoogleTest(argc, argv, "Queue*");
		}
		else if (input == HashTable) {
			runGoogleTest(argc, argv, "HashTable*");
		}
		else if (input == BinarySearchTree) {
			runGoogleTest(argc, argv, "BinarySearchTree*");
		}
		else if (input == QuickSort) {
			runGoogleTest(argc, argv, "QuickSort*");
		}
		else if (input == MergeSort) {
			runGoogleTest(argc, argv, "MergeSort*");
		}
		else {
			input = 0;
		}
	}
	
	return 0;
}

int promptUser() {
	int input;

	std::cout << std::endl
		<< "Type a number (1-7) and press Enter to run the unit tests for the corresponding data structure / algorithm "
		<< "(Or type in anything else and press Enter to exit the program)." << std::endl
		<< "1. Vector" << std::endl
		<< "2. Linked List" << std::endl
		<< "3. Stack" << std::endl
		<< "4. Queue" << std::endl
		<< "5. Hash Table" << std::endl
		<< "6. Binary Search Tree" << std::endl
		<< "7. Quick Sort" << std::endl
		<< "8. Merge Sort" << std::endl;

	std::cin >> input;

	return input;
}

void runGoogleTest(int argc, char** argv, std::string testSuite) {
	testing::GTEST_FLAG(filter) = testSuite;
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	std::cin.get();
}