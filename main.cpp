#include <iostream>
#include "BinaryLinkedList.hpp"

int main() {
	BinaryLinkedList<int> binaryLinkedList{6};
	std::cout << binaryLinkedList[0] << std::endl;
}
