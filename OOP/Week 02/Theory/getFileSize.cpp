#include <iostream>
#include <fstream>

size_t getFileSize(std::ifstream& ifs) {
	size_t curr = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	size_t size = ifs.tellg();
	ifs.seekg(curr, std::ios::beg);

	return size;
}

int main() {
  
}
