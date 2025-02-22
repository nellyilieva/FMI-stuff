#pragma once
#include <iostream>
#include <cstring>
#pragma warning (disable: 4996)

constexpr unsigned int MAX_SIZE = 64;

class Game {
private:
	char title[MAX_SIZE];
	double price;
	bool isAvailable;

public:
	Game();
	Game(const char* title, double price, bool isAvailable);

	const char* getTitle() const;
	double getPrice() const;
	bool getAvailability() const;

	void setTitle(const char* title);
	void setPrice(double price);
	void setAvailability(bool isAvailable);

	bool isFree() const;
	void print() const;

	void writeToFile(std::ofstream& ofs);
	void readFromFile(std::ifstream& ifs);
};

class GamePlatform {
private:
	Game* games = nullptr;
	int count = 0;
	int capacity = 0;

	bool isFull() const;
	bool isEmpty() const;

public:
	GamePlatform() = default;
	GamePlatform(const Game* games, int count);
	GamePlatform(int size);

	~GamePlatform();

	bool addGame(const Game& g);
	const Game* getGame(int idx) const;
	void printGames() const;

	const Game* getCheapest() const;
	const Game* getMostexpensive() const;

	void printAllFreeGames() const;

	void removeGame(int idx);

	void serializeGamePlatrform(const char* fileName);

	void deserializeGamePlatform(const char* fileName);
};