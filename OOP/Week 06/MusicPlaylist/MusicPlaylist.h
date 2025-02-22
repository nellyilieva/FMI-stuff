#pragma once
#include <iostream>

const int MAX_SIZE = 30;

struct Duration {
private:
	unsigned minutes;
	unsigned seconds;

public:
	Duration();
	Duration(unsigned newMinutes, unsigned newSeconds);

	unsigned getMinutes() const;
	unsigned getSeconds() const;
};

class Song {
private:
	char* name;
	Duration duration;
	char* genre;

	void copyFrom(const Song& other);
	void free();

public:
	Song();
	Song(const char* newName, unsigned mins, unsigned secs, const char* newGenre);
	Song(const Song& other);
	Song& operator=(const Song& other);
	~Song();

	const char* getName() const;
	Duration getDuration() const;
	const char* getGenre() const;

	void setName(const char* newName);
	void setDuration(const Duration& newDuration);
	void setGenre(const char* newGenre);
};

class Playlist {
private:
	Song* arrSongs;
	int count;
	char name[MAX_SIZE];

	void copyFrom(const Playlist& other);
	void free();

public:
	Playlist();
	Playlist(const Playlist& other);
	Playlist& operator=(const Playlist& other);
	~Playlist();

	const char* getName() const;
	int getCount() const;

	int getSongIndex(const char* songName);
	void addSong(const Song& songToAdd);
	bool removeSong(const char* songName);
	void printPlaylistInfo();
};