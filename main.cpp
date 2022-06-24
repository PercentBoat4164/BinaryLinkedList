#include <iostream>
#include "BinaryLinkedList.hpp"

int main() {
	BinaryLinkedList<int> binaryLinkedList{10};
	std::cout <<binaryLinkedList[0] << std::endl;
}
