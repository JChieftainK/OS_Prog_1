#include <iostream>
#include <unistd.h>    //execl
#include <sys/stat.h>  //S_IRUSR S_IWUSR mkfifo
#include <fstream>     //fstream
#include <time.h>

int main(int argc, char *argv[]) {
	time_t rawtime;
	int c_pid = getpid();
	time (&rawtime);
	std::cout << "Client: PID " << c_pid 
					<< " - Running on "<< ctime(&rawtime);
	//Enter file name
	std::cout << "\nClient: PID " << c_pid
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
	
	//Fork the current process
	//Use child process as sacrifice
	pid_t pid = fork();
	if(pid == 0){
		//Sacrifice child process to start server
		execl("Server", NULL);
	}
	
	//Create objects to manipulate files
	std::ifstream stoc ("stoc", std::ifstream::in);
	std::ofstream ctos ("ctos", std::ifstream::out);
	
	//Synchronize
	ctos.write("We good", 1024);

	char * buffer = new char [1024];
	stoc.read(buffer, 1024);
	std::cout << "'" << buffer << "'\n";
	
	//Tell server file to read
	//Tell server phrase to search for
	//Read in server
	//Display results from server
	//Terminate Client and Server
	delete[] buffer;
	
	stoc.close();
	ctos.close();
	
	return 0;
}