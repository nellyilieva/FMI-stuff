#include <iostream>
#include <fstream>
#include <sstream>

size_t getFileSize(std::ifstream& ifs) {
    size_t currPos = ifs.tellg();
    ifs.seekg(0, std::ios::end);
    size_t size = ifs.tellg();
    ifs.seekg(currPos, std::ios::beg);

    return size;
}

bool isValidSymbol(unsigned char ch) {
    return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ('0' <= ch && ch <= '9');
}

class HexViewFile {
private:
    unsigned char* data;
    size_t size = 0;

public:
    HexViewFile() : data(nullptr), size(0) {}
    
    ~HexViewFile() {
        delete[] data;
        data = nullptr;
        size = 0;
    }

    void load(const char* fileName) {
        std::ifstream ifs(fileName, std::ios::binary);

        if (!ifs.is_open()) {
            return;
        }

        size_t size = getFileSize(ifs);

        data = new unsigned char[size];  //!!!!!!!

        ifs.read((char*)data, size);

        ifs.close();
    }

    void save(const char* fileName) const{
        std::ofstream ofs(fileName, std::ios::binary);

        if (!ofs.is_open()) {
            return;
        }

        ofs.write((const char*)data, size);

        ofs.close();
    }
    
    void print() const {
        for (size_t i = 0; i < size; i++) {
            if (isValidSymbol(data[i])) {
                std::cout << data[i] << " ";
            }
            else {
                std::cout << ".. ";
            }
        }
        std::cout << std::endl;

    }

    void modify(unsigned idx, char ch) {
        if (idx < size) {
            data[idx] = ch;
        }
    }

    size_t getSize() const {
        return size;
    }

    const unsigned char* getData() const {
        return data;
    }
};

int main()
{
    
}

