#include<stdio.h>
#include <WinSock2.h>
#include <Windows.h>


#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996) 
int main(int argc, char* argv[])
{
    float throttle1 = 1, throttle2 = 1, No_Comand = -999;
    char header[5] = { 68,65,84,65,0 };
    
    char commanded_throttle_index[4] = { 25,0,0,0 };
    
    float throotle_cmd[] = { throttle1,throttle2,No_Comand ,No_Comand,No_Comand ,No_Comand,No_Comand ,No_Comand };
    char datagram[41];
    int index = 0;
    memcpy(datagram, &header, sizeof(header));
    index += sizeof(header) / sizeof(char);
    
    memcpy(datagram + index, commanded_throttle_index, sizeof(commanded_throttle_index));
    index += sizeof(commanded_throttle_index) / sizeof(char);
    memcpy(datagram + index, throotle_cmd, sizeof(throotle_cmd));
    index += sizeof(throotle_cmd) / sizeof(char);
    

    
    WSADATA wsd; // initialization information
        SOCKET soSend; //Send SOCKET
    int nRet = 0;
    //int i = 0;
    int dwSendSize = 0;
    SOCKADDR_IN siLocal; //Remote sender address and local receiver address

    // Start Winsock
        if(WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {
               
            printf("WSAStartup Error = %d\n", WSAGetLastError());
        return 1;
    }

    //Create a socket

        //AF_INET protocol family: Determines the combination of ipv4 address (32-bit) and port number (16-bit)
        //SOCK_DGRAM -- UDP type, does not guarantee the order of data reception, unreliable connection;
        soSend = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (soSend == SOCKET_ERROR) {
        printf("Socket Error = %d\n", WSAGetLastError());
        return 1;
    }

    //Set the port number
        int nPort = 49000;
    siLocal.sin_family = AF_INET;
    siLocal.sin_port = htons(nPort);

    siLocal.sin_addr.s_addr = inet_addr("127.0.0.1");
   
            nRet = sendto(soSend, datagram,41, 0, (SOCKADDR*)&siLocal, sizeof(SOCKADDR));
        if (nRet == SOCKET_ERROR) {
            printf("Sendto Error = %d\n", WSAGetLastError());
        }
    
    // Close the socket connection
        closesocket(soSend);
    //Clean up
    WSACleanup();
    system("pause");
    return 0;
}
