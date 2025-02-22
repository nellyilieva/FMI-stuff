#include <iostream>
#include <cstring>
#include <fstream>

enum class Color {
    White,
    Green,
    Red,
    Unknown
};

Color stringToColor(const char* colorStr) {
    if (strcmp(colorStr, "White") == 0) {
        return Color::White;
    }
    else if (strcmp(colorStr, "Green") == 0) {
        return Color::Green;
    }
    else if (strcmp(colorStr, "Red") == 0) {
        return Color::Red;
    }
    else {
        return Color::Unknown;
    }
}

class Baloon {
private:
    int price;
    Color color;

public:
    Baloon() : price(0), color(Color :: Unknown) {}

    Baloon(int initPrice, Color initColor) {
        price = initPrice;
        color = initColor;
    }

    //Baloon(int price, Color color) : price(price), color(color) {}

    int getPrice() const{
        return price;
    }

    Color getColor() const{
        return color;
    }

    void setPrice(int price) {
        this->price = price;
    }

    void setColor(Color color) {
        this->color = color;
    }
};

enum class Taste {
    Blueberry,
    Queen,
    Mango,
    Strawberry,
    Apple,
    Unknown
};

class Narga {
private:
    int price;
    char brand[1024];
    Taste taste;

    Taste getTasteFromNum(int n) {
        switch (n) {
        case 0:
            return Taste::Blueberry;
        case 1:
            return Taste::Queen;
        case 2:
            return Taste::Mango;
        case 3:
            return Taste::Strawberry;
        case 4:
            return Taste::Apple;
        default:
            return Taste::Unknown;
        }
    }

    const char* tasteToString(Taste taste) const {
        switch (taste) {
        case Taste::Blueberry:
            return "Blueberry";
        case Taste::Queen:
            return "Queen";
        case Taste::Mango:
            return "Mango";
        case Taste::Strawberry:
            return "Strawberry";
        case Taste::Apple:
            return "Apple";
        default:
            return "Unknown";
        }
    }
public:
    void readFromInput() {
        std::cin >> price;
        std::cin.ignore();
        std::cin.getline(brand, 1024);

        int tasteNum;
        std::cin >> tasteNum;

        taste = getTasteFromNum(tasteNum);
    }

    void print() const{
        std::cout << price << " " << brand << " " << tasteToString(taste) << "\n";
    }

    Narga() : price(0), brand(""),  taste(Taste::Unknown) {}

    Narga(int price, const char* brand, Taste taste) : price(price), taste(taste) { strcpy(this->brand, brand); }

    Narga(int price, const char* brand): price(price) { strcpy(this->brand, brand); }

    int getPrice() const {
        return price;
    }

    const char* getBrand() const {
        return brand;
    }

    Taste getTaste() const {
        return taste;
    }

    void setPrice(int price) {
        this->price = price;
    }

    void setBrand(const char* brand) {
        strcpy(this->brand, brand);
    }

    void setTaste(Taste taste) {
        this->taste = taste;
    }
};

const int MAX_LENGTH = 128;

class Alchohol {
private:
    char name[MAX_LENGTH];
    double price;
public:
    Alchohol() : name(""), price(0) {}

    Alchohol(const char* name, double price) : price(price) { strcpy(this->name, name); }

    const char* getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    void setName(const char* name) {
        strcpy(this->name, name);
    }

    void setPrice(int price) {
        this->price = price;
    }
};


class NightClub {
private:
    Baloon baloons[1024];
    unsigned int countBallon = 0;

    Alchohol alchohols[512];
    unsigned int countAlchohol = 0;

    Narga nargas[256];
    unsigned int countNarga = 0;

    int parseCount(const char* str) const {
        int result = 0;
        for (int i = 0; str[i] != '\0'; ++i) {
            result = result * 10 + (str[i] - '0');
        }
        return result;
    }

public:
    bool hasBaloon(Color color) const {
        for (int i = 0; i < countBallon; i++) {
            if (baloons[i].getColor() == color) {
                return true;
            }
        }
        return false;
    }

    bool hasAlchohol(const char* name) const {
        for (int i = 0; i < countAlchohol; i++) {
            if (strcmp(alchohols[i].getName(), name) == 0) {
                return true;
            }
        }

        return false;
    }

    bool hasNarga(Taste taste) const {
        for (int i = 0; i < countAlchohol; i++) {
            if (nargas[i].getTaste() == taste) {
                return true;
            }
        }

        return false;
    }

    void addBaloon(const char* fileName) {
        std::ifstream file(fileName);

        if (!file.is_open()) {
            return;
        }

        Color color;
        int price = 0;

        char colorStr[20];

        while (file.getline(colorStr, 20, '-')) {
            Color color = stringToColor(colorStr);

            file >> price;
            file.ignore();

            Baloon b(price, color);
            baloons[countBallon++] = b;
        }

        file.close();
    }

    void addNarga(const char* fileName) {
        std::ifstream file(fileName);

        if (!file.is_open()) {
            return;
        }

        char buffer[1024];
        while (file.getline(buffer, 1024)) {
            char brand[128];
            int price = 0;

            int i = 0;
            while (buffer[i] != '-' && buffer[i] != '\0' && i < 1023) {
                brand[i] = buffer[i];
                i++;
            }
            brand[i] = '\0';

            if (buffer[i] == '-')
                i++;

            price = (int)(&buffer[i]);

            Narga n(price, brand);
            nargas[countNarga++] = n;
        }

        file.close();
    }

