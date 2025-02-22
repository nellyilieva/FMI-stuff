#include <iostream>
#include<exception>

template<typename T>
class Vector {
private:
	static const short INITIAL_CAPACITY = 4;
	static const short RESIZE_COEF = 2;

	T* data = nullptr;
	size_t size = 0;
	size_t capacity = INITIAL_CAPACITY;

	void copyFrom(const Vector<T>& other);
	void moveFrom(Vector<T>&& other);
	void free();

	void resize(size_t newCap);

public:
	Vector();

	Vector(const Vector<T>& other);
	Vector<T>& operator=(const Vector<T>& other);

	Vector(Vector<T>&& other) noexcept;
	Vector<T>& operator=(Vector<T>&& other) noexcept;

	~Vector();

	size_t getSize();
	size_t getCapacity();

	void pushBack(const T& obj);
	void pushBack(T&& obj);

	void insert(const T& obj, const size_t idx);
	void insert(T&& obj, const size_t idx);

	void popBack();
	T pop_back();

	void erase(size_t idx);
	T erase_and_return(size_t idx);

	void clear();

	bool isEmpty() const;

	T& operator[](const size_t);
	const T& operator[](const size_t) const;
};

template<typename T>
Vector<T>::Vector() {
	capacity = 8;
	size = 0;
	data = new T[capacity];
}

template<typename T>
void Vector<T>::copyFrom(const Vector<T>& other) {
	size = other.size;
	capacity = other.capacity;

	data = new T[capacity];
	for (int i = 0; i < size; i++) {
		data[i] = other.data[i];
	}
}

template<typename T>
void Vector<T>::moveFrom(Vector<T>&& other) {
	size = other.size;
	other.size = 0;

	capacity = other.capacity;
	other.capacity = 0;

	data = other.data;
	other.data = nullptr;
}

template<typename T>
void Vector<T>::free() {
	delete[] data;

	data = nullptr;
	size = 0;
	capacity = 0;
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other) {
	copyFrom(other);
}

template<typename T>
Vector<T>::Vector(Vector<T>&& other) {
	moveFrom(std::move(other));
}

template<typename T>
Vector<T>::~Vector() {
	free();
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<typename T>
void Vector<T>::resize(size_t newCap) {
	capacity = newCapacity;
	T* temp = new T[capacity];

	// Note: the std::vector allocates ONLY MORE than the current capacity
	if (size > newCapacity) {
		size = newCapacity;
	}

	for (size_t i = 0; i < size; i++) {
		temp[i] = std::move(data[i]);
	}

	delete[] data;
	data = temp;
}

template<typename T>
size_t Vector<T>::getSize() {
	return size;
}

template<typename T>
size_t Vector<T>::getCapacity() {
	return capacity;
}

template<typename T>
void Vector<T>::pushBack(const T& obj) {
	if (size == capacity) {
		resize(capacity * RESIZE_COEF);
	}

	data[size] = obj;
	size++;
}

template<typename T>
void Vector<T>::pushBack(T&& obj) {
	if (size == capacity) {
		resize(capacity * RESIZE_COEF);
	}

	data[size] = std::move(obj);
	size++;
}

template<typename T>
void Vector<T>::insert(const T& obj, const size_t idx) {
	if (size == capacity) {
		resize(capacity * RESIZE_COEF);
	}

	//check for valid idx
	for (size_t i = size; i > size; i--) {
		data[i] = std::move(data[i - 1]);
	}

	data[idx] = obj;
	size++;
}

template<typename T>
void Vector<T>::insert(T&& obj, const size_t idx) {
	if (size == capacity) {
		resize(capacity * RESIZE_COEF);
	}

	//check for valid idx
	for (size_t i = size; i > size; i--) {
		data[i] = std::move(data[i - 1]);
	}

	data[idx] = std::move(obj);
	size++;
}

template<typename T>
bool Vector<T>::isEmpty() const {
	return size == 0;
}

template<typename T>
void Vector<T>::popBack() {
	if (isEmpty()) {
		throw std::runtime_error("Empty vector")
	}

	size--;
	data[size].~T();
}

template<typename T>
T Vector<T>::pop_back() {
	if (isEmpty()) {
		throw std::runtime_error("Empty vector")
	}

	return data[--size];
}

template<typename T>
void Vector<T>::erase(size_t idx) {
	if (isEmpty()) {
		throw std::runtime_error("Empty vector")
	}

	//check for idx
	size--;

	for (size_t i = idx + 1; i < size; i++) {
		data[i] = std::move(data[i + 1]);
	}
}

template<typename T>
T Vector<T>::erase_and_return(size_t idx) {
	if (isEmpty()) {
		throw std::runtime_error("Empty vector")
	}

	//check for idx
	T temp = data[idx];

	size--;

	for (size_t i = idx; i < size; i++) {
		data[i] = std::move(data[i + 1]);
	}

	return temp;
}

template<typename T>
void Vector<T>::clear() {
	size = 0;
}

template<typename T>
T& Vector<T>::operator[](const size_t idx) {
	//check idx
	return data[idx];
}

template<typename T>
const T& Vector<T>::operator[](const size_t idx) const {
	//check idx
	return data[idx];
}

int main()
{

}