#include <iostream>
#include <exception>

template <typename T>
class Queue {
private:
	static const short INIT_CAPACITY = 4;
	static const short RESIZE_COEF = 2;

	T* data = nullptr;
	size_t size = 0;
	size_t capacity = INIT_CAPACITY;

	size_t get;
	size_t put;

	void resize();

	void copyFrom(const Queue<T>& other);
	void moveFrom(Queue<T>&& other);
	void free();

public:
	Queue();

	Queue(const Queue<T>& other);
	Queue<T>& operator=(const Queue<T>& other);

	Queue(Queue<T>&& other) noexcept;
	Queue<T>& operator=(Queue<T>&& other) noexcept;

	~Queue();

	void push(const Queue<T>& obj);
	void push(Queue<T>&& obj);

	void pop();

	const T& peek() const;
	bool isEmpty() const;
};

template<typename T>
Queue<T>::Queue(){
	size = 0;
	capacity = INIT_CAPACITY;
	data = new T[capacity];
}

template<typename T>
Queue<T>::Queue(const Queue<T>& other) {
	copyFrom(other);
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
Queue<T>::Queue(Queue<T>&& other) noexcept {
	moveFrom(std::move(other));
}

template<typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<typename T>
Queue<T>::~Queue() {
	free();
}

template<typename T>
void Queue<T>::copyFrom(const Queue<T>& other) {
	size = other.size;
	capacity = other.capacity;

	data = new T[capacity];
	for (size_t i = 0; i < size; i++) {
		data[i] = other.data[i];
	}

	get = other.get;
	put = other.put;
}

template<typename T>
void Queue<T>::moveFrom(Queue<T>&& other) {
	size = other.size;
	other.size = 0;

	capacity = other.capacity;
	other.capacity = 0;

	data = other.data;
	other.data = nullptr;

	get = other.get;
	other.get = 0;

	put = other.put;
	other.put = 0;
}

template<typename T>
void Queue<T>::free() {
	delete[] data;
}

template<typename T>
void Queue<T>::resize() {
	T* temp = new T[capacity * RESIZE_COEF];
	int i = 0;

	while (i != size)
	{
		temp[i++] = data[get];
		(++get) %= capacity;
	}
	delete[] data;
	data = temp;
	get = 0;
	put = size;
	capacity *= 2;
}

template<typename T>
bool Queue<T>::isEmpty() const {
	return size == 0;
}

template<typename T>
void Queue<T>::push(const Queue<T>& obj) {
	if (size == capacity) {
		resize();
	}

	//check idx
	data[put] = obj;
	(++put) %= capacity;
	size++;
}

template<typename T>
void Queue<T>::push(Queue<T>&& obj) {
	if (size == capacity) {
		resize();
	}

	//check idx
	data[put] = std::move(obj);
	(++put) %= capacity;
	size++;
}

template<typename T>
void Queue<T>::pop() {
	if (isEmpty()) {
		throw std::runtime_error("Empty queue");
	}

	size--;
	(++get) %= capacity;
}

template<typename T>
const T& Queue<T>::peek() const {
	if (isEmpty()) {
		throw std::runtime_error("Empty queue");
	}

	return data[get];
}

int main() {

}