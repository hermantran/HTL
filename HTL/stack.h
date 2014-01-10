#ifndef STACK_H
#define STACK_H
// Ref: http://www.cplusplus.com/reference/stack/stack/
#include "list.h"

namespace HTL {
	template <class T>
	class stack : private list<T> {
		public:
			// Default constructor function
			stack()
			{};

			// Copy constructor
			stack(const stack& copy)
			{
				*this = copy;
			}

			// Assignment operator
			void operator = (const stack& copy) {
				list<T>::operator=(copy);
			}

			// Returns a boolean value whether the stack is empty
			bool empty() const {
				return (list<T>::size() == 0);
			}

			// Returns the number of filled nodes
			int size() const {
				return list<T>::size();
			}

			// Returns reference to the node at the tail (top of stack)
			T& top() {
				return *(end() - 1);
			}

			// Adds new node at tail (top of stack)
			void push(const T& value) {
				push_back(value);
			}

			// Removes node at tail (top of stack)
			void pop() {
				pop_back();
			}
	};
}
#endif