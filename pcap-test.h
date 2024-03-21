#include <stdio.h>
#include <libnet/libnet-headers.h>
#include <pcap.h>
#include <stdbool.h>

typedef struct {
	char* dev_;
} Param;

int main(int argc, char* argv[]);
bool parse(Param* param, int argc, char* argv[]);
void usage(void);
