/*
*	Justin Kennedy
*	OS 4323
*	Programming Homework ONE
*	Using Named Pipes
*/
#include <iostream>
#include <sys/stat.h>  //S_IRUSR S_IWUSR mkfifo
#include <stdio.h>     //remove
#include <fcntl.h>     //O_WRONLY O_RDONLY
#include <unistd.h>    //execl fork read write
#include <cstring>     //strcmp

const std::string CONFIRMATION = "Confirmed";

void read_confirmation(int);
int read_handshake(int);
int read_server(int);
int write_server(int, const char*);

int main(int argc, char *argv[]) {
	int c_pid = getpid();
	time_t rawtime;
	time (&rawtime);
	std::cout << "Client: PID " << c_pid 
						<< " - Running on "<< ctime(&rawtime);
	
	//Enter file name
	std::cout << "Client: PID " << c_pid
						<< " - Enter File Name:\n";
	std::string file_string;
	getline(std::cin,file_string);
	
	//Enter target
	std::cout << "Client: PID " << c_pid
						<< " - Enter Target:\n";
	std::string target_string;
	getline(std::cin, target_string);
					
	//Display file name and target
	std::cout << "Client: PID " << c_pid << " - Input File >>>" 
						<< file_string << "<<<\n";
	std::cout << "Client: PID " << c_pid << " - Target >>>"
						<< target_string << "<<<\n";
	
	//Make the Named Pipes
	//ctos = client to server
	//stoc = server to client
	mkfifo("ctos", S_IRUSR | S_IWUSR);
	mkfifo("stoc", S_IRUSR | S_IWUSR);
	
	//Create copy of process
	pid_t pid = fork();
	if(pid == 0){
		//Sacrifice copy to start new process in its place
		execl("Server", NULL);
	}
	
	//Open pipe to write to
	int wr = open("ctos", O_WRONLY);
	//Write handshake to server 
	std::string handshake = "Head nod and handshake";
	write_server(wr, handshake.c_str());
	
	//Open pipe to read from server
	int rd = open("stoc", O_RDONLY);
	//Read handshake from server
	read_handshake(rd);
	
	//Write file target to server
	write_server(wr, file_string.c_str());
	
	//Read confirmation
	read_confirmation(rd);
	
	//Write target to server
	write_server(wr, target_string.c_str());
	
	//Read confirmation
	read_confirmation(rd);
	
	while(read_server(rd) != 1) {
		//Send confirmation
		write_server(wr, CONFIRMATION.c_str());
	}
	
	//Close pipes
	close(wr);
	close(rd);
	//Remove pipes
	remove("ctos");
	remove("stoc");
	
	time (&rawtime);
	std::cout << "Client: PID " << c_pid 
					<< " - Terminated on "<< ctime(&rawtime);
	return 0;
}

//Read confirmation from server
void read_confirmation(int read_from) {
	char * buffer = new char[1024];
	int rd_status = read(read_from, buffer, 1024);
	if(rd_status < 0) {
		std::cout << "Client: FAILURE TO READ CONFIRMATION\n";
	}else {
		if(strcmp(buffer, "Confirmed") != 0) {
			std::cout << "Client: CONFIRMATION FAILED\n";
		}
	}
	delete[] buffer;	
}

//Read from server and display to screen
int read_server(int read_from) {
	char * buffer = new char[1024];
	int rd_status = read(read_from, buffer, 1024);
	if(strcmp(buffer, "Server-EOF") == 0) {
		return 1;
	}else {
		std::cout << "Client: PID " << getpid()
					<< " - " << buffer << "\n";
	}
	delete[] buffer;
	return 0;
}

//Read handshake from server and confirm
int read_handshake(int read_from) {
	char * buffer = new char[1024];
	int rd_status = read(read_from, buffer, 1024);
	if(rd_status < 0) { 
		//STILL NEED TO DO
		std::cout << "Client: FAILURE TO READ HANDSHAKE\n";
	}else {
		if(strcmp(buffer, "Handshake and nod head") == 0) {
			std::cout << "Client: PID " << getpid()
								<< " - Synchronized to Server.\n";
		}else {
			std::cout << "Client: PID " << getpid()
								<< " - FAILURE TO SYNCHRONIZE\n";
		}
	}
	delete[] buffer;
	
	return 0;
}

//Write to server given char array
int write_server(int write_to, const char* buffer) {
	int wr_status = write(write_to, buffer, sizeof(buffer) * 8);
	return 0;
}