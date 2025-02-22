#include <iostream>
#include <cstring>
#include <fstream>

const int MAX_CHAR_NAME = 50;

enum class Type {
    NORMAL,
    FIRE,
    WATER,
    GRASS,
    ELECTRIC,
    GHOST,
    FLYING
};

struct Pokemon {
    char name[MAX_CHAR_NAME + 1];
    Type type;
    unsigned int power = 0;
};

struct PokemonHandler {
    char nameFile[MAX_CHAR_NAME + 1];
};

bool inInterval(unsigned int power) {
    return 10 <= power && power <= 1000;
}

size_t getFileSize(std::ifstream& ifs) {
	size_t currPos = ifs.tellg();

	ifs.seekg(0, std::ios::end);
	size_t fileSize = ifs.tellg();

	ifs.seekg(currPos, std::ios::beg);

	return fileSize;
}

const char* getTypeStr(Type t) {
    switch (t)
    {
    case Type::NORMAL: return "NORMAL";
    case Type::FIRE: return "FIRE";
    case Type::WATER: return "WATER";
    case Type::GRASS: return "GRASS";
    case Type::ELECTRIC: return "ELECTRIC";
    case Type::GHOST: return "GHOST";
    case Type::FLYING: return "FLYING";
    default: return "UNKNOWN";
    }
}

Type readType(int typeNumber) {
    switch (typeNumber) {
    case 0:
        return Type::NORMAL;
    case 1:
        return Type::FIRE;
    case 2:
        return Type::WATER;
    case 3:
        return Type::GRASS;
    case 4:
        return Type::ELECTRIC;
    case 5:
        return Type::GHOST;
    case 6:
        return Type::FLYING;
    }
}


Pokemon createPokemon() {
    Pokemon pokemon;

    char name[MAX_CHAR_NAME];
    int typeNumber;
    unsigned int power;

    std::cin >> name >> typeNumber >> power;

    Type t = readType(typeNumber);

    if (!inInterval(power)) {
        return {};
    }

    strcpy(pokemon.name, name);
    pokemon.type = t;
    pokemon.power = power;

    return pokemon;
}

Pokemon createPokemonFromBinary(std::ifstream& ifs) {
    Pokemon pokemon;

    ifs.read((char*)&pokemon, sizeof(Pokemon));
   // std::cout << pokemon.name << " " << (int)pokemon.type << " " << pokemon.power << std::endl;

    return pokemon;
}

void writePokemon(const char* fileName, const Pokemon& pokemon) {
    std::ofstream file(fileName, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        return;
    }

    file.write((const char*)&pokemon, sizeof(pokemon));

    file.close();
}

PokemonHandler newPokemonHandler(const char* fileName) {
    PokemonHandler handler;

    strcpy(handler.nameFile, fileName);

    return handler;
}

int size(const PokemonHandler& ph) {
    std::ifstream file(ph.nameFile, std::ios::binary);

    if (!file.is_open()) {
        return -1;
    }

    int fileSize = getFileSize(file);
    int pokemonSize = fileSize / sizeof(Pokemon);

    file.close();

    return pokemonSize;
}

Pokemon at(const PokemonHandler& ph, int i) {
    int pokemonCount = size(ph);

    if (i < 0 || i >= pokemonCount) {
        return {};
    }

    std::ifstream file(ph.nameFile, std::ios::binary);

    if (!file.is_open()) {
        return {};
    }

    file.seekg(i * sizeof(Pokemon), std::ios::beg);

    Pokemon pokemon = createPokemonFromBinary(file);

    file.close();

    return pokemon;
}

void swap(const PokemonHandler& ph, int i, int j) {
    int pokemonCount = size(ph);

    if (i < 0 || i >= pokemonCount|| j < 0 || j >= pokemonCount) {
        return;
    }

    Pokemon first = at(ph, i);
    Pokemon second = at(ph, j);

    std::fstream file(ph.nameFile, std::ios::binary | std::ios::in | std::ios::out);

    if (!file.is_open()) {
        return;
    }

    file.seekp(i * sizeof(Pokemon));
    writePokemon(ph.nameFile, second);

    file.seekp(j * sizeof(Pokemon));
    writePokemon(ph.nameFile, first);

    file.close();
}

void insert(const PokemonHandler& ph, const Pokemon& pokemon)    {
    int sizePokemon = sizeof(Pokemon);

    std::fstream file(ph.nameFile, std::ios::binary | std::ios::in | std::ios::out);

    if (!file.is_open()) {
        return;
    }

    Pokemon curr;
    int position = 0;

    while (file.read((char*)&curr, sizePokemon)) {
        if (pokemon.power < curr.power) {
            break;
        }
        position++;
    }

    file.seekg(0, std::ios::end);

    int endPosition = file.tellg() / sizePokemon;

    for (int i = endPosition - 1; i >= position; i--) {
        swap(ph, i, i + 1);
    }

    file.seekp(position * sizePokemon);
    writePokemon(ph.nameFile, pokemon);

    file.close();

}

void textify(const PokemonHandler& ph, const char* filename) {
    int pokemonCount = size(ph);

    std::ifstream file(ph.nameFile, std::ios::binary);

    if (!file.is_open()) {
        return;
    }

    std::ofstream writeFile(filename);

    if (!writeFile.is_open()) {
        return;
    }

    while (pokemonCount) {
        Pokemon pokemon = createPokemonFromBinary(file);
        writeFile << pokemon.name << " " << getTypeStr(pokemon.type) << " " << pokemon.power << "\n";
        pokemonCount--;
    }

    file.close();
    writeFile.close();
}

void untextify(const PokemonHandler& ph, const char* filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        return;
    }

    std::ofstream binaryFile(ph.nameFile, std::ios::binary);

    if (!binaryFile.is_open()) {
        file.close();
        return;
    }

    Pokemon pokemon;

    while (file >> pokemon.name >> (int&)pokemon.type >> pokemon.power) {
        writePokemon(ph.nameFile, pokemon);
    }

    file.close();
    binaryFile.close();
}

int main()
{
    
}