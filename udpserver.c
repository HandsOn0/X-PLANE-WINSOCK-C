//#include "stdafx.h"
#include<stdio.h>
#include <WinSock2.h>
#include <Windows.h>


#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996) 
int main(int argc, char* argv[])
{
    int n =6; // number of outputs selected on X-plane output data setting
    WSADATA wsd; // initialization information
    SOCKET soRecv; //Receive SOCKET
    int nRet = 0;
    //int i = 0;
    int dwSendSize = 0;
    SOCKADDR_IN siRemote, siLocal; //Remote sender address and local receiver address

    // Start Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {
        printf("WSAStartup Error = %d\n", WSAGetLastError());
        return 1;
    }

    // Create a socket
    soRecv = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (soRecv == SOCKET_ERROR) {
        printf("WSAStartup Error = %d\n", WSAGetLastError());
        return 1;
    }

    // Set the port number
    int nPort = 49003;

    //int nPort = 1234;
    siLocal.sin_family = AF_INET;
    siLocal.sin_port = htons(nPort);
    siLocal.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind the local address to the socket
    if (bind(soRecv, (SOCKADDR*)&siLocal, sizeof(siLocal)) == SOCKET_ERROR) {
        printf("BIND Error = %d\n", WSAGetLastError());
        return 1;
    }

    // Apply for memory
   char *Recv=malloc (5+n*36);
   dwSendSize = sizeof(siRemote);
   
    // Start accepting data
    nRet = recvfrom(soRecv, Recv, 5+n*36, 0, (SOCKADDR*)&siRemote, &dwSendSize);
    printf("dwSendSize=%d\n", dwSendSize);

    if (nRet == SOCKET_ERROR) {
        printf("recvfrom Error = %d\n", WSAGetLastError());

    }
   
   float **Data_in=(float **)malloc(n*sizeof(float*));
   for (int i = 0; i < n; i++) Data_in[i] = (float *)malloc(8 * sizeof(float));

    for (int i = 0; i < n; i++) {
        for (int j = 1; j < 9; j++) {

   
            memcpy(Data_in[i]+j-1, Recv + 5+i*36+j*4, sizeof(float));
            
            printf("%.2f\t",Data_in[i][j-1]);

        }
        printf("\n\n");
            }
    
    closesocket(soRecv);
    WSACleanup();
    system("pause");
    return 0;
}