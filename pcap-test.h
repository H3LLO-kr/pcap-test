#include <stdio.h>
#include <pcap/pcap.h>
#include <stdbool.h>
#include <stdint.h>
#include <libnet.h>

#define u_int8_t uint8_t

typedef struct {
	char* dev_;
} Param;

int main(int argc, char* argv[]);
bool parse(Param* param, int argc, char* argv[]);
void usage(void);
