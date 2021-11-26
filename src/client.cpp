#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 2) {
        cout << "usage: ./server <ip:port>" << endl;
        return 0;
    }
    string portip = argv[1];
    cout << "hi " << portip << endl;
}