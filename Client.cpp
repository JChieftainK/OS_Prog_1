#include <iostream>
#include <unistd.h>    //execl
#include <sys/stat.h>  //S_IRUSR S_IWUSR mkfifo
#include <fstream>     //fstream

int main(int argc, char *argv[]) {
	//std::cout << "Client: PID " << getpid();
	
	mkfifo("ctos", S_IRUSR | S_IWUSR);
	mkfifo("stoc", S_IRUSR | S_IWUSR);
	
	pid_t pid = fork();
	if(pid == 0){
		execl("Server", NULL);
	}
	
	std::ifstream stoc ("stoc", std::ifstream::in);
	std::ofstream ctos ("ctos", std::ifstream::out);
	
	ctos.write("CWrite", 1024);
	std::cout << "Wrote\n";
	char * buffer = new char [1024];
	stoc.read(buffer,1024);
	std::cout << "Write\n";
	std::cout << "'" << buffer << "'\n";
	delete[] buffer;
	
	stoc.close();
	ctos.close();
	
	return 0;
}