    void addAlchohol(const char* fileName) {
        std::ifstream file(fileName);

        if (!file.is_open()) {
            return;
        }

        char* name;
        int price = 0;

        char name[128];

        while (file.getline(name, 128, '-')) {
            file >> price;
            file.ignore();

            Alchohol a(name, price);
            alchohols[countAlchohol++] = a;
        }

        file.close();
    }

    void removeBaloon(Color color) {
        int idx = 0;

        for (int i = 0; i < countBallon; i++) {
            if (baloons[i].getColor() != color) {
                if (i != idx) {
                    baloons[idx] = baloons[i];
                }
                idx++;
            }
        }
        countBallon = idx;
    }

    void removeAlchohol(const char* name) {
        int idx = 0;

        for (int i = 0; i < countAlchohol; i++) {
            if (strcmp(alchohols[i].getName(), name) != 0) {
                if (i != idx) {
                    alchohols[idx] = alchohols[i];
                }

                idx++;
            }
        }
        countAlchohol = idx;
    }

    void removeNarga(const char* brand, Taste taste) {
        int idx = 0;

        for (int i = 0; i < countNarga; i++) {
            if (strcmp(nargas[i].getBrand(), brand) != 0 && nargas[i].getTaste() != taste) {
                if (i != idx) {
                    nargas[idx] = nargas[i];
                }

                idx++;
            }
        }
        countNarga = idx;
    }

    double returnCheck(const char* fileName) {
        std::ifstream file(fileName);

        if (!file.is_open()) {
            return;
        }

        double totalAmount = 0.0;
        char line[1024];

        // Process Alchohols section
        while (file.getline(line, 1024) && strcmp(line, "Baloons:") != 0) {
            if (strcmp(line, "Alchohols:") == 0 || line[0] == '\0') continue;

            char name[128];
            int count = 0;

            int idx = 0;
            while (line[idx] != '-' && line[idx] != '\0') {
                name[idx] = line[idx];
                idx++;
            }
            name[idx] = '\0';
            count = parseCount(line + idx + 1);

            for (int i = 0; i < countAlchohol; i++) {
                if (strcmp(alchohols[i].getName(), name) == 0) {
                    totalAmount += alchohols[i].getPrice() * count;
                    break;
                }
            }
        }

        // Process Baloons section
        while (file.getline(line, 1024) && strcmp(line, "Nargas:") != 0) {
            if (strcmp(line, "Baloons:") == 0 || line[0] == '\0') continue;

            char colorStr[20];
            int count = 0;

            int idx = 0;
            while (line[idx] != '-' && line[idx] != '\0') {
                colorStr[idx] = line[idx];
                idx++;
            }
            colorStr[idx] = '\0';
            count = parseCount(line + idx + 1);

            Color color = stringToColor(colorStr);
            for (int i = 0; i < countBallon; i++) {
                if (baloons[i].getColor() == color) {
                    totalAmount += baloons[i].getPrice() * count;
                    break;
                }
            }
        }

        // Process Nargas section
        while (file.getline(line, 1024)) {
            if (strcmp(line, "Nargas:") == 0 || line[0] == '\0') continue;

            char brand[128];
            char tasteStr[20];
            int count = 0;

            int idx = 0;
            while (line[idx] != '-' && line[idx] != '\0') {
                brand[idx] = line[idx];
                idx++;
            }
            brand[idx] = '\0';

            int startTasteIdx = idx + 1;
            idx = startTasteIdx;
            while (line[idx] != '-' && line[idx] != '\0') {
                tasteStr[idx - startTasteIdx] = line[idx];
                idx++;
            }
            tasteStr[idx - startTasteIdx] = '\0';
            count = parseCount(line + idx + 1);

            Taste taste = Taste::Unknown;
            if (strcmp(tasteStr, "Blueberry") == 0) taste = Taste::Blueberry;
            else if (strcmp(tasteStr, "Queen") == 0) taste = Taste::Queen;
            else if (strcmp(tasteStr, "Mango") == 0) taste = Taste::Mango;
            else if (strcmp(tasteStr, "Strawberry") == 0) taste = Taste::Strawberry;
            else if (strcmp(tasteStr, "Apple") == 0) taste = Taste::Apple;

            for (int i = 0; i < countNarga; i++) {
                if (strcmp(nargas[i].getBrand(), brand) == 0 && nargas[i].getTaste() == taste) {
                    totalAmount += nargas[i].getPrice() * count;
                    break;
                }
            }
        }

        file.close();
        return totalAmount;
    }
};

struct Client {
private:
    char* name;
    char nameFile[50 + 1];
public:
    const char* getName() const {
        return name;
    }

    Client(const char* clientName) : name(nullptr) {
        name = new char[strlen(clientName) + 1];
        strcpy(name, clientName);
    }

    ~Client() {
        delete[] name;
    }

    double calculateProfit(NightClub& club) const {
        double totalProfit = club.returnCheck(nameFile);
        return totalProfit;
    }
    
    void storeProfit(const Client* clients, int countClients, NightClub& club) {
        std::ofstream ofs("money.dat", std::ios::binary);

        if (!ofs.is_open()) {
            return;
        }

        for (int i = 0; i < countClients; i++) {
            double profit = clients[i].calculateProfit(club);
            ofs.write((const char*)(&clients[i]), sizeof(Client));
            ofs.write((const char*)(&profit), sizeof(double));
        }

        ofs.close();
    }
};