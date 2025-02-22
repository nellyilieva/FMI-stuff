#include "MusicPlaylist.h"
#pragma once
#pragma warning(disable : 4996)


Duration::Duration() : minutes(0), seconds(0) {}

Duration::Duration(unsigned newMinutes, unsigned newSeconds) : minutes(newMinutes), seconds(newSeconds) {}

unsigned Duration::getMinutes() const {
	return minutes;
}
unsigned Duration::getSeconds() const {
	return seconds;
}


void Song::copyFrom(const Song& other) {
	name = new char[strlen(other.name)+ 1];
	strcpy(name, other.name);

	genre = new char[strlen(other.genre) + 1];
	strcpy(genre, other.genre);

	duration = other.duration;
}

void Song::free() {
	delete[] name;
	delete[] genre;
	duration = Duration(0, 0);
}

Song::Song() : duration(0, 0) {
	strcpy(name, "");
	strcpy(genre, "");
}

Song::Song(const char* newName, unsigned mins, unsigned secs, const char* newGenre) : duration(mins, secs) {
	strcpy(name, newName);
	strcpy(genre, newGenre);
}

Song::Song(const Song& other) {
	copyFrom(other);
}

Song& Song::operator=(const Song& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

Song::~Song() {
	free();
}

const char* Song::getName() const {
	return name;
}

Duration Song::getDuration() const {
	return duration;
}

const char* Song::getGenre() const {
	return genre;
}

void Song::setName(const char* newName) {
	strcpy(name, newName);
}

void Song::setDuration(const Duration& newDuration) {
	duration = Duration(newDuration);
}

void Song::setGenre(const char* newGenre) {
	strcpy(genre, newGenre);
}

void Playlist::copyFrom(const Playlist& other) {
	strcpy(name, other.name);
	count = other.count;

	arrSongs = new Song[other.count];
	for (int i = 0; i < count; i++) {
		arrSongs[i] = other.arrSongs[i];
	}
}

void Playlist::free() {
	delete[] arrSongs;
	arrSongs = nullptr;
}

Playlist::Playlist() : arrSongs(nullptr), count(0) {
	strcpy(name, "");
}

Playlist::Playlist(const Playlist& other) {
	copyFrom(other);
}

Playlist& Playlist::operator=(const Playlist& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

Playlist::~Playlist() {
	free();
}

const char* Playlist::getName() const {
	return name;
}

int Playlist::getCount() const {
	return count;
}

int Playlist::getSongIndex(const char* songName) {
	for (int i = 0; i < getCount(); i++) {
		if (strcmp(songName, arrSongs[i].getName()) == 0) {
			return i;
		}
	}
	return -1;
}

void Playlist::addSong(const Song& songToAdd) {
	if (getSongIndex(songToAdd.getName()) == -1) {
		arrSongs[count++] = songToAdd;
	}
}

bool Playlist::removeSong(const char* songName) {
	int idx = getSongIndex(songName);
	if (idx != -1) {
		for (int i = idx; i < getCount() - 1; i++) {
			arrSongs[i] = arrSongs[i + 1];
		}
		count--;
		return true;
	}

	return false;
}

void Playlist::printPlaylistInfo() {
	for (int i = 0; i < getCount(); i++) {
		std::cout << arrSongs[i].getName() << " " << arrSongs[i].getGenre() << " " 
			<< arrSongs[i].getDuration().getMinutes() << "-" << arrSongs[i].getDuration().getSeconds();
	}
}
