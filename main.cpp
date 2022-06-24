#include "BinaryLinkedList.hpp"

#include <iostream>

int main() {
	BinaryLinkedList<int> binaryLinkedList{99999};
	binaryLinkedList[99998] = 100;
	std::cout << binaryLinkedList[99998] << std::endl;
}