#include <iostream>
#include <cstring>
#include <fstream>
#pragma warning (disable: 4996)

struct User {
	char name[25];
};

struct Message {
	User from;
	char* text = nullptr;
};


User createUser(const char* name) {
	User u;
	strcpy(u.name, name);
	return u;
}

Message createMessage(const User& u, const char* str) {
	Message m;
	m.text = new char[strlen(str) + 1];
	strcpy(m.text, str);

	m.from = u;

	return m;
}

void serializeMessage(std::ofstream& ofs, const Message& m) {
	ofs.write((const char*)&m.from, sizeof(User));

	int size = strlen(m.text);
	ofs.write((const char*)&size, sizeof(size));
	ofs.write(m.text, size);
}

Message deserializeMessage(std::ifstream& ifs) {
	Message m;

	ifs.read((char*)&m.from, sizeof(User));
	int size = 0;
	ifs.read((char*)&size, sizeof(size));

	m.text = new char[size + 1];
	ifs.read(m.text, size);

	return m;
}

void freeMessage(Message& m) {
	delete[] m.text;

}

void printMessage(const Message& m) {
	std::cout << m.from.name << ": " << m.text << std::endl;
}

void printChat(const char* filePath) {
	std::ifstream ifs(filePath, std::ios::binary);

	if (!ifs.is_open()) {
		return;
	}

	while (true) {
		Message m = deserializeMessage(ifs);

		if (ifs.eof()) {
			break;
		}

		printMessage(m);
	}

	ifs.close();
}

int main() {


}
