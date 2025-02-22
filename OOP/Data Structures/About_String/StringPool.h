#pragma once

class StringPool {
private:
	static constexpr int INITIAL_CAPACITY = 8;

	struct StringNode {
		char* data = nullptr;
		size_t referenceCount = 0;

		StringNode() = default;
		StringNode(const StringNode& other) = delete;
		StringNode& operator=(const StringNode& other) = default;
		~StringNode() = default;

		void allocateData(const char* str);
	};

	StringNode* nodes = nullptr;
	size_t size = 0;
	size_t capacity = INITIAL_CAPACITY;

	bool lowerBound(const char* str, size_t& idx);
	const char* insert(const char* str, size_t idx);
	void removeStringFromPool(size_t idx);

	void resize();

public:
	StringPool();

	StringPool(const StringPool& other) = delete;
	StringPool& operator=(const StringPool& other) = delete;
	~StringPool();

	const char* getString(const char* str);
	void removeString(const char* str);

	void print() const;
};