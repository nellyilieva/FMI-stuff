#include <iostream>
using namespace std;

//how we implement singly linked list -> the idea is that we have blocks of data in different places in the memory; this are the nodes
//Node -> data to store the value; pointer next pointing to the next node; constructor
//in the linked list we have 2 pointers head(to the first node) and tail(to the last node)(tail is not neccesary)
//size keeps track of numbber of elements in the list (??does is really fit the logic for linked list??)
//in the functions we basically just work with pointers; we set them to other pointers
//head points to the first node and tail points to the last node; head and tail belong to the class and not to the node

//in order to use the list we need to implement iterators -> for modifying abd reading
//the iterators have pointer which points to the current element
//functions: *, ->, ++, +, +=, ==, !=
//we use the iterators in the functions begin, end, cbegin, cend -> returns the head/nullptr(tail + 1)
//insertAfter the current node and removeAfter the current node


template <typename T>
class SinglyLinkedList {
private:
	struct Node {
		T data;
		Node* next;

		Node(const T& data) {
			this->data = data;
			next = nullptr;
		}
	};

	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;

	void copyFrom(const SinglyLinkedList<T>& other) {
		Node* iter = other.head;

		while (iter) {
			pushBack(iter->data);
			iter = iter->next;
		}
	}

	void moveFrom(SinglyLinkedList<T>&& other) {
		head = other.head;
		tail = other.tail;
		other.head = other.tail = nullptr;
	}

	void free() {
		Node* iter = head;

		while (iter) {
			Node* toDelete = iter;
			iter = iter->next;
			delete toDelete;
		}
		head = tail = nullptr;
		size = 0;
	}

public:
	class SllIterator {   //modify the elements
		Node* currentElementPtr;

		friend class SinglyLinkedList;
	public:

		typedef std::forward_iterator_tag iterator_category;

		SllIterator(Node* currentElementPtr = nullptr) : currentElementPtr(currentElementPtr) {}

		T& operator*() {
			return currentElementPtr->data;
		}

		T* operator->() {
			return &currentElementPtr->data;
		}

		SllIterator& operator++() {
			if (currentElementPtr)
				currentElementPtr = currentElementPtr->next;
			return *this;
		}

		SllIterator operator++(int) {
			SllIterator copy(*this);
			++(*this);
			return copy;
		}

		SllIterator& operator+=(size_t s) {

			while (s--)
				++(*this);

			return *this;
		}

		SllIterator operator+(int i) const {

			SllIterator res(*this);
			return res += i;
		}

		bool operator==(const SllIterator& rhs) const { return currentElementPtr == rhs.currentElementPtr; }
		bool operator!=(const SllIterator& rhs) const { return !(rhs == *this); }

	};

	class ConstSllIterator {   //read the elements
		Node* currentElementPtr;

		friend class SinglyLinkedList;
	public:

		typedef std::forward_iterator_tag iterator_category;

		ConstSllIterator(const SllIterator& nonConstIter) : currentElementPtr(nonConstIter.currentElementPtr) {}
		ConstSllIterator(Node* currentElementPtr = nullptr) : currentElementPtr(currentElementPtr) {}

		const T& operator*() const {
			return currentElementPtr->data;
		}

		const T* operator->() const {
			return &currentElementPtr->data;
		}

		ConstSllIterator& operator++() {
			if (currentElementPtr)
				currentElementPtr = currentElementPtr->next;
			return *this;
		}

		ConstSllIterator operator++(int) {
			ConstSllIterator copy(*this);
			++(*this);
			return copy;
		}

		ConstSllIterator& operator+=(size_t s) {

			while (s--)
				++(*this);

			return *this;
		}

		ConstSllIterator operator+(int i) const {

			ConstSllIterator res(*this);
			return res += i;
		}

		bool operator==(const ConstSllIterator& rhs) const { return currentElementPtr == rhs.currentElementPtr; }
		bool operator!=(const ConstSllIterator& rhs) const { return !(rhs == *this); }

	};

	SllIterator begin() {
		return SllIterator(head);
	}
	SllIterator end() {
		return SllIterator(nullptr);
	}

