//// Playlist.cpp : This file contains the 'main' function. Program execution begins and ends there.
////
//
#include <iostream>;
#include <fstream>;


namespace UtilityFunctions {
    void writeStringToFileWithTerminator(const char* filename, const char* data) {
        std::ofstream ofs(filename, std::ios::binary);
        if (!ofs.is_open()) {
            return;
        }
        ofs.write(data, strlen(data) * sizeof(char));
        const char sentinel = '\0';
        ofs.write((const char*)&sentinel, 1 * sizeof(char));
        ofs.close();
    }
}
enum Genre : char {
    rock = 1 << 0,
    pop = 1 << 1,
    hipHop = 1 << 2,
    electronic = 1 << 3,
    jazz = 1 << 4,
};

namespace Constants {
    constexpr int MAX_SONGS = 30;
    constexpr int MAX_NAME_SIZE = 64;
    constexpr int MAX_CONTENT_SIZE = 256;
    constexpr int GENRES_COUNT = 5;
    const int BIT_COUNT = 8;
}
 

class Time {
private:
    int hour;
    int minutes;
    int seconds;
public:
    int getHour() const {
        return this->hour;
    }
    int getMinutes() const {
        return this->minutes;
    }
    int getSeconds() const {
        return this->seconds;
    }
    void setHours(int hours) {
        this->hour = hours;
    }
    void setMinutes(int minutes) {
        this->minutes = minutes;
    }
    void setSeconds(int seconds) {
        this->seconds = seconds;
    }
    Time(int hour, int minutes, int seconds) {
        setHours(hour);
        setMinutes(minutes);
        setSeconds(seconds);
    }
    Time() {
        setHours(0);
        setMinutes(0);
        setSeconds(0);
    }

    void printTime() {
        printFormattedTime(this->hour);
        std::cout << ":";
        printFormattedTime(this->minutes);
        std::cout << ":";
        printFormattedTime(this->seconds);
    }


    void printFormattedTime(int time) {
        if (time >= 10) {
            std::cout << time;
            return;
        }
        std::cout << "0" << time;
    }

    int getTimeConvertedToSecs() {
        return this->hour * 3600 + this->minutes * 60 + this->seconds;
    }
};

class Song {
private:
    char name[Constants::MAX_NAME_SIZE +1];
    Time duration;
    char genre;
    char content[Constants::MAX_CONTENT_SIZE +1];
public:
    const char* getName() const {
        return this->name;
    }
    const char* getContent() const {
        return this->content;
    }
    Time getDuration() const {
        return this->duration;
    }
    char getGenre() const {
        return this->genre;
    }

    void setName(const char* name) {
        int len = strlen(name);
        strcpy_s(this->name, len + 1, name);
    }
    void setContent(const char* content) {
        std::ifstream ifs(content, std::ios::binary);
        if (!ifs.is_open()) {
            return;
        }
        ifs.read(this->content, Constants::MAX_CONTENT_SIZE);
        ifs.close();
    }
    void combineSongMusic(int index , const Song& song) {
        this->content[index] ^= song.getContent()[index];
    }

    void setDuration(int hour, int minutes, int seconds) {
        this->duration = Time(hour, minutes, seconds);
    }

    void setGenre(const char* genreStr) {
        char genre = 0;
        while (*genreStr) {
            switch (*genreStr)
            {
            case 'r':
                genre = Genre::rock | genre;
                break;
            case 'p':
                genre = Genre::pop | genre;
                break;
            case 'j':
                genre = Genre::jazz | genre;
                break;
            case 'h':
                genre = Genre::hipHop | genre;
                break;
            case 'e':
                genre = Genre::electronic | genre;
                break;
            }
            genreStr++;
        }
        this->genre = genre;
    }
    Song(const char* name, int hours, int minutes, int seconds, const char* genreStr, const char* filename) {
        this->setName(name);
        this->setDuration(hours, minutes, seconds);
        this->setGenre(genreStr);
        this->setContent(filename);
    }

    Song(){
        this->setName("");
        this->setContent(""); // doesn't exist file with location "";
        this->genre = '\0';
    }

    void print() {
        std::cout << this->name << ", ";
        this->duration.printTime();
        std::cout << ", ";
        this->printGenre();
    }

