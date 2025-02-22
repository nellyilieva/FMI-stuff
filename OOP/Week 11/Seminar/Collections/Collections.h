#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include <stdexcept>
#pragma warning (disable: 4996)


//Да се реализира полиморфна йерархия за работа колекции от цели числа.
//Всяка от колекциите трябва да съдържа :
//
//add - Добавя елемент към колекцията.
//remove - Премахва елемент от колекцията.
//count - Връща колко елемента от този тип имаме.
//contains - Връща дали елемента се съдържа в колекцията.
// 
//Ща раелизираме следните колекции :
//
//NormalCollection - Това е стандартната динамична колекция.
//add - O(1)
//remove - O(n) (remove e O(1) ако премахваме по индекс)
//count - O(n)
//contains - O(n)
// 
//SortedCollection - Колекция в която елементите са сортирани
//add - O(n)
//remove - O(n)
//count - O(log(n))
//contains - O(log(n)) - двоично търсене. 
// 
//IntervalCollection - Колекция, която допуска числа само от определен интервал(примерно[5, 49])
//add - O(1)
//remove - O(1)
//count - O(1)
//contains - O(1)
//
//Напишете функция, която приема произвола колекция от горните и измерва нейния performance за подадени входни данни.

//we have this class hierarchy : Collection(abstract) <- Set & Dynamic(abstract) <- (Pure number(abstract) <- Normal & Sorted) & Interval

//we start with abstract class for collection

class Collection {
public:
	virtual void add(int n) = 0;
	virtual void remove(int n) = 0;
	virtual unsigned count(int n) const = 0;
	virtual bool contains(int n) const = 0;

	virtual ~Collection() = default;
};

//dynamic collection -> dynamic arr management
class DynamicCollection : public Collection {
protected:
	int* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void resize(size_t newCap);

	void copyFrom(const DynamicCollection& other);
	void moveFrom(DynamicCollection&& other);
	void free();

	DynamicCollection(size_t capacity);

public:
	DynamicCollection();

	DynamicCollection(const DynamicCollection& other);
	DynamicCollection& operator=(const DynamicCollection& other);

	DynamicCollection(DynamicCollection&& other) noexcept;
	DynamicCollection& operator=(DynamicCollection&& other) noexcept;

	~DynamicCollection();
};

//pure number collection -> store numbers that will only be in the set (normal and sorted)
class PureNumberCollection : public DynamicCollection {};

//normal unordered collection
class NormalCollection : public PureNumberCollection {
public:
	void add(int n) override;
	void remove(int n) override;
	unsigned count(int n) const override;
	bool contains(int n) const override;
};


//sorted collection; we have to make sure that tje collection stays sorted after the operations
class SortedCollectioin : public PureNumberCollection {
private:
	// returns the leftmost index in which we can insert n; binary search
	int lowerBound(int n) const;

	// returns the rightmost index in which we can insert n; binary search
	int upperBound(int n) const;

public:
	void add(int n) override;
	void remove(int n) override;
	unsigned count(int n) const override;
	bool contains(int n) const override;
};

//interval collection -> like bitset but can have repeating numbers!
class IntervalCollection : public DynamicCollection {
private:
	int start;
	int end;

public:
	IntervalCollection(int start, int end);
	unsigned intervalLength() const;

	void add(int n) override;
	void remove(int n) override;
	unsigned count(int n) const override;
	bool contains(int n) const override;
};

//the function of set -> manages collection of UNIQUE numbers; interval is not because it will just be bitset then
//polymorphic because it can be both normal and sorted collection

enum CollectionType {
	NORMAL_COLLECTION,
	SORTED_COLLECTION
};

class Set : public Collection {
private:
	PureNumberCollection* collection;

public:
	Set(CollectionType type);  //here is the factory
	
	Set(const Set& other) = delete;
	Set& operator=(const Set& other) = delete;

	void add(int n) override;
	void remove(int n) override;
	unsigned count(int n) const override;
	bool contains(int n) const override;

	~Set();
};

