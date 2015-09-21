#include <iostream>
#include <unistd.h>    //execl
#include <sys/types.h> //mode_t
#include <sys/stat.h>  //mode_t mkfifo
#include <iomanip>     //std::localtime

int main(int argc, char *argv[]) {
	std::time_t time = std::time(nullptr);
	std::cout << "Client: PID " << getpid() <<  " - "
					<< std::put_time(std::localtime(&time),"%F_%T") << '\n';
	
	if(mkfifo("ctos", S_IRUSR | S_IWUSR) < 0) {
		std::cout << "Failed\n";	
	}
	
	pid_t pid = fork();
	if(pid == 0){
		std::cout << pid << " Child Process " << getpid() << '\n';
		execl("Server",NULL);
		std::cout << "After Exec\n";
	}
	
	
	
	std::cout << pid << " Goodbye Client " << getpid() << '\n';
}