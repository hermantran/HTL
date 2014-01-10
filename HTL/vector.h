#ifndef VECTOR_H
#define VECTOR_H
// Ref: http://www.cplusplus.com/reference/vector/vector/
namespace HTL {
	const int CAPACITY_INCREASE_RATE = 2;

	template<class T>
	class vector {
		public:
			typedef T data_type;
			/* Constructor functions */
			// No parameters
			vector() : 
				_size(0), 
				_capacity(0), 
				_pointer(new T[0]), 
				_iterator(*this)
			{}

			// One parameter: copy constructor
			vector(const vector& copy) : 
				_size(0), 
				_capacity(0), 
				_pointer(new T[0]), 
				_iterator(*this)
			{
				*this = copy;
			}

			// One parameter: initial size (and capacity) of type int
			vector(int initSize) : 
				_size(initSize), 
				_capacity(initSize), 
				_pointer(new T[initSize]), 
				_iterator(*this)
			{}

			// Two parameters: initial size (and capacity) of type int, initial value of type T
			vector(int initSize, const T initValue) : 
				_size(initSize), _capacity(initSize), 
				_pointer(new T[initSize]), 
				_iterator(*this)
			{
				for (int i = 0; i < initSize; i++) {
					_pointer[i] = initValue;
				}
			}

			// Destructor function
			~vector() {
				delete [] _pointer;
			}


			/* Operator functions */
			// Equality operator
			bool operator == (const vector& second) const {
				return (_pointer == second._pointer);
			}

			// Inequality operator
			bool operator != (const vector& second) const {
				return (_pointer != second._pointer);
			}

			// Element setter function
			T& operator [] (int index) {
				return _pointer[index];
			}

			// Element getter function
			const T operator [] (int index) const {
				return _pointer[index];
			}

			// Assignment function
			void operator = (const vector& copy) {
				T * newPointer = new T[copy._size];
				
				for (int i = 0; i < copy._size; i++) {
					newPointer[i] = copy[i];
				}

				delete [] _pointer;
				_pointer = newPointer;
				_size = copy._size;
				_capacity = copy._capacity;
			}


			/* Capacity member functions */
			// Returns the number of filled elements
			int size() const {
				return _size;
			}
			
			// Returns the total allocated space of the vector
			int capacity() const {
				return _capacity;
			}

			// Resizes the vector to specified size of type int
			void resize(int newSize) {
				if (newSize < _size) {
					for (int i = newSize; i < _size; i++) {
						_pointer[i] = 0;
					}
				}
				else if (newSize > _capacity) {
					T * newPointer = new T[newSize];

					for (int i = 0; i < _size; i++) {
						newPointer[i] = _pointer[i];
					}

					delete [] _pointer;
					_pointer = newPointer;
				}

				_size = newSize;
			}


			/* Iterator class */
			friend class iterator;
			class iterator {
				public:
					friend class vector;

					// Constructor function needs to store reference to vector nesting the iterator
					iterator(vector& v) :
						_vector(v),
						_index(0)
					{}

					// Constructor with two args to start referencing a given index
					iterator(vector& v, const int index) : 
						_vector(v),
						_index(index)
					{}

					// Constructor function for copy operator
					iterator(const iterator& copy) :
						_vector(copy._vector),
						_index(copy._index)
					{}

					// Returns element at the current index
					const T operator * () const {
						return _vector[_index];
					}

					// Setter for element at given iterator
					T& operator * () {
						return _vector[_index];
					}

					// Copies another iterator
					iterator& operator = (const iterator& copy) {
						_vector = copy._vector;
						_index = copy._index;
						return *this;
					}

					// Equality operator
					bool operator == (const iterator& second) const {
						return ((_vector == second._vector) && (_index == second._index));
					}

					// Inequality operator
					bool operator != (const iterator& second) const {
						return ((_vector != second._vector) || (_index != second._index));
					}

					// Allows going to a different index (e.g. v.begin() + 5)
					iterator operator + (int pos) {
						_index += pos;
						return *this;
					}

					// Allows going to a different index (e.g. v.end() - 5)
					iterator operator - (int pos) {
						_index -= pos;
						return *this;
					}

					// Pre-increment operator
					iterator operator ++ () {
						_index++;
						return *this;
					}

					// Post-increment operator
					iterator operator ++ (int) {
						iterator temp = *this;
						_index++;
						return temp;
					}

					// Pre-decrement operator
					iterator operator -- () {
						_index--;
						return *this;
					}

					// Post-decrement operator
					iterator operator -- (int) {
						iterator temp = *this;
						_index--;
						return temp;
					}
				private:
					int _index; // index to current element
					vector& _vector;
			};

			/* Iterator member functions */
			// Returns an iterator to the first element
			iterator begin() {
				iterator temp(*this, 0);
				return temp;
			}

			// Returns an iterator to the last element
			iterator end() {
				iterator temp(*this, _size - 1);
				return temp;
			}

			
			/* Element access member functions */
			// Returns reference to the first element
			T& front() {
				return _pointer[0];
			}

			// Returns reference to the last element
			T& back() {
				return _pointer[_size - 1];
			}


			/* Modifier member functions */
			// Adds new element and increases capacity if limit reached
			void push_back(const T& element) {
				if (_capacity <= _size) {
					if (_capacity <= 0) {
						_capacity = 1;
					} else {
						_capacity *= CAPACITY_INCREASE_RATE;
					}

					T * newPointer = new T[_capacity];

					for (int i = 0; i < _size; i++) {
						newPointer[i] = _pointer[i];
					}

					delete [] _pointer;
					_pointer = newPointer;
				}
				
				_pointer[_size] = element;
				_size++;
			}

			// Removes last element and decreases size by 1
			void pop_back() {
				if (_size > 0) {
					_size--;
					_pointer[_size] = 0;
				}
			}

			// Erases a single element given the iterator
			iterator erase(const iterator pos) {
				if (pos._index != _size - 1) {
					for (int i = pos._index; i < _size - 1; i++) {
						_pointer[i] = _pointer[i+1];
					}
				}
				
				_size--;
				_pointer[_size] = 0;
				_iterator._index = pos._index;
				return _iterator; 
				
			}

			// Removes all elements from the vector
			void clear() {
				_capacity = 0;
				_size = 0;
				delete [] _pointer;
				_pointer = NULL;
			}

		private:
			int _size, _capacity;
			T * _pointer;
			iterator _iterator;
	};
}
#endif