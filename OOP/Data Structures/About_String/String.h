#pragma once
#include <iostream>
#include <fstream>

class String {
private:
	char* data;
	size_t size = 0;
	size_t capacity = 8; //static variable

	void resize(size_t newCap);

	void copyFrom(const String& other);
	void moveFrom(String&& other);
	void free();

	explicit String(size_t size);

public:
	String();
	String(const char* newData);
	
	String(const String& other);
	String& operator=(const String& other);

	String(String&& other) noexcept;
	String& operator=(String&& other) noexcept;

	~String();

	operator bool() const;

	size_t getSize() const;
	size_t getCapacity() const;
	const char* c_str() const;

	String& operator+=(const String& other);
	String& operator+=(char ch);

	char& operator[](size_t idx);
	const char& operator[](size_t idx) const;

	friend std::ostream& operator<<(std::ostream os, const String& obj);
	friend std::istream& operator>>(std::istream is, String& obj);

	friend String operator+(const String& lhs, const String& rhs);
};

bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);
bool operator<(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator>=(const String& lhs, const String& rhs);