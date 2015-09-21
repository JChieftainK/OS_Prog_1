#include <iostream>
#include <unistd.h>    //execl
#include <sys/types.h> //mode_t
#include <sys/stat.h>  //mode_t mkfifo
#include <iomanip>     //std::localtime
#include <fcntl.h>     //O_WRONLY O_RDONLY
#include <fstream>     //fstream

int main(int argc, char *argv[]) {
	//std::cout << "Client: PID " << getpid();
	
	mkfifo("ctos", S_IRUSR | S_IWUSR);
	mkfifo("stoc", S_IRUSR | S_IWUSR);
	
	pid_t pid = fork();
	
	if(pid == 0){
		execl("Server",NULL);
	}
	
	std::fstream ctos;
	//ctos.open("ctos");
	
	//ctos.close();
	
	std::fstream stoc;
	stoc.open("stoc");
	
	char * buffer = new char [1024];
	stoc.read(buffer,1024);
	std::cout << buffer;
	delete[] buffer;
	
	stoc.close();
	
	return 0;
}