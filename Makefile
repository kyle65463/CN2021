server: src/server.cpp
	g++ -std=c++11 src/server.cpp -o server

client: src/client.cpp
	g++ -std=c++11 src/client.cpp -o client