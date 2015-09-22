#include <iostream>
#include <unistd.h>    //execl
#include <sys/stat.h>  //S_IRUSR S_IWUSR mkfifo
#include <fstream>     //fstream

int main(int argc, char *argv[]) {
	time_t rawtime;
	int c_pid = getpid();
	time (&rawtime);
	std::cout << "Client: PID " << c_pid 
						<< " - Running on "<< ctime(&rawtime);
	
	//Enter file name
	std::cout << "Client: PID " << c_pid
						<< " - Enter File Name:\n";
	std::string file_string;
	getline(std::cin,file_string);
	
	//Enter target
	std::cout << "\nClient: PID " << c_pid
						<< " - Enter Target:\n";
	std::string target_string;
	getline(std::cin, target_string);
					
	//Display file name and target
	std::cout << "\nClient: PID " << c_pid << " - Input File >>>" 
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
	
	//Sending handshake to server
	std::ofstream ctos ("ctos", std::ifstream::out);
	if(ctos.is_open()) {
		ctos.write("We good?", 1024);
	}
	ctos.close();
	
	//Receiving handshake from server
	std::ifstream stoc ("stoc", std::ifstream::in);
	if(stoc.is_open()) {
		char * buffer = new char [1024];
		stoc.getline(buffer, 1024);
		if(strcmp(buffer,"Yeah we good") == 0) {
			std::cout << "Client: PID " << c_pid
							<< " - Synchronized to Client.\n";
		}else {
			std::cout << "Client: Failure to Synchronize\n";
			ctos.close();
			exit(1);
		}
		delete[] buffer;
	}
	stoc.close();
	
	//Tell server file to read
	//Tell server phrase to search for
	//Read in server
	//Display results from server
	//Terminate Client and Server
	
	return 0;
}