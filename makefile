default:
	g++ Client.cpp -o cli
	g++ Server.cpp -o Server

clean:
	rm cli
	rm Server