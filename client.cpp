#include "InitSock.h"
#include <stdio.h>
CInitSock initSock;

int main() {
    //
    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(s == INVALID_SOCKET) {
        printf("Error: Failed to create client socket.\n");
        return 0;
    }

    //
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(4567);
    serverAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    if(connect(s, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Error: Failed to connect to server.\n");
        return 0;
    }
    
    //
    while(TRUE) {
        char send_message[1024];
        printf("Enter message to send to server: \n");
        scanf(" %[^\n]", send_message);
        send(s, send_message, strlen(send_message), 0);


        char recv_message[1024];

        int nRecv = recv(s, recv_message, 1024, 0);
        if(nRecv > 0) {
            recv_message[nRecv] = '\0';
            printf("Received message: \"%s\" from server.\n", recv_message);
        }
        printf("\n");
    }
    closesocket(s);
    return 0;
}