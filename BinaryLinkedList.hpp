#pragma once

#include <string>
#include <stdexcept>
#include <cmath>

#include "BinaryLinkedListElement.hpp"

template<typename T> class BinaryLinkedList {
	BinaryLinkedListElement<T> *primaryElement = new BinaryLinkedListElement<T>{};
	uint64_t size = 0;
	uint64_t maxDepth = 0;
	
public:
	BinaryLinkedList() = default;
	
	explicit BinaryLinkedList(uint64_t initialSize) {
		primaryElement->depth = 1;
		primaryElement->index = floor((double_t) initialSize / 2);
		maxDepth = (uint64_t) floor(log2((double_t) initialSize)) + 1;
		uint64_t currentAllocation = pow(2, maxDepth + 1) - 1;
		uint64_t overAllocation = currentAllocation - initialSize;
		BinaryLinkedListElement<T> *parent = primaryElement;
		while (true) {
			if (parent->child1 == nullptr) {
				parent->child1 = new BinaryLinkedListElement<T>{};
				parent->child1->index = floor(parent->index / 2);  /**@todo Calculate index*/
				parent->child1->parent = parent;
				parent->child1->depth = parent->depth + 1;
			} else if (parent->child2 == nullptr) {
				parent->child2 = new BinaryLinkedListElement<T>{};
				parent->child2->index = floor(parent->index / 2);  /**@todo Calculate index*/
				parent->child2->parent = parent;
				parent->child2->depth = parent->depth + 1;
			} else parent = parent->child2;
			
			++size;
			
			// Handle what happens when the tree is complete
			if (size == initialSize) {
				break;
			}
			
			// Handle what happens at the bottom of the tree
			if (parent->depth == maxDepth || (overAllocation <= currentAllocation && parent->depth == maxDepth - 1)) {
				--currentAllocation;
				while (parent->child2 != nullptr) {
					parent = parent->parent;
				}
				continue;
			}
			
			parent = parent->child2 != nullptr ? parent->child2 : parent->child1;
			
		}
	}
	
	T operator[](uint64_t index) {
		return primaryElement->value;
	}
	
	~BinaryLinkedList() {
//		BinaryLinkedListElement<T> *node = primaryElement;
//		while (node != nullptr) {
//			BinaryLinkedListElement<T> *next = node->child1;
//			node->child1 = nullptr;
//			if (next != nullptr) {
//				next = node->child2 != nullptr ? node->child2 : node->parent;
//				delete next;
//			}
//			next = node->child2;
//		}
	}
};