    void printGenre() {
        const char* genresStr[Constants::GENRES_COUNT] = {"Rock", "Pop", "Jazz", "Electronic", "HipHop"};
        const char* genresFound[Constants::GENRES_COUNT];
        Genre genres[] = { Genre::rock,Genre::pop, Genre::jazz, Genre::electronic, Genre::hipHop };
        int findCounter = 0;
        for (int i = 0; i < Constants::GENRES_COUNT; i++) {
            if (genres[i] & this->genre) {
                genresFound[findCounter++] = genresStr[i];
            }
        }
        for (int i = 0; i < findCounter; i++) {
            std::cout << genresFound[i];
            if (i != findCounter - 1) {
                std::cout << "&";
            }
        }
    }
    void setBit(int index, int k) {
        char newChar = (1 << k) | this->content[index];
        this->content[index] = newChar;
    }

};


class Playlist {
private:
    Song songs[Constants::MAX_SONGS];
    size_t songsLen;
public:
    size_t getSongsLen() const {
        this->songsLen;
    }
    const Song* getSongs() const {
        return this->songs;
    }

    Playlist() {
        this->songsLen = 0;
    }

    void add(const char* name, int hours, int minutes, int seconds, const char* genreStr, const char* filename) {
        if (this->findByName(name)) {
            std::cout << "Name already created" << std::endl; 
            return;
        }
        if (this->songsLen + 1 < Constants::MAX_SONGS) {
            Song newSong(name, hours, minutes, seconds, genreStr, filename);
            songs[this->songsLen++] = newSong;
        }
    }
    void print() {
        for (int i = 0; i < this->songsLen; i++) {
            songs[i].print();
            std::cout << std::endl;
        }
    }

    void sort(bool(*predicate)(const Song& first, const Song& second)) {
        for (int i = 0; i < this->songsLen; i++)
        {
            int minIndex = i;
            for (int j = i + 1; j < this->songsLen; j++)
            {
                if (predicate(this->songs[j], this->songs[minIndex]))
                    minIndex = j;

            }
            if (i != minIndex)
                std::swap(this->songs[i], this->songs[minIndex]);
        }
    }

    void sortByName() {
        sort([](const Song& first, const Song& second) { return strcmp(first.getName(), second.getName()) < 0; });
    }

    void sortByDuration() {
        sort([](const Song& first, const Song& second) { return first.getDuration().getTimeConvertedToSecs() - second.getDuration().getTimeConvertedToSecs() < 0; });
    }

    Song* findByName(const char* name) {
        if (!name || !strcmp(name, "")) {
            return nullptr;
        }
        Song song;
        song.setName(name);
        for (int i = 0; i < this->songsLen; i++) {
            if (!strcmp(song.getName(), this->songs[i].getName())) {
                return &this->songs[i];
            }
        }
        return nullptr;
    }

    void findGenre(const char* genre) {
        Song song;
        song.setGenre(genre);
        for (int i = 0; i < this->songsLen; i++) {
            if ((song.getGenre() & this->songs[i].getGenre())) {
                this->songs[i].print();
                std::cout << std::endl;
            }
        }
    }
    

    
    void save(const char* name, const char* filename) {
        const Song *s = this->findByName(name);
        if (!s) {
            return;
        }
        UtilityFunctions::writeStringToFileWithTerminator(filename, s->getContent());
    }


    void setKthBit(Song& song, int k) {
        for (int i = strlen(song.getContent()) * Constants::BIT_COUNT - k; i >= 0; i -= k) {
            int index = i / Constants::BIT_COUNT;
            song.setBit(index, i%Constants::BIT_COUNT);
        }
    }


    void mix(const char* firstName, const char* secondName) {
        if (!firstName || !secondName) {
            return; 
        }
        Song* destination = this->findByName(firstName);
        Song* secondSong = this->findByName(secondName);

        if (!destination || !secondSong) {
            std::cout << "Invalid song while mixing" << std::endl;
            return;
        }

        int minWordLen = std::min(strlen(destination->getContent()), strlen(secondSong->getContent()));
        for (int i = minWordLen - 1; i >= 0; i--) {
            destination->combineSongMusic(i, *secondSong);
        }
    }
};




using UtilityFunctions::writeStringToFileWithTerminator;
int main()
{

}

