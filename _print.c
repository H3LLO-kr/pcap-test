#include "pcap-test.h"

int		_print_ip(struct in_addr ip)
{
	uint32_t ip_addr = (uint32_t)ntohs(ip.s_addr);
	printf("%u.%u.%u.%u", ip_addr & 0xF000 >> 24, ip_addr & 0x0F00 >> 16, ip_addr & 0x00F0 >> 8, ip_addr & 0x000F);
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
