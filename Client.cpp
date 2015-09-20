#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
	std::cout << "Hello Client\n";
	execl("Server",NULL);
	std::cout << "Goodbye Client\n";
}