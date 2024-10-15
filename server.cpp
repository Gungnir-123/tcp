#include "InitSock.h"
#include <stdio.h>
#include <string.h>
CInitSock initSock;

int main() {
    // 1. Create a Listen Socket
    SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sListen == INVALID_SOCKET) {
        printf("Error: Failed to create a listen socket.\n");
        return 0;
    }
    // 2. Bind the socket to a specific port
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(4567); // 1024 - 65535
    sin.sin_addr.S_un.S_addr = INADDR_ANY;
    if(bind(sListen, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR) {
        printf("Error: Failed to bind the socket.\n");
        return 0;
    }
    // 3. Listen for incoming connections
    if(listen(sListen, 2) == SOCKET_ERROR) {
        printf("Error: Failed to listen for incoming connections.\n");
        return 0;
    }
    // 4. Accept incoming connections
    sockaddr_in remoteAddr;
    int nAddrLen = sizeof(remoteAddr);
    SOCKET sClient;
    sClient = accept(sListen, (LPSOCKADDR)&remoteAddr, &nAddrLen);
    if(sClient == INVALID_SOCKET) {
        printf("Error: Failed to accept incoming connection.\n");
        return 0;
    }

    char recv_buffer[1024];

    while(TRUE) {
        int nRecv = recv(sClient, recv_buffer, 1024, 0);
        if(nRecv > 0) {
            recv_buffer[nRecv] = '\0';
            printf("Received message: \"%s\" from %s:%d.\n", recv_buffer, inet_ntoa(remoteAddr.sin_addr), ntohs(remoteAddr.sin_port));
            send(sClient, recv_buffer, strlen(recv_buffer), 0);
        }
    }
    closesocket(sListen);
    return 0;
}