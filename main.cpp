#include "BinaryLinkedList.hpp"

#include <iostream>
#include <algorithm>

int main() {
	BinaryLinkedList<int> binaryLinkedList{10};
	int elementNumber = 0;
	std::generate(binaryLinkedList.begin(), binaryLinkedList.end(), [&] -> int { return elementNumber++; });
	std::cout << binaryLinkedList.begin()[3] << std::endl;
}