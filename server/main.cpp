#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

void ErrorHandling(string s)
{
    cout << s << endl;
}


#include <iostream>

int main(int, char**) {
    int server_sock;
    int client_sock;

    sockaddr_in server_addr;
    sockaddr_in client_addr;

    socklen_t client_addr_size;

    string messages = "Hello world!";

    // 如何求指针数组长度
    

}
