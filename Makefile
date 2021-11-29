server: src/server.cpp
	g++ -std=c++17 src/server.cpp -o server

client: src/client.cpp
	g++ -std=c++17 src/client.cpp -o client