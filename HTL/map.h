#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include "list.h"
// Ref: http://www.cplusplus.com/reference/map/map/
namespace HTL {
	const int PRIME_NUMBERS[] = { 127, 283, 607, 1229, 2539, 5099, 7919 };

	template <class T>
	struct HashFunc
	{
	};

	template <>
	struct HashFunc<int> {
		// http://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key/664066#664066
		// For some reason, the reinterpret_cast() was returning exactly the same value
		unsigned int operator() (int value) {
			int k = value;
			k *= 357913941;
			k ^= k << 24;
			k += ~357913941;
			k ^= k >> 31;
			k ^= k << 31;
			return (unsigned int)(k);
		}
	};

	template <>
	struct HashFunc<char> {
		// DJB2
		unsigned int operator() (char value) {
			unsigned int hash = 5381;
			int c;

			while (c = value++)
				hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

			return hash;
		}
	};

	template <class Key, class Value, class Hash = HashFunc<Key> >
	class map {
		struct pair {
			Key key;
			Value value;
		};

		public:
			/* Constructor functions */
			// Default constructor
			map() :
				_size(0),
				_bucketSize(PRIME_NUMBERS[0]),
				_filledBuckets(0),
				_buckets(new HTL::list<pair>[_bucketSize])
			{
			}

			// Copy constructor
			map(const map& copy) :
				_size(0),
				_bucketSize(PRIME_NUMBERS[0]),
				_filledBuckets(0),
				_buckets(new HTL::list<pair>[_bucketSize])
			{
				*this = copy;
			}

			// Destructor function
			~map() {
				delete [] _buckets;
			}

			/* Operator functions */
			// Assignment function
			void operator = (const map& copy) {
				_size = 0;
				_bucketSize = copy._bucketSize;
				delete [] _buckets;
				_buckets = new HTL::list<pair>[_bucketSize];

				HTL::list<pair>::iterator it;

				// Go through all the copy's buckets and add all their elements
				for (int i = 0; i < _bucketSize; i++) {
					if (copy._buckets[i].size() > 0) {
						for (it = copy._buckets[i].begin(); it != copy._buckets[i].end(); it++) {
							emplace((*it).key, (*it).value);
						}
					}
				}
			}

			// Accesses the value associated with a given key
			Value& operator[](const Key key) {
				int index = _hash(key);
				HTL::list<pair>::iterator it;
				
				// Iterate over the specified bucket's nodes and match the key
				if (_buckets[index].size() > 0) {
					for (it = _buckets[index].begin(); it != _buckets[index].end(); it++) {
						if ((*it).key == key) {
							return (*it).value;
						}
					}
				}

				// If key is not found, create a new pair
				pair p;
				p.key = key;
				p.value = 1;

				// Keep track of how many buckets have at least one element
				if (_buckets[index].size() == 0) {
					_filledBuckets++;
				}
				_buckets[index].push_back(p);
				_size++;

				// At 80% filled, make more buckets
				if (_filledBuckets > 0.8 * _bucketSize) {
					_resize();
				}

				return _buckets[index].back().value;
			}

			/* Iterator class */
			friend class iterator;
			class iterator {
				public:
					friend class map;
					// Default constructor
					iterator() :
						_currentBucket(0),
						_map(nullptr)
					{}

					// Constructor function for copy operator
					iterator(const iterator& copy) :
						_currentBucket(0),
						_map(nullptr)
					{
						*this = copy;
					}

					// Returns element at the current index
					const pair operator * () const {
						return *_it;
					}

					// Returns element at the current index
					pair& operator * () {
						return *_it;
					}

					// Copies another iterator
					iterator& operator = (const iterator& copy) {
						_it = copy._it;
						_currentBucket = copy._currentBucket;
						_map = copy._map;
						return *this;
					}

					// Equality operator
					bool operator == (const iterator& second) const {
						return _it == second._it;
					}

