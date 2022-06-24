#pragma  once
template<typename T> class BinaryLinkedListElement {
public:
	T value{};
	uint64_t index{};
	uint64_t depth{};
	BinaryLinkedListElement<T> *parent{};
	BinaryLinkedListElement<T> *child2{};
	BinaryLinkedListElement<T> *child1{};
};
