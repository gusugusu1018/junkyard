#include <stdio.h> //printf(), fprintf(), perror(), getc()
#include <sys/socket.h> //socket(), bind(), sendto(), recvfrom()
#include <arpa/inet.h> // struct sockaddr_in, struct sockaddr, inet_ntoa(), inet_aton()
#include <stdlib.h> //atoi(), exit(), EXIT_FAILURE, EXIT_SUCCESS
#include <string.h> //memset(), strcmp()
#include <unistd.h> //close()
#include <stdint.h> //uint_t

#define MSG_FAILURE -1

#define MAX_MSGSIZE 1024
#define MAX_BUFSIZE (MAX_MSGSIZE + 1)

int  get_socket(const char *);
void sockaddr_init (const char *, unsigned short, struct sockaddr *);
int  udp_send(int, const uint8_t *, int, struct sockaddr *);
int  udp_receive(int, uint8_t *, int, struct sockaddr *);
void socket_close(int);

int main(int argc, char* argv[]) {

    const char *address = "127.0.0.1";
    unsigned short port = 9750;
    struct sockaddr servSockAddr, clitSockAddr;
    uint8_t recvBuffer[MAX_BUFSIZE];

    int server_sock = get_socket("udp");
    sockaddr_init(address, port, &servSockAddr);

    if (bind(server_sock, &servSockAddr, sizeof(servSockAddr)) < 0) {
        perror("bind() failed.");
        exit(EXIT_FAILURE);
    }

    while(1) {
        int recvMsgSize = udp_receive(server_sock, recvBuffer, MAX_BUFSIZE, &clitSockAddr);
        if (recvMsgSize == MSG_FAILURE) continue;

        //printf("message received from %s.\n", inet_ntoa(((struct sockaddr_in *)&clitSockAddr)->sin_addr));
        printf("message received from %s. ", inet_ntoa(((struct sockaddr_in *)&clitSockAddr)->sin_addr));
        printf("The massege is");
	for (uint8_t i=0;i<16;i++) {
		if (i%4==0)
        		printf(" | 0x%x", recvBuffer[i]);
		else
        		printf(" 0x%x", recvBuffer[i]);
	}
        printf("\n");

        int sendMsgSize = udp_send(server_sock, recvBuffer, recvMsgSize, &clitSockAddr);
        if (sendMsgSize == MSG_FAILURE) continue;
    }
}

int get_socket(const char *type) {
    int sock;

    if (strcmp(type, "udp") == 0) {
        sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    } else if(strcmp(type, "tcp") == 0) {
        sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    }

    if (sock < 0){
        perror("socket() failed.");
        exit(EXIT_FAILURE);
    }

    return sock;
}

void sockaddr_init (const char *address, unsigned short port, struct sockaddr *sockaddr) {

    struct sockaddr_in sockaddr_in;
    sockaddr_in.sin_family = AF_INET;

    if (inet_aton(address, &sockaddr_in.sin_addr) == 0) {
        if (strcmp(address, "") == 0 ) {
            sockaddr_in.sin_addr.s_addr = htonl(INADDR_ANY);
        } else {
            fprintf(stderr, "Invalid IP Address.\n");
            exit(EXIT_FAILURE);
        }
    }

    if (port == 0) {
        fprintf(stderr, "invalid port number.\n");
        exit(EXIT_FAILURE);
    }
    sockaddr_in.sin_port = htons(port);

    *sockaddr = *((struct sockaddr *)&sockaddr_in);
}

int udp_send(int sock, const uint8_t *data, int size, struct sockaddr *sockaddr) {
    int sendSize;
    sendSize = sendto(sock, data, size, 0, sockaddr, sizeof(*sockaddr));
    if (sendSize != size) {
        perror("sendto() failed.");
        return MSG_FAILURE;
    }
    return sendSize;
}

int udp_receive(int sock, uint8_t *buffer, int size, struct sockaddr *sockaddr) {
    unsigned int sockaddrLen = sizeof(*sockaddr);
    int receivedSize = recvfrom(sock, buffer, MAX_BUFSIZE, 0, sockaddr, &sockaddrLen);
    if (receivedSize < 0) {
        perror("recvfrom() failed.");
        return MSG_FAILURE;
    }

    return receivedSize;
}

void socket_close(int server) {
    if (close(server) < 0) {
        perror("close() failed.");
        exit(EXIT_FAILURE);
    }
}
