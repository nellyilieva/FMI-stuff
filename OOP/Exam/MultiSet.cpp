#include <iostream>

//Напишете клас MultiSet, който съдържа мултимножество от числа в диапазона от 0 до n - 1.
//Стойността на n се приема от конструктора на класа.
//Всяко число може да се среща най - много 3 пъти в рамките на мултимножеството.
//
//Във всеки един момент обект от вашия клас трябва да има задължително минимален възможен размер.
//
//Трябва да имате следната функционалност :
//
//Добавяне на число, ако се среща по - малко от 3 пъти в множеството.
//Премахване на число, ако се съдържа.
//Проверка колко пъти се съдържа число.
//Принтиране на всички числа, които съдържа множеството.
//Функция, която приема две множества и връща тяхното сечение.
//Функция, която приема две множества и връща тяхното обединение.

//when the number can occure only 1 time, we represent it with 1 bit
//here we represent the number with 2 bits (2 because in binary 3 is 11 and according to the occurance we set the bits)

const unsigned MAX_OCCURANCES = 3;
const unsigned MAX_IN_BUCKET = 4;

class MultiSet {
private:
	uint8_t* buckets;
	unsigned n;
	unsigned countOfBuckets;

	void copyFrom(const MultiSet& other) {
		n = other.n;
		countOfBuckets = other.countOfBuckets;

		for (int i = 0; i < countOfBuckets; i++) {
			buckets[i] = other.buckets[i];
		}
	}

	void free() {
		delete[] buckets;
	}

public:
	explicit MultiSet(unsigned n) {
		this->n = n;
		countOfBuckets = n / MAX_IN_BUCKET + 1;
		buckets = new uint8_t[countOfBuckets]{ 0 };
	}

	MultiSet(const MultiSet& other) {
		copyFrom(other);
	}

	MultiSet& operator=(const MultiSet& other) {
		if (this != &other) {
			free();
			copyFrom(other);
		}

		return *this;
	}

	~MultiSet() {
		free();
	}

	bool add(unsigned num) {
		unsigned bucketIdx = num / MAX_IN_BUCKET;
		unsigned bitIdx = num % MAX_IN_BUCKET;

		uint8_t mask = 1;
		mask <<= bitIdx * 2;

		uint8_t& curr = buckets[bucketIdx];

		unsigned occur = getOccurances(num);

		switch (occur) {
		case 0:
		case 2:
		{
			curr |= mask;
			return true;
		}
		case 1:
		{
			mask = ~mask;
			curr &= mask;
			mask = ~mask;
			mask <<= 1;
			curr |= mask;
			return true;
		}
		default:
			return false;
		}

	}

	bool remove(unsigned num) {
		unsigned bucketIdx = num / MAX_IN_BUCKET;
		unsigned bitIdx = num % MAX_IN_BUCKET;

		uint8_t mask = 1;
		mask <<= bitIdx * 2;

		uint8_t& curr = buckets[bucketIdx];

		unsigned occur = getOccurances(num);

		switch (occur) {
		case 3:
		case 1:
		{
			mask = ~mask;
			curr &= mask;
			return true;
		}
		case 2:
		{
			curr |= mask;
			mask <<= 1;
			mask = ~mask;
			curr &= mask;
			return true;
		}
		default:
			return false;
		}
	}

	void printNumber(unsigned num, unsigned occurances) const {
		for (unsigned i = 0; i < occurances; i++)
			std::cout << num << " ";
	}

	void printSet() const {
		std::cout << '{';
		for (unsigned i = 0; i < n; i++)
		{
			unsigned occurrences = getOccurances(i);
			printNumber(i, occurrences);
		}
		std::cout << '}';
	}

	unsigned getOccurances(unsigned num) const {
		unsigned bucketIdx = num / MAX_IN_BUCKET;
		unsigned bitIdx = num % MAX_IN_BUCKET;

		uint8_t mask = 1;
		//to go to the correct bit
		mask <<= bitIdx * 2;

		uint8_t& curr = buckets[bucketIdx];

		bool isFirstUp = ((curr & mask) == mask);
		mask <<= 1;
		bool isSecondUp = ((curr & mask) == mask);

		return (isFirstUp * (1 << 0) + isSecondUp * (1 << 1));
	}

	void addNumberMultipleTimes(unsigned num, unsigned times) {
		if (times > MAX_OCCURANCES)
			times = MAX_OCCURANCES;

		for (unsigned i = 0; i < times; i++)
			add(num);
	}
};

int main()
{
   
}
