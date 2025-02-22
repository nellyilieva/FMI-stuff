#include <iostream>
#include <sstream>
#include <fstream>

//Имплементирайте клас за множество от естествени числа по критерии.
//Класът трябва да приема в конструктора цяло число - максималното число
//което може да се запази в множеството и две булеви функции : за включване на число(тези, които да са елементи на множеството) 
//и изключване на число (тези, които първата функция връща истина, но искаме да не ги поставим в множеството).
//Едно цяло число е в множеството, когато функията за включване връща истина за него и ф - ята на изключване връща лъжа за него.
//Трябва да имате функции за проверка дали число е в множеството(за константно време), 
//за връщане на броя на елементите и за принтиране на множеството.
//
//Примерен интерфейс :
//
//int main()
//{
//	SetByCriteria s(10, isPrime, isOdd);
//
//	s.print(); // {2}
//}

class DynamicSet {
private:
	uint8_t* buckets = nullptr;  //this could be unsigned char
	size_t bucketsCount = 0;
	unsigned maxNum = 0;
	const unsigned elementsInBucket = sizeof(uint8_t) * 8;

	unsigned getBucketIdx(unsigned num) const;

	void copyFrom(const DynamicSet& other);
	void moveFrom(DynamicSet&& other);
	void free();

public:
	DynamicSet(unsigned maxNum);

	DynamicSet(const DynamicSet& other);
	DynamicSet& operator=(const DynamicSet& other);

	DynamicSet(DynamicSet&& other) noexcept;
	DynamicSet& operator=(DynamicSet&& other) noexcept;

	~DynamicSet();

	unsigned getMaxNum() const;

	void add(unsigned num);
	void remove(unsigned num);

	bool isInSet(unsigned num) const;

	void printNumbers() const;

	void clear();

	friend DynamicSet unionOfSets(const DynamicSet& lhs, const DynamicSet& rhs);
	friend DynamicSet intersectionOfSets(const DynamicSet& lhs, const DynamicSet& rhs);
};


//use functoins from DynamicSet
class SetByCriteria : private DynamicSet {
private:
	struct Criteria {
		bool(*includes)(unsigned n);
		bool(*excludes)(unsigned n);
	} criteria;

	void fillSet();

public:
	SetByCriteria(unsigned maxNumber, bool(*includes)(unsigned n), bool(*excludes)(unsigned n));

	void setIncludes(bool(*includes)(unsigned n));
	void setExcludes(bool(*excludes)(unsigned n));

	bool contains(unsigned num) const;
	
	void print() const;
};


//Имплементирайте и клас за множество по стринг.
//Множество, което в конструктора приема цяло число - максималното число, което може да се запази в множеството 
//и символен низ - числата, които да се запазят, разделени с интервал.
//Трябва да имате функция за промяна на стринга,
//както и за промяна на символ по индекс.
//Трябва да имате и функции за проверка дали число е в множеството(за константно време),
//за връщане на броя на елементите и за принтиране на множеството.
//
//int main()
//{
//	SetByString s(300, "1 2 3");
//
//	s.print(); // {1, 2, 3}
//
//	s.setAt(1, '1');
//
//	s.print(); // {3, 112}
//}

class SetByString : private DynamicSet {
private:
	char* str = nullptr;
	size_t length = 0;

	void fillSet();

	void copyFrom(const SetByString& other);
	void moveFrom(SetByString&& other);
	void free();

public:
	SetByString(unsigned maxNum, const char* str);

	SetByString(const SetByString& other);
	SetByString& operator=(const SetByString& other);

	SetByString(SetByString&& other) noexcept;
	SetByString& operator=(SetByString&& other) noexcept;

	~SetByString();

	bool contains(unsigned num) const;

	void print() const;

	void setAt(unsigned idx, char ch);
};
