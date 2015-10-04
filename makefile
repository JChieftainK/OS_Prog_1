#Justin Kennedy
#OS 4323
default: cli Server

cli: Client.cpp
	g++ Client.cpp -o cli

Server: Server.cpp
	g++ Server.cpp -o Server
	
clean:
	rm cli
	rm Server