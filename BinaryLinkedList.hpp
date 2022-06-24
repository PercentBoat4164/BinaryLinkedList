#pragma once

#include "BinaryLinkedListElement.hpp"

#include <cstdint>
#include <cmath>
#include <cassert>
#include <iterator>

template<typename T> class BinaryLinkedList {
private:
	BinaryLinkedListElement<T> *primaryElement = new BinaryLinkedListElement<T>{};
	uint64_t size = 0;
	uint64_t maxDepth = 0;

public:
	class iterator {
	private:
		uint64_t _index{};
		BinaryLinkedList<T> *_binaryLinkedList;
		
	public:
		typedef std::random_access_iterator_tag iterator_category;
		typedef uint64_t value_type;
		typedef std::ptrdiff_t difference_type;
		typedef uint64_t* pointer;
		typedef uint64_t& reference;
		
		iterator() = default;
		
		explicit iterator(BinaryLinkedList<T> *binaryLinkedList, uint64_t index) {
			_index = index;
			_binaryLinkedList = binaryLinkedList;
		}
		
		T &operator*() {
			return _binaryLinkedList->operator[](_index);
		}
		
		iterator operator++(int) {
			iterator temp = *this;
			++*this;
			return temp;
		}
		
		iterator operator--(int) {
			iterator temp = *this;
			--*this;
			return temp;
		}
		
		iterator &operator++() {
			++_index;
			return *this;
		}
		
		iterator &operator--() {
			--_index;
			return *this;
		}
		
		iterator &operator+=(const iterator &other) {
			_index += other._index;
			return *this;
		}
		
		iterator &operator-=(const iterator &other) {
			_index -= other._index;
			return *this;
		}
		
		iterator &operator+=(const uint64_t offset) {
			_index += offset;
			return *this;
		}
		
		iterator &operator-=(const uint64_t offset) {
			_index -= offset;
			return *this;
		}
		
		uint64_t operator+(const iterator &other) {
			return _index + other._index;
		}
		
		uint64_t operator-(const iterator &other) {
			return _index - other._index;
		}
		
		uint64_t operator+(const uint64_t &offset) {
			return _index + offset;
		}
		
		uint64_t operator-(const uint64_t &offset) {
			return _index - offset;
		}
		
		bool operator<(const iterator &other) {
			return _index < other._index;
		}
		
		bool operator>(const iterator &other) {
			return _index > other._index;
		}
		
		bool operator<=(const iterator &other) {
			return _index <= other._index;
		}
		
		bool operator>=(const iterator &other) {
			return _index >= other._index;
		}
		
		bool operator<(const uint64_t &other) {
			return _index < other;
		}
		
		bool operator>(const uint64_t &other) {
			return _index > other;
		}
		
		bool operator<=(const uint64_t &other) {
			return _index <= other;
		}
		
		bool operator>=(const uint64_t &other) {
			return _index >= other;
		}
		
		friend bool operator==(const iterator &a, const iterator &b) {
			return a._index == b._index;
		}
		
		friend bool operator!=(const iterator &a, const iterator &b) {
			return a._index != b._index;
		}
		
		friend bool operator==(const iterator &a, const uint64_t &b) {
			return a._index == b;
		}
		
		friend bool operator!=(const iterator &a, const uint64_t &b) {
			return a._index != b;
		}
		
		T &operator[](uint64_t offset) {
			return _binaryLinkedList->operator[](_index + offset);
		}
	};
	
	iterator begin() {
		return iterator(this, 0);
	}
	
	iterator end() {
		return iterator(this, size);
	}
	
	BinaryLinkedList() = default;
	
	explicit BinaryLinkedList(uint64_t initialSize) {
		maxDepth = (uint64_t) log2((double_t) initialSize) + 1;
		uint64_t spacesToBeUsedAtMaxDepth = initialSize - (uint64_t) (pow(2, maxDepth - 1) - 1);
		uint64_t elementsInMaxDepth = 0;
		uint64_t currentIndex = 0;
		
		// Initialize first element
		BinaryLinkedListElement<T> *element = primaryElement;
		element->depth = 1;
		element->index = UINT64_MAX;
		
		// Create binary tree
		while (++size < initialSize) {
			// If at bottom, go up one layer
			if (element->depth == maxDepth || (element->depth == maxDepth - 1 && spacesToBeUsedAtMaxDepth <= elementsInMaxDepth)) {
				++elementsInMaxDepth;
				if (element->index == UINT64_MAX) element->index = currentIndex++;
				element = element->parent;
				if (element->index == UINT64_MAX) element->index = currentIndex++;
			}
			
			// Create one of two children
			if (element->child1 == nullptr) {  // Build child 1
				element->child1 = new BinaryLinkedListElement<T>{};
				element->child1->index = UINT64_MAX;
				element->child1->parent = element;
				element->child1->depth = element->depth + 1;
				element = element->child1;  // Treat child 1 as start of new branch
			} else if (element->child2 == nullptr) {  // Build child 2
				element->child2 = new BinaryLinkedListElement<T>{};
				element->child2->index = UINT64_MAX;
				element->child2->parent = element;
				element->child2->depth = element->depth + 1;
				element = element->child2;  // Treat child 2 as start of new branch
			} else {  // If this branch is completely built
				--size;  // This path does not actually create a new element
				if (element->index == UINT64_MAX) element->index = currentIndex++;
				element = element->parent;
				if (element->index == UINT64_MAX) element->index = currentIndex++;
			}
		}
		
		// Generate indices on far right side of tree
		while (element != primaryElement) {
			if (element->index == UINT64_MAX) element->index = currentIndex++;
			element = element->parent;
			if (element->index == UINT64_MAX) element->index = currentIndex++;
		}
	}
	
	T &operator[](uint64_t index) {
		assert(index >= 0 && index < size);
		BinaryLinkedListElement<T> *element = primaryElement;
		while (element->index != index) element = element->index > index ? element->child1 : element->child2;
		return element->value;
	}
	
	const T &operator[](uint64_t index) const {
		assert(index >= 0 && index < size);
		BinaryLinkedListElement<T> *element = primaryElement;
		while (element->index != index) element = element->index > index ? element->child1 : element->child2;
		return &element->value;
	}
	
	~BinaryLinkedList() {
		BinaryLinkedListElement<T> *element = primaryElement;
		while (element != nullptr) {
			if (element->child1 != nullptr) element = element->child1;
			else if (element->child2 != nullptr) element = element->child2;
			else {
				if (element == primaryElement) break;
				if (element->parent->child1 == element) element->parent->child1 = nullptr;
				else element->parent->child2 = nullptr;
				delete element;
				element = primaryElement;
			}
		}
		delete primaryElement;
	}
};