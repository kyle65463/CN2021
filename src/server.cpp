#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 2) {
        cout << "usage: ./server <port>" << endl;
        return 0;
    }
    int port = stoi(argv[1]);
    cout << "hi " << port << endl;
}