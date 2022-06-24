#pragma  once
template<typename T> class BinaryLinkedListElement {
public:
	T value{};
	uint64_t index{};
	uint64_t depth{};
	BinaryLinkedListElement<T> *parent{};
	BinaryLinkedListElement<T> *child1{};
	BinaryLinkedListElement<T> *child2{};
};
