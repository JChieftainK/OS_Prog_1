#include <iostream>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>

int main() {
	std::ofstream stoc ("stoc", std::ofstream::out);
	std::ifstream ctos ("ctos", std::ifstream::in);
	
	
	char * buffer = new char [1024];
	std::cout << "trying to read\n";
	ctos.getline(buffer, 1024);
	std::cout << "REad\n";
	std::string something = "SWrite";
	stoc.write(something.c_str(), 1024);
	delete[] buffer;
	
	ctos.close();
	stoc.close();
	
	return 0;
}