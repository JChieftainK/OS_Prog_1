#include <iostream>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>

int main() {
	time_t rawtime;
	int c_pid = getpid();
	time (&rawtime);
	std::cout << "Server: PID " << c_pid 
						<< " - Running on "<< ctime(&rawtime);
	
	//Receiving handshake from client
	std::ifstream ctos ("ctos", std::ifstream::in);
	if(ctos.is_open()) {
		char * buffer = new char [1024];
		ctos.getline(buffer, 1024);
		if(strcmp(buffer,"We good?") == 0) {
			std::cout << "Server: PID " << c_pid
								<< " - Synchronized to Client.\n";
		}else {
			std::cout << "Server: Failure to Synchronize\n";
			ctos.close();
			exit(1);
		}
		delete[] buffer;
	}
	ctos.close();
	
	//Sending handshake to client
	std::ofstream stoc ("stoc", std::ofstream::out);
	if(stoc.is_open()) {
		stoc.write("Yeah we good", 1024);
	}
	stoc.close();
	
	return 0;
}