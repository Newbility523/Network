#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>

using namespace std;

void ErrorHandling(string s)
{
    cout << s << endl;
}

int main(int argc, char* argv[]) 
{
    int server_sock;
    int client_sock;

    sockaddr_in server_addr;
    sockaddr_in client_addr;

    socklen_t client_addr_size;

    string messages = "Hello world!";

    // 如何求指针数组长度

    server_sock = socket(PF_INET, SOCK_STREAM, 0);

    if (server_sock == -1)
    {
        ErrorHandling("socket() error");
    }

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));

    if (bind(server_sock, (sockaddr*) &server_addr, sizeof(server_addr)) == -1)
    {
        ErrorHandling("bind() error");
    }
    
    if (listen(server_sock, 5) == -1)
    {
        ErrorHandling("listen() error");
    }

    client_addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (sockaddr*) &client_addr, &client_addr_size);

    if (client_sock == -1)
    {
        ErrorHandling("accept() error");
    }

    char bufferMessage[] = "Helle world lalala!";
    write(client_sock, bufferMessage, sizeof(bufferMessage));
    close(client_sock);
    close(server_sock);

    return 0;
}
