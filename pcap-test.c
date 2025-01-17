#include "pcap-test.h"

Param param = {
	.dev_ = NULL
};

int		main(int argc, char* argv[])
{
	if (!parse(&param, argc, argv))
		return -1;

	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t* pcap = pcap_open_live(param.dev_, BUFSIZ, 1, 1000, errbuf);
	if (pcap == NULL)
	{
		fprintf(stderr, "pcap_open_live(%s) return null - %s\n", param.dev_, errbuf);
		return (-1);
	}

	while (true)
	{
		struct pcap_pkthdr* header;
		const u_char* packet;
		int res = pcap_next_ex(pcap, &header, &packet);
		if (res == 0)
			continue;
		if (res == PCAP_ERROR || res == PCAP_ERROR_BREAK)
		{
			printf("pcap_next_ex return %d(%s)\n", res, pcap_geterr(pcap));
			break;
		}

		struct libnet_ethernet_hdr *eth_hdr = (struct libnet_ethernet_hdr *)packet;
		if (ntohs(eth_hdr -> ether_type) != ETHERTYPE_IP)
			continue ;
		struct libnet_ipv4_hdr *ip_hdr = (struct libnet_ipv4_hdr *)((char *)eth_hdr + LIBNET_ETH_H);
		if (ip_hdr -> ip_p != 0x06) // if it is not a TCP Header
			continue ;
		struct libnet_tcp_hdr *tcp_hdr = (struct libnet_tcp_hdr *)((char *)ip_hdr + (ip_hdr -> ip_hl << 2));

		printf("---------------------------------------------------------\n");
		printf("Ethernet Header\n");
		printf("Source mac		: ");
		_print_mac(eth_hdr -> ether_shost);
		printf("Destination mac	: ");
		_print_mac(eth_hdr -> ether_dhost);
		printf("IP Header\n");
		printf("Source IP		: ");
		_print_ip(ip_hdr -> ip_src);
		printf("Destination IP	: ");
		_print_ip(ip_hdr -> ip_dst);
		printf("TCP Header\n");
		printf("Source Port		: %hu\n", ntohs(tcp_hdr -> th_sport));
		printf("Destination Port: %hu\n", ntohs(tcp_hdr -> th_dport));

		if (ntohs(ip_hdr -> ip_len) > LIBNET_IPV4_H + tcp_hdr -> th_off * 4)
		{
			printf("Data			: ");
			int data_len = ip_hdr -> ip_len - LIBNET_IPV4_H - LIBNET_TCP_H;
			if (data_len > 20)
				data_len = 20;
			for (int i = 0; i < data_len; i++)
				printf("%02x", packet[LIBNET_ETH_H + LIBNET_IPV4_H + tcp_hdr -> th_off * 4 + i]);
			printf("\n");
		}
		else
			printf("No Data\n");

		printf("\n");
	}

	pcap_close(pcap);
}

void	usage(void)
{
	printf("syntax: pcap-test <interface>\n");
	printf("sample: pcap-test wlan0\n");
}

bool	parse(Param* param, int argc, char* argv[])
{
	if (argc != 2)
	{
		usage();
		return false;
	}
	param->dev_ = argv[1];
	return true;
}
