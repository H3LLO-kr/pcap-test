#ifndef PCAP_TEST_H

#define PCAP_TEST_H

#include <stdio.h>
#include <pcap/pcap.h>
#include <stdbool.h>
#include <stdint.h>
#include <libnet.h>

#define u_int8_t uint8_t

typedef struct {
	char* dev_;
} Param;

/*			pcap-test.c				*/
int		main(int argc, char* argv[]);
bool	parse(Param* param, int argc, char* argv[]);
void	usage(void);

/*			_print.c				*/
int		_print_ip(struct in_addr ip);
int		_print_mac(uint8_t mac[]);

#endif
