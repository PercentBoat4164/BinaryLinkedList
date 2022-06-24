#pragma once

#include <string>
#include <stdexcept>
#include <cmath>

#include "BinaryLinkedListElement.hpp"

template<typename T>
class BinaryLinkedList {
	BinaryLinkedListElement<T> *primaryElement = new BinaryLinkedListElement<T>{};
	uint64_t size = 0;
	uint64_t maxDepth = 0;

public:
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
	
	T operator[](uint64_t index) {
		BinaryLinkedListElement<T> *element = primaryElement;
		while (element->index != index) {
			element = element->index > index ? element->child1 : element->child2;
		}
		return element->value;
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