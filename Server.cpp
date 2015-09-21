#include <iostream>
#include <fcntl.h>
#include <fstream>

int main() {
	std::fstream ctos;
	std::fstream stoc;
	
	//Read from Client
	//ctos.open("ctos");
	
	
	
	//ctos.close();
	
	//Write to Client
	stoc.open("stoc");
	
	stoc.write("Hah\n", 1024);
	
	stoc.close();
	return 0;
}