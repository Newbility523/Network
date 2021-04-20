#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>

#define BUFFER_SIZE 1024

using namespace std;

void ErrorHandling(string s)
{
    cout << s << endl;
    exit(1);
}

int main(int argc, char* argv[]) 
{
    int sock;
    sockaddr_in server_addr;
    char message[30];
    int str_len = 0;

    if (argc != 3)
    {
        printf("Usage: %s <IP><port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    // if (sock == -1)
    // {
    //     ErrorHandling("socket() error");
    // }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;

    // 127.0.0.1 9190
    // server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // server_addr.sin_port = htons(atoi("9190"));

    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (sockaddr*) &server_addr, sizeof(server_addr)) == -1)
    {
        ErrorHandling("connect() error!");
    }
    else
    {
        cout << "connect success" << endl;
    }

    int read_len = 0;
    int index = 0;

    int sendLen = 0;
    int recvCount = 0;

    while (true)
    {
        fputs("input message(Q to quit):", stdout);
        fgets(message, BUFFER_SIZE, stdin);

        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
        {
            break;
        }

        sendLen = write(sock, message, strlen(message));
        while (read_len < sendLen)
        {
            recvCount = read(sock, &message[read_len], BUFFER_SIZE - 1);
            if (recvCount == -1)
            {
                ErrorHandling("read() error!");
            }
            else
            {
                read_len += recvCount;
            }
        }

        message[read_len] = 0;

        printf("Get Message from server : %s", message);
    }

    close(sock);

    return 0;
}