	ConstSllIterator cbegin() const {
		return ConstSllIterator(head);
	}
	ConstSllIterator cend() const {
		return ConstSllIterator(nullptr);
	}

	SllIterator insertAfter(const T& element, const ConstSllIterator& it) {
		if (it == end())
			return end();

		Node* newNode = new Node(element);
		Node* itNode = it.currentElementPtr;  //points to the node pointed by it

		newNode->next = itNode->next;
		itNode->next = newNode;
		size++;
		return SinglyLinkedList<T>::SllIterator(newNode);
	}

	SllIterator removeAfter(const ConstSllIterator& it) {
		if (it == end() || getSize() == 1)
			return end();

		Node* toDelete = (it + 1).currentElementPtr;

		Node* newNext = toDelete->next;

		it.currentElementPtr->next = newNext;
		size--;

		if (toDelete == tail) {
			tail = it.currentElementPtr;
		}

		delete toDelete;

		return SinglyLinkedList<T>::SllIterator(newNext);
	}


	SinglyLinkedList() = default;

	SinglyLinkedList(const SinglyLinkedList<T>& other) {
		copyFrom(other);
	}

	SinglyLinkedList(SinglyLinkedList<T>&& other) {
		moveFrom(std::move(other));
	}

	SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>& other) {
		if (this != &other) {
			free();
			copyFrom(other);
		}

		return *this;
	}

	SinglyLinkedList<T>& operator=(SinglyLinkedList<T>&& other) {
		if (this != &other) {
			free();
			moveFrom(std::move(other));
		}

		return *this;
	}

	~SinglyLinkedList() {
		free();
	}

	void pushFront(const T& el) {
		Node* toAdd = new Node(el);   //pointer to the new node and initialize it

		if (isEmpty()) {
			head = tail = toAdd;   //pointers are set to pointer
		}
		else {
			toAdd->next = head;    //the pointer(next) of the pointer(toAdd) is set to head
			head = toAdd;
		}
		size++;
	}

	void pushBack(const T& el) {
		Node* toAdd = new Node(el);

		if (isEmpty()) {
			head = tail = toAdd;
		}
		else {
			tail->next = toAdd;
			tail = toAdd;
		}
		size++;
	}

	void popFront() {
		if (!head)
			throw std::logic_error("Empty list!");

		if (head == tail) {
			delete head;
			head = tail = nullptr;
		}
		else {
			Node* toDelete = head;  //we need it so we don't lose track of the original head node which we need to delete
			head = head->next;
			delete toDelete;
		}
		size--;
	}

	const T& front() const {
		if (!head)
			throw std::logic_error("Empty list!");

		return head->data;
	}

	const T& back() const {
		if (!tail)
			throw std::logic_error("Empty list!");

		return tail->data;
	}

	T& front() {
		if (!head)
			throw std::logic_error("Empty list!");

		return head->data;
	}

	T& back() {
		if (!tail)
			throw std::logic_error("Empty list!");

		return tail->data;
	}

	size_t getSize() const {
		return size;
	}

	bool isEmpty() const {
		return getSize() == 0;
	}

	template <typename U>
	friend SinglyLinkedList<U> concat(SinglyLinkedList<U>& lhs, SinglyLinkedList<U>& rhs) {   //!!!
		SinglyLinkedList<T> result;

		if (!lhs.head) {     //if no lhs
			result.head = rhs.head;
			result.tail = rhs.tail;
		}
		else if (!rhs.head) {  //if no rhs
			result.head = lhs.head;
			result.tail = lhs.tail;
		}
		else {
			lhs.tail->next = rhs.head;
			result.head = lhs.head;
			result.tail = rhs.tail;
		}

		result.size = rhs.size + lhs.size;
		rhs.size = lhs.size = 0;
		rhs.head = rhs.tail = lhs.head = lhs.tail = nullptr;

		return result;
	}

	void print() const {
		Node* iter = head;

		while (iter) {
			std::cout << iter->data << ' ';
			if (iter->next)
				std::cout << "->" << ' ';
			iter = iter->next;
		}

		std::cout << std::endl;
	}
};

int main()
{

}