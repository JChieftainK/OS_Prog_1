#include <iostream>
#include <fcntl.h>
#include <unistd.h>    //execl fork read write
#include <cstring>     //strcmp

int read_handshake(int);
void read_client(int);
int write_client(int, const char*);

int main(int argc, char *argv[]) {
	time_t rawtime;
	int s_pid = getpid();
	time (&rawtime);
	std::cout << "Server: PID " << s_pid 
						<< " - Running on "<< ctime(&rawtime);
	
	//Open pipe to read from
	int rd = open("ctos", O_RDONLY);
	
	//Read from client
	read_handshake(rd);
	
	//Open pipe to write to
	int wr = open("stoc", O_WRONLY);
	
	//Write handshake to client
	std::string handshake = "Handshake and nod head";
	write_client(wr,handshake.c_str());
	
	//Read from
	read_client(rd);
	
	//Close pipes
	close(rd);
	close(wr);
	
	return 0;
}

//Read from client
void read_client(int read_from) {
	char * buffer = new char[1024];
	int rd_status = read(read_from, buffer, 1024);
	std::cout << "Server: '" << buffer << "'\n";
	delete[] buffer;
}

//Read handshake from client and confirm
int read_handshake(int read_from) {
	char * buffer = new char[1024];
	int rd_status = read(read_from, buffer, 1024);
	if(rd_status < 0) { 
		//STILL NEED TO DO
	}else {
		if(strcmp(buffer, "Head nod and handshake") == 0) {
			std::cout << "Server: PID " << getpid()
								<< " - Synchronized to Client.\n";
		}else {
			std::cout << "Server: PID " << getpid()
								<< " - FAILURE TO SYNCHRONIZE\n";
		}
	}
	delete[] buffer;
	
	return 0;
}

//Write to client given char array
int write_client(int write_to, const char* buffer) {
	int wr_status = write(write_to, buffer, sizeof(buffer) * 8);
	return 0;
}