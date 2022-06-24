#include "BinaryLinkedList.hpp"

#include <iostream>

int main() {
	BinaryLinkedList<int> binaryLinkedList{10};
	int elementNumber = 0;
	for (int &element : binaryLinkedList) {
		element = elementNumber++;
	}
	for (int element : binaryLinkedList) {
		std::cout << element << std::endl;
	}
}