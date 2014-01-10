#ifndef LIST_H
#define LIST_H
// Ref: http://www.cplusplus.com/reference/list/list/
namespace HTL {
	template <class T>
	class list {
		struct Node {
			T value;
			Node * next;
			Node * prev;
		};

		typedef Node* NodePtr;

		public:
			typedef T data_type;
			/* Constructor functions */
			// No parameters
			list() :
				_head(nullptr),
				_tail(nullptr),
				_size(0),
				_iterator(*this),
				_pastTail(new Node())
			{
				_pastTail->prev = nullptr;
				_pastTail->next = nullptr;
			}

			// One parameter: copy constructor
			list(const list& copy) : 
				_head(nullptr),
				_tail(nullptr),
				_size(0),
				_iterator(*this),
				_pastTail(new Node())
			{
				_pastTail->prev = nullptr;
				_pastTail->next = nullptr;
				*this = copy;
			}

			// Two parameters: size of type int, value of type T
			list(int initSize, const T& value) :
				_head(nullptr),
				_tail(nullptr),
				_size(0),
				_iterator(*this),
				_pastTail(new Node())
			{
				_pastTail->prev = nullptr;
				_pastTail->next = nullptr;

				for (int i = 0; i < initSize; i++) {
					push_back(value);
				}
			}

			// Destructor function
			~list() {
				while (_size > 0) {
					pop_back();
				}
			}


			/* Operator functions */
			// Assignment function
			void operator = (const list& copy) {
				while (_size > 0) {
					pop_back();
				}

				NodePtr temp = copy._head;
				while (temp->next) {
					push_back(temp->value);
					temp = temp->next;
				}
			}


			/* Iterator class */
			friend class iterator;
			class iterator {
				public:
					friend class list;

					// Default constructor
					iterator() :
						_node(nullptr)
					{}

					// Constructor function needs to store reference to vector nesting the iterator
					iterator(const list& l) :
						_node(l._head)
					{}

					// Constructor with two args to start referencing a given index
					iterator(const list& l, const int index) : 
						_node(l._head)
					{
						for (int i = 0; i < index; i++) {
							_node = _node->next;
						}
					}

					// Constructor function for copy operator
					iterator(const iterator& copy) :
						_node(copy._node)
					{}

					// Returns element at the current index
					const T operator * () const {
						return _node->value;
					}

					// Returns element at the current index
					T& operator * () {
						return _node->value;
					}

					// Copies another iterator
					iterator& operator = (const iterator& copy) {
						_node = copy._node;
						return *this;
					}

					// Equality operator
					bool operator == (const iterator& second) const {
						return _node == second._node;
					}

					// Inequality operator
					bool operator != (const iterator& second) const {
						return (_node != second._node);
					}

					// Allows going to a different index (e.g. v.begin() + 5)
					iterator operator + (int pos) {
						iterator temp = *this;
						for (int i = 0; i < pos; i++) {
							temp._node = temp._node->next;
						}
						return temp;
					}

					// Allows going to a different index (e.g. v.end() - 5)
					iterator operator - (int pos) {
						iterator temp = *this;
						for (int i = 0; i < pos; i++) {
							temp._node = temp._node->prev;
						}
						return temp;
					}

					// Pre-increment operator
					iterator operator ++ () {
						_node = _node->next;
						return *this;
					}

					// Post-increment operator
					iterator operator ++ (int) {
						iterator temp = *this;
						_node = _node->next;
						return temp;
					}

					// Pre-decrement operator
					iterator operator -- () {
						_node = _node->prev;
						return *this;
					}

					// Post-decrement operator
					iterator operator -- (int) {
						iterator temp = *this;
						_node = _node->prev;
						return temp;
					}

				private:
					NodePtr _node;
			};

			/* Iterator member functions */
			// Returns an iterator to the first element
			iterator begin() {
				iterator temp(*this);
				temp._node = _head;
				return temp;
			}

			// Returns an iterator to after the last element
			iterator end() {
				iterator temp(*this);
				temp._node = _pastTail;
				return temp;
			}


			/* Capacity member functions */
			// Returns the number of filled elements
			int size() const {
				return _size;
			}


			/* Element access member functions */
			// Returns reference to the first element
			T& front() {
				return _head->value;
			}

			// Returns reference to the last element
			T& back() {
				return _tail->value;
			}


			/* Modifier member functions */
			// Adds new node at tail and increases size by 1
			void push_back(const T& value) {
				NodePtr node = new Node();
				node->value = value;
				node->next = nullptr;

				if (_head == nullptr) {
					node->prev = nullptr;
					_head = node;
					_tail = _head;
				}
				else {
					_tail->next = node; // Next pointer of current tail to new node
					node->prev = _tail; // Prev pointer of new node to current tail
					_tail = node; // Tail is now the new node
				}

				_size++;
				linkPastTail();
			}

			// Adds new node at head and increases size by 1
			void push_front(const T& value) {
				NodePtr node = new Node();
				node->value = value;
				node->prev = nullptr;

				if (_head == nullptr) {
					node->next = nullptr;
					_head = node;
					_tail = _head;
				}
				else {
					_head->prev = node; // Prev pointer of current head to new node
					node->next = _head; // Next pointer of new node to current head
					_head = node; // Head is the new node
				}

				_size++;
				linkPastTail();
			}

			// Removes node at tail and decreases size by 1
			void pop_back() {
				NodePtr temp = _tail->prev;
				delete _tail;
				_tail = temp;
				_size--;
				
				if (_size == 0) {
					_head = nullptr;
				}

				linkPastTail();
			}

			// Removes node at head and decreases size by 1
			void pop_front() {
				NodePtr temp = _head->next;
				delete _head;
				_head = temp;
				_head->prev = nullptr;
				_size--;
				
				if (_size == 0) {
					_tail = nullptr;
				}

				linkPastTail();
			}

			// Removes a single node given the iterator
			iterator erase(iterator pos) {
				iterator temp = pos;

				if (pos._node == _head) {
					temp._node = nullptr;
					delete pos._node;
					_size--;
					return temp;
				}
				// Return nullptr because no node follows the tail
				if (pos._node == _tail) {
					temp._node->prev->next = nullptr;
					temp._node = nullptr;
				// Else, return iterator to next node
				} else {
					temp._node->prev->next = temp._node->next;
					temp._node = pos._node->next;
				}
				
				temp._node->prev = pos._node->prev;
				delete pos._node;
				_size--;
				linkPastTail();
				return temp; 
			}

			// Removes all nodes from the list
			void clear() {
				while (_size != 0) {
					pop_back();
				}
			}
		protected:
			NodePtr _head;
			NodePtr _tail;
			NodePtr _pastTail;
			int _size;
			iterator _iterator;

			// Keeps the tail linked to a pastTail node for purposes of end() member function
			void linkPastTail() {
				if (_tail == nullptr || _size == 0) {
					_pastTail->prev = nullptr;
				} else {
					_pastTail->prev = _tail;
					_tail->next = _pastTail;
				}
			}
	};
}
#endif