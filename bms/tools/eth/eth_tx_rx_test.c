#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <net/if.h>

#define DATA_BUFFER_SIZE 65536
#define MAGIC_PACKET_LEN (102 + 14)

static unsigned char buffer[DATA_BUFFER_SIZE] = { 0 };

unsigned char specific_packet_header[12] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x64, 0x00, 0x01, 0x02, 0x03, 0x04
};

unsigned char magic_mac[6] = { 0x64, 0x00, 0x01, 0x02, 0x03, 0x04 };

static int is_expected_packet(void)
{
	if (!memcmp(buffer, specific_packet_header,
		    sizeof(specific_packet_header)))
		return 1;
	else
		return 0;
}

int main(int argc, char *argv[])
{
	struct sockaddr_ll sll;
	int sockfd;
	struct ifreq ifr;
	struct sockaddr_ll recvaddr;
	socklen_t addrlen = sizeof(recvaddr);
	unsigned char mac[6] = { 0 };
	int send_cnt, recv_cnt;
	unsigned long pkt_seq = 0;
	int i = 0;

	/* Create socket. */
	sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (sockfd == -1) {
		perror("socket");
		return -1;
	}

	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name, argv[1], IFNAMSIZ - 1);
	ioctl(sockfd, SIOCGIFHWADDR, &ifr);
	memcpy(mac, (unsigned char *)ifr.ifr_hwaddr.sa_data, 6);
	printf("mac: %02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2],
	       mac[3], mac[4], mac[5]);

	/* Bind to interface. */
	memset(&sll, 0, sizeof(sll));
	sll.sll_family = AF_PACKET;
	sll.sll_ifindex = if_nametoindex(argv[1]); /* Interface index. */
	sll.sll_halen = ETH_ALEN; /* MAC address length. */

	if (bind(sockfd, (struct sockaddr *)&sll, sizeof(sll)) == -1) {
		perror("bind");
		close(sockfd);
		return -1;
	}

	if (!strncmp(argv[2], "magic", 5)) {
		printf("send magic packet...\n");
		memcpy(buffer, magic_mac, 6);
		memcpy(buffer + 6, mac, 6);
		buffer[12] = (102 & 0xff00) >> 8;
		buffer[13] = 102 & 0x00ff;
		memcpy(buffer + 14, specific_packet_header, 12);

		for (i = 0; i < 15; i++)
			memcpy(buffer + 14 + 12 + i * 6, magic_mac, 6);

		/* Send Ethernet frame. */
		send_cnt = sendto(sockfd, buffer, MAGIC_PACKET_LEN, 0, NULL, 0);
		if (send_cnt == -1) {
			perror("sendto");
			close(sockfd);
			return -1;
		}
		printf("Sent %d bytes\n", send_cnt);
		memset(buffer, 0, send_cnt);
		send_cnt = 0;
		recv_cnt = 0;

		close(sockfd);
		return 0;
	}

	printf("start receive...\n");
	while (1) {
		while (1) {
			recv_cnt = recvfrom(sockfd, buffer, sizeof(buffer), 0,
					    (struct sockaddr *)&recvaddr,
					    &addrlen);
			if (recv_cnt == -1) {
				perror("recvfrom");
				close(sockfd);
				return -1;
			}
			if (is_expected_packet())
				break;
		}
		pkt_seq++;
		printf("pkt_seq: %ld\n", pkt_seq);
		printf("have received correctly %d bytes\n", recv_cnt);

		memcpy(buffer, buffer + 6, 6);
		memcpy(buffer + 6, mac, 6);

		/* Send Ethernet frame. */
		send_cnt = sendto(sockfd, buffer, recv_cnt, 0, NULL, 0);
		if (send_cnt == -1) {
			perror("sendto");
			close(sockfd);
			return -1;
		}
		printf("Sent %d bytes\n", send_cnt);
		printf("\n");
		memset(buffer, 0, send_cnt);
		send_cnt = 0;
		recv_cnt = 0;
	}

	close(sockfd);
	return 0;
}
