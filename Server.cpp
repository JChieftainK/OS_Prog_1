#include <iostream>
#include <fcntl.h>
#include <fstream>
#include <time.h>
#include <unistd.h>

int main() {
	time_t rawtime;
	time (&rawtime);
	std::cout << "Server: PID " << getpid() 
					<< " - Running on "<< ctime(&rawtime);
	
	std::ofstream stoc ("stoc", std::ofstream::out);
	std::ifstream ctos ("ctos", std::ifstream::in);
	
	char * buffer = new char [1024];
	ctos.getline(buffer, 1024);
	
	std::string something = "SWrite";
	stoc.write(something.c_str(), 1024);
	delete[] buffer;
	
	ctos.close();
	stoc.close();
	
	return 0;
}