					// Inequality operator
					bool operator != (const iterator& second) const {
						return (_it != second._it);
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
						// Start iterating over the next bucket's linked list if we reached the end of the current bucket
						if (_it == _map->_buckets[_currentBucket].end() - 1 && _currentBucket < _map->_bucketSize) {
							_currentBucket++;
							
							// Only iterate buckets with actual elements
							while (_map->_buckets[_currentBucket].size() == 0) {
								// If already at the last bucket, just return the last element
								if (_currentBucket == _map->_bucketSize - 1) {
									_it = _map->_buckets[_currentBucket].end();
									return *this;
									break;
								}
								
								_currentBucket++;
							}

							_it = _map->_buckets[_currentBucket].begin();
						} else {
							_it++;
						}

						return *this;
					}

					// Post-increment operator
					iterator operator ++ (int) {
						iterator temp = *this;

						// Start iterating over the next bucket's linked list if we reached the end of the current bucket
						if (_it == _map->_buckets[_currentBucket].end() - 1 && _currentBucket < _map->_bucketSize) {
							_currentBucket++;

							while (_map->_buckets[_currentBucket].size() == 0) {
								if (_currentBucket == _map->_bucketSize - 1) {
									_it = _map->_buckets[_currentBucket].end();
									return temp;
									break;
								}

								_currentBucket++;
							}

							_it = _map->_buckets[_currentBucket].begin();
						} else {
							_it++;
						}
						return temp;
					}
				private:
					typename HTL::list<pair>::iterator _it;
					map* _map;
					int _currentBucket;
			};

			/* Iterator member functions */
			// Returns an iterator to the first element
			iterator begin() {
				iterator temp;
				temp._map = this;
				
				for (int i = 0; i < _bucketSize; i++) {
					if (_buckets[i].size() > 0) {
						temp._it = _buckets[i].begin();
						temp._currentBucket = i;
						break;
					}
				}
				return temp;
			}

			// Returns an iterator to after the last element
			iterator end() {
				iterator temp;
				temp._map = this;
				temp._it = _buckets[_bucketSize - 1].end();
				temp._currentBucket = _bucketSize - 1;
				return temp;
			}

			/* Capacity member functions */
			// Tests whether the hash table is empty
			bool empty() const {
				if (_size > 0) {
					return false;
				}

				return true;
			}

			// Returns the number of elements in the hash table
			int size() const {
				return _size;
			}


			/* Modifier member functions */
			// Removes an element given its iterator
			void erase(iterator pos) {
				int index = _hash((*pos).key);
				HTL::list<pair>::iterator it;

				for (it = _buckets[index].begin(); it != _buckets[index].end(); it++) {
					if ((*it).key == (*pos).key) {
						_buckets[index].erase(it);
						_size--;
						break;
					}
				}
			}

			// Removes all elements from the hash table
			void clear() {
				for (int i = 0; i < _bucketSize; i++) {
					if (_buckets[i].size() > 0) {
						_buckets[i].clear();
					}
				}

				_size = 0;
			}

			// Constructs a new pair element and inserts it
			void emplace(const Key& key, const Value& value) {
				(*this)[key] = value;
			}

			/* Operation member functions */
			// Returns an iterator to a pair given its key
			iterator find(Key key) {
				HTL::list<pair>::iterator it;
				iterator pos;
				int index = _hash(key);

				for (it = _buckets[index].begin(); it != _buckets[index].end(); it++) {
					if ((*it).key == key) {
						pos._it = it;
					}
				}

				return pos;
			}
		
		private:
			int _size;
			int _filledBuckets;
			int _bucketSize;
			HTL::list<pair>* _buckets;
			Hash _myFunc;

			unsigned int _hash(Key key) {
				return _myFunc(key) % _bucketSize;
			}

			void _resize() {
				pair* temp = new pair[_size];
				int oldSize = _size;
				iterator it = begin();

				// Copy over all elements into a temp container
				for (int i = 0; i < oldSize; i++) {
					temp[i] = *it;
					it++;
				}

				delete [] _buckets;
				_size = 0;
				_filledBuckets = 0;

				// Go to next prime number for bucket size
				for (int i = 0; i < 7; i++) {
					if (_bucketSize == PRIME_NUMBERS[i]) {
						_bucketSize = PRIME_NUMBERS[i+1];
						break;
					}
				}

				_buckets = new HTL::list<pair>[_bucketSize];

				for (int i = 0; i <oldSize; i++) {
					emplace(temp[i].key, temp[i].value);
				}
			}
	};
}
#endif