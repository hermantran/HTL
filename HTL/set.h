#ifndef SET_H
#define SET_H
// Ref: http://www.cplusplus.com/reference/set/set/
namespace HTL {
	template <class T>
	class set {
		struct Node {
			T value;
			Node* parent;
			Node* left;
			Node* right;
		};

		typedef Node* NodePtr;

		public:
			/* Constructor functions */
			// No parameters
			set() :
				_root(nullptr),
				_end(new Node()),
				_size(0)
			{
				_end->parent = nullptr;
				_end->left = nullptr;
				_end->right = nullptr;
			}

			// One parameter: copy constructor
			set(set& copy) : 
				_root(nullptr),
				_end(new Node()),
				_size(0)
			{
				_end->parent = nullptr;
				_end->left = nullptr;
				_end->right = nullptr;
				*this = copy;
			}

			// Destructor function
			~set() {
				clear();
				delete _end;
			}


			/* Operator functions */
			// Assignment function
			void operator = (set& copy) {
				clear();

				for (iterator it = copy.begin(); it != copy.end(); it++) {
					emplace(*it);
				}
			}


			/* Iterator class */
			friend class iterator;
			class iterator {
				public:
					friend class set;

					// Default constructor
					iterator() :
						_node(nullptr)
					{}

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
							temp++;
						}

						return temp;
					}

					// Pre-increment operator
					iterator operator ++ () {
						// If current node has no right child node
						// Going back up the tree since there is no right child node to traverse down
						if (_node->right == nullptr) {
							// If current node is the right child node of its parent
							// Traverse up to the point where the new node is greater than the current node
							if (_node->parent->right == _node) {
								NodePtr parentNode = _node->parent;
								while (_node->value > parentNode->value) {
									parentNode = parentNode->parent;
								}
								_node = parentNode;
							} 
							// If current node is the left child node of its parent
							else {
								_node = _node->parent;
							}
						} 
						// If current node has a right child node
						// Go to the right child node and then traverse down to the leftmost child node 
						else {
							_node = _node->right;
							while (_node->left != nullptr) {
								_node = _node->left;
							}
						}

						return *this;
					}

					// Post-increment operator
					iterator operator ++ (int) {
						iterator temp = *this;

						// If current node has no right child node
						// Going back up the tree since there is no right child node to traverse down
						if (_node->right == nullptr) {
							// If current node is the right child node of its parent
							// Traverse up to the point where the new node is greater than the current node
							if (_node->parent->right == _node) {
								NodePtr parentNode = _node->parent;
								while (_node->value > parentNode->value) {
									parentNode = parentNode->parent;
								}
								_node = parentNode;
							} 
							// If current node is the left child node of its parent
							else {
								_node = _node->parent;
							}
						} 
						// If current node has a right child node
						// Go to the right child node and then traverse down to the leftmost child node 
						else {
							_node = _node->right;
							while (_node->left != nullptr) {
								_node = _node->left;
							}
						}

						return temp;
					}

