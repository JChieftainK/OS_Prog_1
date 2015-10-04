/*
*	Justin Kennedy
*	OS 4323
*	Programming Homework ONE
*	Using Named Pipes
*/
#include <iostream>
#include <fcntl.h>
#include <unistd.h>    //execl fork read write
#include <cstring>     //strcmp
#include <fstream>     //std::ifstream
#include <queue>       //std::queue
#include <sstream>     //std::istringstream
#include <algorithm>   //std::remove erase transform

const std::string CONFIRMATION = "Confirmed";

void read_confirmation(int);
int read_handshake(int);
std::string read_client(int);
int write_client(int, const char*);

int main(int argc, char *argv[]) {
	int s_pid = getpid();
	time_t rawtime;
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
	
	//Read target file from client
	std::string file_target = read_client(rd);

	//Send confirmation
	write_client(wr, CONFIRMATION.c_str());
	
	//Read target from client
	std::string target = read_client(rd);
	
	//Send confirmation
	write_client(wr, CONFIRMATION.c_str());
	
	//Open target file
	std::ifstream in(file_target.c_str(), std::ios_base::in);
	if(in) {					//File has been opened
		std::string str;
		std::queue<std::string> sq; //sq == string_queue
		while(std::getline(in,str)) { //Fill queue line by line
			sq.push(str);
		}
		in.close();
		
		int counter = 0;
		int total = 0;
		int line = 1;
		std::istringstream istr;
		std::ostringstream ostr;
		std::transform(target.begin(), target.end(), target.begin(), ::tolower);
		
		while(!sq.empty()) { //Go through entire file line by line
			istr.str(sq.front()); //set istringstream with line from queue
			sq.pop(); //Remove line from queue
			
			while(istr.peek() != EOF){ //Go through istringstream until empty
				istr >> str;
				//Convert string into lowercase
				std::transform(str.begin(), str.end(), str.begin(), ::tolower);
				//Remove different/common characters from the string
				str.erase(std::remove(str.begin(), str.end(), '>'), str.end());
				str.erase(std::remove(str.begin(), str.end(), '<'), str.end());
				str.erase(std::remove(str.begin(), str.end(), '.'), str.end());
				str.erase(std::remove(str.begin(), str.end(), '\''), str.end());
				str.erase(std::remove(str.begin(), str.end(), '"'), str.end());
				str.erase(std::remove(str.begin(), str.end(), ','), str.end());
				//Compare the two strings and if equal increment counter
				if(str.compare(target) == 0) {
					++counter;
				}
			}
			istr.clear();
			if(counter > 0) {
				ostr.str("");
				ostr << "Target >>" << target << "<< Appeared on Line "<< line 
									<< ",\t" << counter << " Times";
				write_client(wr, (ostr.str()).c_str()); //Write to Client
				read_confirmation(rd); //Read confirmation
			}
			++line;
			total += counter;
			counter = 0;
		}
		ostr.str("");
		ostr << "Target >>" << target << "<< in File >>" << file_target 
							<< "<< Appeared a Total of " << total << " Times.";
		write_client(wr, (ostr.str()).c_str());
		read_confirmation(rd);
	}else {	 //Error opening file
		std::cout << "Server: PID " << s_pid << " - DID NOT OPEN FILE: '" 
							<< file_target << "'\n";
	}
	std::string finish = "Server-EOF";
	write_client(wr, finish.c_str());
	
	//Close pipes
	close(rd);
	close(wr);
	
	time (&rawtime);
	std::cout << "Server: PID " << s_pid 
					<< " - Terminated on "<< ctime(&rawtime);
	return 0;
}

//Read confirmation from server
void read_confirmation(int read_from) {
	char * buffer = new char[1024];
	int rd_status = read(read_from, buffer, 1024);
	if(rd_status < 0) {
		std::cout << "Server: FAILURE TO READ CONFIRMATION\n";
	}else {
		if(strcmp(buffer, "Confirmed") != 0) {
			std::cout << "Server: CONFIRMATION FAILED\n";
		}
	}
	delete[] buffer;	
}

//Read from client and return what is read
std::string read_client(int read_from) {
	char * buffer = new char[1024];
	int rd_status = 0;
	//do{
		rd_status = read(read_from, buffer, 1024);
	//}while(rd_status == 0);
	std::string result;
	if(rd_status < 0) {
		//Failure to read
		std::cout << "Server: FAILURE TO READ\n";
	}else {
		result = buffer;
	}
	delete[] buffer;
	return result;
}

//Read handshake from client and confirm
int read_handshake(int read_from) {
	std::string handshake = read_client(read_from);
	if(handshake.compare("Head nod and handshake") == 0) {
		std::cout << "Server: PID " << getpid()
							<< " - Synchronized to Client.\n";
	}else {
		std::cout << "Server: PID " << getpid()
							<< " - FAILURE TO SYNCHRONIZE\n";
	}
	return 0;
}

//Write to client given char array
int write_client(int write_to, const char* buffer) {
	int wr_status = write(write_to, buffer, sizeof(buffer) * 8);
	return 0;
}