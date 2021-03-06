#include <iostream>
#include <sys/socket.h>
#define FILE_BUF_SIZE 1024
#define HEADER_SIZE 16 // Use a string with `HEADER_SIZE` chars indicates a file's length
using namespace std;

class Connection
{
public:
    Connection(int fd) : fd(fd) {}

    void sendMessage(const string &msg, int size = -1)
    {
        if (size < 0)
            size = msg.size() + 1;
        send(fd, msg.c_str(), size, 0);
    }

    string recvMessage(int size = -1)
    {
        char buf[256] = {};
        if (size < 0)
            size = sizeof(buf);
        int ret = recv(fd, buf, size, 0);

        // Check if the connection is down
        if (ret <= 0)
        {
            isDisconnected = true;
            closeConnection();
        }
        return string(buf);
    }

    bool sendFile(const string &filename)
    {
        // Open the file and
        FILE *fp = fopen(filename.c_str(), "rb");
        if (!fp)
        {
            sendMessage("-1", HEADER_SIZE); // Indicates no sending file
            return true;
        }

        // Read length and send the file's length as header
        fseek(fp, 0L, SEEK_END);
        int filelen = ftell(fp);
        fseek(fp, 0L, SEEK_SET);
        sendMessage(to_string(filelen), HEADER_SIZE);

        // Read and send the file
        char buffer[FILE_BUF_SIZE];
        int bytesRead;
        while (!feof(fp))
        {
            if ((bytesRead = fread(&buffer, 1, FILE_BUF_SIZE, fp)) > 0)
                send(fd, buffer, bytesRead, 0);
            else
                break;
        }
        fclose(fp);
        return false;
    }

    bool recvFile(const string &outname)
    {
        // Receive header (file length) first
        int length = stoi(recvMessage(HEADER_SIZE));
        if (length < 0)
            return true; // Client put a non-existing file

        // Recieve the file
        FILE *fp = fopen(outname.c_str(), "wb");
        char buffer[FILE_BUF_SIZE];
        int bytesRead;
        while (length > 0)
        {
            bytesRead = recv(fd, buffer, min(length, int(sizeof(buffer))), 0);
            length -= bytesRead;
            fwrite(&buffer, 1, bytesRead, fp);
        }
        fclose(fp);
        return false;
    }

    void login(const string &username)
    {
        this->username = username;
        isLoggedIn = true;
    }

    void closeConnection()
    {
        close(fd);
    }

    // Getters
    int getFd() { return fd; }
    bool getIsDisconnected() { return isDisconnected; }
    bool getIsLoggedIn() { return isLoggedIn; }
    const string &getUsername() { return username; }

private:
    int fd;
    bool isDisconnected = false;
    bool isLoggedIn = false;
    string username = "";
};