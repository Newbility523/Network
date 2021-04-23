#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>

#define BUFFER_SIZE 1024
#define OPSZ 4
#define RESULT_SIZE 4
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
    int result = 0;
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

    int operandCount = 0;

    cout << "input operand num:";
    cin >> operandCount;

    // 头字节   操作数量 int
    // 中段     int 操作 N 个
    // 尾字节   操作符 char
    unsigned char* opmsg = new unsigned char[operandCount * OPSZ + 2];

    opmsg[0] = operandCount;

    int temp;
    for (int i = 0; i < operandCount; ++i)
    {
        cout << "input num." << i + 1 << ": ";
        cin >> temp;
        *(int*)(opmsg + i * OPSZ + 1) = temp;
    }

    char operation;
    cout << "operation: ";
    cin >> operation;
    opmsg[operation * OPSZ + 1];

    write(sock, opmsg, operandCount * OPSZ + 2);
    read(sock, &result, OPSZ);

    cout << "Get result from server: " << result << endl;
    close(sock);

    delete[] opmsg;

    return 0;
}