				private:
					NodePtr _node;
			};

			/* Iterator member functions */
			// Returns an iterator to the first element
			iterator begin() {
				iterator temp;
				temp._node = _root;
				while (temp._node->left != nullptr) {
					temp._node = temp._node->left;
				}
				return temp;
			}

			// Returns an iterator to after the last element
			iterator end() {
				iterator temp;
				temp._node = _end;
				return temp;
			}


			/* Capacity member functions */
			// Tests whether the binary search tree is empty
			bool empty() const {
				if (_size > 0) {
					return false;
				}

				return true;
			}

			// Returns the number of filled nodes
			int size() const {
				return _size;
			}


			/* Modifier member functions */
			// Removes an element given its iterator
			void erase(iterator pos) {
				// Node does not have any child nodes
				if (pos._node->left == nullptr && pos._node->right == nullptr) {
					if (pos._node->parent->right == pos._node) {
						pos._node->parent->right = nullptr;
					} else {
						pos._node->parent->left = nullptr;
					}

					if (pos._node == _root) {
						_root = nullptr;
					}
				}
				// Node has two child nodes
				else if (pos._node->left != nullptr && pos._node->right != nullptr) {
					// Replace value with the in-order successor node's value
					// Then delete the in-order successor node
					iterator successorNode = pos++;
					pos._node->value = successorNode._node->value;
					erase(successorNode);
					return;
				}
				// Node has a left child node
				else if (pos._node->left != nullptr) {
					// If it is the root node, set its left child to be the new root node
					if (pos._node == _root) {
						pos._node->left->parent = nullptr;
						_root = pos._node->left;
					}
					// Else, have the parent inherit the child node
					else {
						pos._node->left->parent = pos._node->parent;

						if (pos._node == pos._node->parent->right) {
							pos._node->parent->right = pos._node->left;
						}
						else {
							pos._node->parent->left = pos._node->left;
						}
					}
				}
				// Node has a right child node
				else if (pos._node->right != nullptr) {
					// If it is the root node, set its right child to be the new root node
					if (pos._node == _root) {
						pos._node->right->parent = nullptr;
						_root = pos._node->right; 
					}
					// Else, have the parent inherit the child node
					else {
						pos._node->right->parent = pos._node->parent;

						if (pos._node == pos._node->parent->right) {
							pos._node->parent->right = pos._node->right;
						}
						else {
							pos._node->parent->left = pos._node->right;
						}
					}
				}

				delete pos._node;
				_size--;
			}

			// Removes all elements from the binary search tree
			void clear() {
				while (_size > 0) {
					erase(begin());
				}
			}

			// Constructs a new node and inserts it
			void emplace(const T& value) {
				NodePtr temp = new Node();
				temp->value = value;
				temp->left = nullptr;
				temp->right = nullptr;

				// Construct the root node if it is null
				if (_root == nullptr) {
					temp->parent = nullptr;
					_root = temp;
					_size++;
					_linkEnd(temp);
				}
				// Else, traverse the tree and determine where to place node
				else {
					bool notFound = true;
					NodePtr currentNode = _root;

					while (notFound) {
						// If already exists, don't insert the node
						if (value == currentNode->value) {
							notFound = false;
						}
						// If less than the value, go down the left subtree
						else if (value < currentNode->value) {
							if (currentNode->left == nullptr) {
								currentNode->left = temp;
								currentNode->left->parent = currentNode;
								_size++;
								notFound = false;
							}
							else {
								currentNode = currentNode->left;
							}
						}
						// If greater than the value, go down the right subtree
						else if (value > currentNode->value) {
							if (currentNode->right == nullptr || currentNode->right == _end) {
								currentNode->right = temp;
								currentNode->right->parent = currentNode;
								_size++;
								notFound = false;
								_linkEnd(temp);
							}
							else {
								currentNode = currentNode->right;
							}
						}
					}
				}
			}

			/* Operation member functions */
			// Returns iterator to the node
			iterator find(const T& value) const {
				iterator temp;
				bool notFound = true;
				NodePtr currentNode = _root;

				while (notFound) {
					if (value == currentNode->value) {
						notFound = false;
					}
					else if (value < currentNode->value) {
						currentNode = currentNode->left;
						
						// Can return a null pointer if not found
						if (currentNode == nullptr) {
							notFound = false;
						}
					}
					else if (value > currentNode->value) {						
						currentNode = currentNode->right;
						
						if (currentNode == nullptr) {
							notFound = false;
						}
					}
				}

				temp._node = currentNode;
				return temp;
			}
		private:
			NodePtr _root;
			NodePtr _end;
			int _size;

			// Keeps the _end pointer as the right child node of the node with the largest value
			void _linkEnd(NodePtr newNode) {
				if (_end->parent == nullptr || newNode->value > _end->parent->value) {
					newNode->right = _end;
					_end->parent = newNode;
				}
			}
	};
}
#endif