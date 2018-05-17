#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> //close
#include <arpa/inet.h> //inet_addr
#include <stdint.h> //uint

#define MSG_FAILURE -1
#define MAX_MSGSIZE 15
#define MAX_BUFSIZE (MAX_MSGSIZE + 1)

void makePacketBuf(uint8_t *packetBuf) {
	uint8_t csum=0;
// LB test
	packetBuf[0]=82;
	packetBuf[1]=192;//64//x
	packetBuf[2]=192;//64//y
	packetBuf[3]=128;//00//spdw
	packetBuf[4]=177;//0x31
	packetBuf[5]=130;//00//FrontARM
	packetBuf[6]=128;//00 
	packetBuf[7]=128;//00
	packetBuf[8]=178;//0x32
	packetBuf[9]=128;//00//BackARM
	packetBuf[10]=128;//00
	packetBuf[11]=128;//checksum
	packetBuf[12]=208;//0x50
	packetBuf[13]=0x40;//00
	packetBuf[14]=0;//00
	int i;
	for (i=0;i<15;i++) {
		csum+=(packetBuf[i]&0x7f);
	}
	packetBuf[15]=csum;//checksum//201?
}

int udpSend(int sock, const uint8_t *data, int size, struct sockaddr_in *sockaddr) {
	int sendSize;
	sendSize = sendto(sock, data, size, 0, (struct sockaddr *)sockaddr, sizeof(*sockaddr));
	if (sendSize != size) {
		perror("sendto() failed.");
		return MSG_FAILURE;
	}
	return sendSize;
}

int main(int argc, char** argv) {
	int sockDescripter;
	struct sockaddr_in addr;
	if ((sockDescripter = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		perror("soket");
		return -1;
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9750);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	uint8_t sendPacketBuffer[MAX_BUFSIZE];
	int sendSize = MAX_BUFSIZE;
	while (1) {
		makePacketBuf(sendPacketBuffer);
		int sendedSize = udpSend(sockDescripter, sendPacketBuffer, sendSize, &addr);
		if (sendedSize == MSG_FAILURE) break;
		sleep(0.09);
	}
	close(sockDescripter);
	return 0;
}
