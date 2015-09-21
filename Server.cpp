#include <iostream>
#define fifo "/home/justijk/ctos"
int main() {
	open(fifo, O_RDONLY);
	
	/*if(mkfifo(fifo, 0666) < 0) {
		return 1;
	}
	
	int fifo_int = open(fifo, O_RDONLY);
	if(fifo_int < 0) {
		return 2;
	}
	
	char temp[32];
	if(read(fifo_int, temp, sizeof(temp)) < 0) {
		return 3;
	}
	*/
	
}