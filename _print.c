#include "pcap-test.h"

int		_print_ip(struct in_addr ip)
{
	uint64_t ip_addr = (uint64_t)ntohl(ip.s_addr);
	printf("%llu.%llu.%llu.%llu", (ip_addr & 0xFF000000) >> 24, (ip_addr & 0xFF0000) >> 16, (ip_addr & 0xFF00) >> 8, ip_addr & 0xFF);
	printf("\n");
	return (0);
}

int		_print_mac(uint8_t mac[])
{
	for (int i = 0; i < ETHER_ADDR_LEN; i++)
	{
		printf("%02x", mac[i]);
		if (i != ETHER_ADDR_LEN - 1)
			printf(":");
	}
	printf("\n");
	
	return (0);
}
