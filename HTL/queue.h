#ifndef QUEUE_H
#define QUEUE_H
// Ref: http://www.cplusplus.com/reference/queue/queue/
#include "list.h"

namespace HTL {
	template <class T>
	class queue : private list<T> {
		public:
			// Default constructor function
			queue()
			{};

			// Copy constructor
			queue(const queue& copy) 
			{
				*this = copy;
			}

			// Assignment operator
			void operator = (const queue& copy) {
				list<T>::operator=(copy);
			}

			// Returns a boolean value whether the queue is empty
			bool empty() const {
				return (list<T>::size() == 0);
			}

			// Returns the number of filled nodes
			int size() const {
				return list<T>::size();
			}

			// Returns reference to the node at the head (front of queue)
			T& front() {
				return *begin();
			}

			// Returns reference to the node at the tail (back of queue)
			T& back() {
				return *(end() - 1);
			}

			// Adds new node at tail (back of queue)
			void push(const T& value) {
				push_back(value);
			}

			// Removes node at head (front of queue)
			void pop() {
				pop_front();
			}
	};
}
#endif