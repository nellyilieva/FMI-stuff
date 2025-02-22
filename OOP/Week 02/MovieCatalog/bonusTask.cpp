#include <iostream>
#include <fstream>
#include <cstring>


const int NAME_SIZE = 128;

enum class ErrorInCatalog {
    catalog_not_open,
    read_from_empty_catalog,
    movie_not_in_catalog,
    no_error_occurred
};

struct SafeAnswer {
    int number;
    ErrorInCatalog error;
};

struct Movie {
    char name[NAME_SIZE];
    unsigned int price;
};

size_t getFileSize(std::ifstream& ifs) {
    size_t currPos = ifs.tellg();

    ifs.seekg(0, std::ios::end);
    size_t fileSize = ifs.tellg();

    ifs.seekg(currPos);
    return fileSize;
}

unsigned getCharCountFromFile(std::ifstream& ifs, char ch) {
    unsigned int count = 0;

    while (true)
    {
        char current = ifs.get();
        if (ifs.eof())
            break;

        if (current == ch)
            count++;
    }

    return count;
}

Movie readMovie(std::ifstream& ifs) {
    Movie movie;

    ifs >> movie.name >> movie.price;

    return movie;
}


SafeAnswer getNumberOfMovies(const char* fileName) {
    SafeAnswer answer;

    std::ifstream file(fileName);

    if (!file.is_open()) {
        answer.number = 0;
        answer.error = ErrorInCatalog::catalog_not_open;

        return answer;
    }

    if (!getFileSize(file)) {
        answer.number = 0;
        answer.error = ErrorInCatalog::read_from_empty_catalog;

        return answer;
    }

    while (!file.eof()) {
        answer.number = getCharCountFromFile(file, '\n') + 1;
        answer.error = ErrorInCatalog::no_error_occurred;

        return answer;
    }

    file.close();
}

SafeAnswer averagePrice(const char* fileName) {
    SafeAnswer answer;

    std::ifstream file(fileName);

    if (!file.is_open()) {
        answer.number = 0;
        answer.error = ErrorInCatalog::catalog_not_open;

        return answer;
    }

    int countOfMovies = 0;
    int avgPrice = 0;

    while (!file.eof()) {
        Movie curr = readMovie(file);
        countOfMovies++;
        avgPrice += curr.price;
    }

    if (countOfMovies == 0) {
        answer.error = ErrorInCatalog::read_from_empty_catalog;
        answer.number = 0;

        return answer;
    }

    avgPrice /= countOfMovies;

    answer.number = avgPrice;
    answer.error = ErrorInCatalog::no_error_occurred;

    file.close();

    return answer;
}

SafeAnswer getMoviePrice(const char* fileName, const char* movieName) {
    SafeAnswer answer;

    std::ifstream file(fileName);

    if (!file.is_open()) {
        answer.number = 0;
        answer.error = ErrorInCatalog::catalog_not_open;

        return answer;
    }

    if (!getFileSize(file)) {
        answer.number = 0;
        answer.error = ErrorInCatalog::read_from_empty_catalog;

        return answer;
    }

    while (!file.eof()) {
        Movie curr = readMovie(file);

        if (strcmp(curr.name, movieName) == 0) {
            answer.number = curr.price;
            answer.error = ErrorInCatalog::no_error_occurred;

            return answer;
        }
    }

    answer.number = 0;
    answer.error = ErrorInCatalog::movie_not_in_catalog;

    return answer;
}

Movie* saveMoviesInArray(std::ifstream& ifs, int countOfMovies) {
    Movie* movies = new Movie[countOfMovies];

    while (!ifs.eof()) {
        for (int i = 0; i < countOfMovies; i++) {
            movies[i] = readMovie(ifs);
        }

        ifs.close();
    }

    return movies;
}

void deleteMovies(Movie*& movies) {
    delete[] movies;
}

void sortMoviesInArray(Movie*& movies, size_t countOfMovies) {
    for (size_t i = 0; i < countOfMovies - 1; i++) {
        size_t minIndex = i;

        for (size_t j = i; j < countOfMovies; j++) {
            if (movies[j].price < movies[minIndex].price) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            std::swap(movies[i], movies[minIndex]);
        }
    }
}

ErrorInCatalog saveMoviesSorted(const char* catalogName, const char* catalogSortedName) {
    int countMovies = getNumberOfMovies(catalogName).number;
    
    std::ifstream file(catalogName);

    if (!file.is_open()) {
        return ErrorInCatalog::catalog_not_open;
    }
    
    Movie* movies = saveMoviesInArray(file, countMovies);

    file.close();

    sortMoviesInArray(movies, countMovies);

    std::ofstream ofs(catalogSortedName);

    if (!ofs.is_open()) {
        return ErrorInCatalog::catalog_not_open;
    }

    for (int i = 0; i < countMovies; i++) {
        ofs << movies[i].name << " " << movies[i].price << "\n";
    }

    ofs.close();
    deleteMovies(movies);
    return ErrorInCatalog::no_error_occurred;
}

int main()
{
    SafeAnswer safeNumberOfMovies = getNumberOfMovies("movieCatalog.txt");
    if (safeNumberOfMovies.error == ErrorInCatalog::no_error_occurred) {
        std::cout << "The number of movies is: " << safeNumberOfMovies.number << std::endl;
    }
    SafeAnswer safeAveragePrice = averagePrice("movieCatalog.txt");
    if (safeAveragePrice.error == ErrorInCatalog::no_error_occurred) {
        std::cout << "The average price is: " << safeAveragePrice.number << std::endl;
    }

    SafeAnswer safePrice = getMoviePrice("movieCatalog.txt", "Black-bullet");
    if (safePrice.error == ErrorInCatalog::no_error_occurred) {
        std::cout << "The price for the Black bullet movies is: " << safePrice.number << std::endl;
    }

    ErrorInCatalog errorSorting = saveMoviesSorted("movieCatalog.txt", "movieCatalogSorted.txt");
    if (errorSorting == ErrorInCatalog::no_error_occurred) {
        std::cout << "Look the content of the movieCatalogSorted.txt file" << std::endl;
    }
}

