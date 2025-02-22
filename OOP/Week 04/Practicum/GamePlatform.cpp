#include <iostream>
#include <cstring>
#include <fstream>
#pragma warning (disable: 4996)
#include "GamePlatform.h"

Game::Game() : price(0.0), isAvailable(false) {
	strcpy(title, " ");
}

Game::Game(const char* title, double price, bool isAvailable) {
	setTitle(title);
	setAvailability(isAvailable);
	setPrice(price);
}

const char* Game::getTitle() const {
	return title;
}

double Game::getPrice() const {
	return price;
}

bool Game::getAvailability() const {
	return isAvailable;
}

void Game::setTitle(const char* title) {
	if (title == nullptr || strlen(title) >= MAX_SIZE) {
		strcpy(this->title, "");
	}
	else {
		strcpy(this->title, title);
	}
}

void Game::setPrice(double price) {
	if (price < 0) {
		this->price = 0.0;
	}
	else {
		this->price = price;
	}
}

void Game::setAvailability(bool isAvailable) {
	this->isAvailable = isAvailable;
}

bool Game::isFree() const {
	return (price < 0.001 && price > -0.001);
}

void Game::print() const {
	std::cout << "Title: " << title << std::endl << "Price: " << price << std::endl << "Is it Available: " << isAvailable << std::endl;
}

void Game::writeToFile(std::ofstream& ofs) {
	ofs << getTitle() << '\n' << getPrice() << '\n' << getAvailability() << '\n';
}

void Game::readFromFile(std::ifstream& ifs) {
	ifs.getline(title, MAX_SIZE);
	ifs >> price;
	ifs >> isAvailable;
	ifs.ignore();
}


bool GamePlatform::isFull() const {
	return count >= capacity;
}

bool GamePlatform::isEmpty() const {
	return count == 0;
}


GamePlatform::GamePlatform(const Game* games, int count) {
	this->games = new Game[count];
	this->count = count;
	this->capacity = count;

	for (int i = 0; i < count; i++) {
		this->games[i].setTitle(games[i].getTitle());
		this->games[i].setPrice(games[i].getPrice());
		this->games[i].setAvailability(games[i].getAvailability());
	}

}

GamePlatform::GamePlatform(int capacity) {
	this->capacity = capacity;
	this->count = 0;
	this->games = new Game[capacity];

}

GamePlatform::~GamePlatform() {
	if (games != nullptr) {
		delete[] games;
	}

	count = 0;
	capacity = 0;
}

bool GamePlatform::addGame(const Game& g) {
	if (isFull()) {
		return false;
	}

	games[count].setTitle(g.getTitle());
	games[count].setPrice(g.getPrice());
	games[count].setAvailability(g.getAvailability());
	count++;

	return true;
}

const Game* GamePlatform::getGame(int idx) const {
	if (0 <= idx && idx <= capacity) {
		return &games[idx];
	}
	return nullptr;
}

void GamePlatform::printGames() const {
	for (int i = 0; i < count; i++) {
		games[i].print();
	}
}

const Game* GamePlatform::getCheapest() const {
	if (isEmpty()) {
		return nullptr;
	}

	double currMin = games[0].getPrice();
	int minIdx = 0;

	for (int i = 1; i < count; i++) {
		if (currMin > games[i].getPrice()) {
			currMin = games[i].getPrice();
			minIdx = i;
		}
	}

	return &games[minIdx];
}

const Game* GamePlatform::getMostexpensive() const {
	if (isEmpty()) {
		return nullptr;
	}

	double currMax = games[0].getPrice();
	int maxIdx = 0;

	for (int i = 1; i < count; i++) {
		if (currMax < games[i].getPrice()) {
			currMax = games[i].getPrice();
			maxIdx = i;
		}
	}

	return &games[maxIdx];
}

void GamePlatform::printAllFreeGames() const {
	if (isEmpty()) {
		return;
	}

	for (int i = 0; i < count; i++) {
		if (games[i].getPrice() == 0)
			games[i].print();
	}
}

void GamePlatform::removeGame(int idx) {
	if (0 <= idx && idx <= capacity) {
		return;
	}

	for (int i = idx; i < count - 1; i++) {
		games[i].setTitle(games[i + 1].getTitle());
		games[i].setPrice(games[i + 1].getPrice());
		games[i].setAvailability(games[i + 1].getAvailability());
	}
	count--;
}

void GamePlatform::serializeGamePlatrform(const char* fileName) {
	std::ofstream ofs(fileName);

	if (!ofs.is_open()) {
		return;
	}

	ofs << count << '\n';

	for (int i = 0; i < count; i++) {
		games[i].writeToFile(ofs);
	}

	ofs.close();
}

void GamePlatform::deserializeGamePlatform(const char* fileName) {
	std::ifstream ifs(fileName);

	if (!ifs.is_open()) {
		return;
	}

	ifs >> count;
	ifs.ignore(); //the new line
	games = new Game[count];

	for (int i = 0; i < count; i++) {
		games[i].readFromFile(ifs);
	}

	ifs.close();
}


int main() {
	Game g1("First", 45.2, true);
	Game g2("Second", 3.3, false);
	Game g3("Third", 45.2, true);
	Game g4("Forth", 3.3, true);
	Game g5("Fifth", 45.2, true);
	Game g6("Six", 3.3, false);

	Game games[] = {
		Game("First", 45.2, true),
		Game("Second", 3.3, false),
		Game("Third", 45.2, true),
		Game("Forth", 3.3, true),
		Game("Fifth", 45.2, true),
		Game("Six", 3.3, false)
	};

	GamePlatform gp(games, 6);

	gp.serializeGamePlatrform("test.txt");

	GamePlatform newGP(10);
	newGP.deserializeGamePlatform("test.txt");
	newGP.printGames();
}
