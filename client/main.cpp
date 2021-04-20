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

    int read_len = 0;
    int index = 0;
    while (read_len = read(sock, &message[index++], 1))
    {
        if (read_len == -1)
        {
            ErrorHandling("read() error");
            return -1;
        }

        str_len += read_len;
    }

    printf("Message from server: %s \n", message);
    printf("count: %d \n", str_len);
    close(sock);

    return 0;
}
