#include "Sniffer.h"
#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <netinet/tcp.h>
#include <netinet/ether.h>
#include <pcap.h>
#include <stdlib.h>

#define SIZE_ETHERNET 14

using namespace std;


struct arphdr2 {{ 
    u_int16_t htype;    /* Hardware Type           */ 
    u_int16_t ptype;    /* Protocol Type           */ 
    u_char hlen;        /* Hardware Address Length */ 
    u_char plen;        /* Protocol Address Length */ 
    u_int16_t oper;     /* Operation Code          */ 
    u_char sha[6];      /* Sender hardware address */ 
    u_char spa[4];      /* Sender IP address       */ 
    u_char tha[6];      /* Target hardware address */ 
    u_char tpa[4];      /* Target IP address       */ 
}};

Sniffer::Sniffer(){{
	snfmutex = new mutex();
}}

Sniffer::~Sniffer(){{
	snfmutex->lock();
	delete snfmutex;
}}

vector<Antigen> Sniffer::getSnifferAntigens(){{

	
	snfmutex->lock();
	vector<Antigen> aux(snfAntigens);
	snfAntigens = vector<Antigen>();
	snfmutex->unlock();

	return aux;
}}

void Sniffer::stopSniffer(){{
	snfStop = true;
}}

void Sniffer::my_packet_handler(
		const struct pcap_pkthdr *header,
		const u_char *packet){{

	/* First, lets make sure we have an IP packet */
	struct ether_header *eth_header;
	eth_header = (struct ether_header *) packet;
	vector<bool> vecBool;
	vector<int> vecInt;
	vector<string> vecStr(2);

	if (ntohs(eth_header->ether_type) == ETHERTYPE_IP) {{
	    struct ip *ip_header;
	    ip_header = (struct ip*)(packet + SIZE_ETHERNET);

	    if (!(ip_header -> ip_p == IPPROTO_TCP) or (ip_header -> ip_p == IPPROTO_UDP)){{
	        //cout << "Not a TCP\n";
	        return;
	    }}

	    char ip2[30];
	    char ip3[30];
	    strcpy(ip2, (char*)inet_ntoa((struct in_addr)ip_header->ip_src));
	    strcpy(ip3, (char*)inet_ntoa((struct in_addr)ip_header->ip_dst));

	    vecStr[0] = string(ip2);
	    vecStr[1] = string(ip3);

	    struct tcphdr *tcp_header;
	    // cout << "IP lenght: " << ip_header->ip_hl << endl;
	    tcp_header = (struct tcphdr *) (packet + SIZE_ETHERNET + (ip_header->ip_hl * 4));

	    //file << "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ";

	    int sp = ntohs(tcp_header->th_sport);
	    int dp = ntohs(tcp_header->th_dport);

	    //int dp = ntohs(tcp_header->th_dport);

	    {0}

	    Antigen auxAntigen = Antigen(true, snfStep++, vecInt, vecBool, vecStr);
	    
	    snfmutex->lock();
	    snfAntigens.push_back(auxAntigen);
	    snfmutex->unlock();


	    //cout << "Sourcer port: " << ntohs(tcp_header->th_sport) << "\n";
	    //cout << "Destination port: " << ntohs(tcp_header->th_dport) << "\n";

	    return;
	}}

	else if (ntohs(eth_header->ether_type) == ETHERTYPE_ARP){{

		return;

	    struct arphdr2 *arpheader;
	    arpheader = (struct arphdr2*)(packet + SIZE_ETHERNET);

	    //printf("\nTarget MAC: "); 
	    int aux = 0;
	    for(int i=0; i<6;i++){{
	        //printf("%c:", arpheader->tha[i]); 
	        aux = aux + (int)arpheader->tha[i];
	    }}	    

	    //file << "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ";
	    

	    if (ntohs(arpheader->oper) == 1) vecBool.push_back(true);
	    else vecBool.push_back(false);

	    if (aux == 0) vecBool.push_back(true);
	    else vecBool.push_back(false);

	    Antigen auxAntigen = Antigen(true, snfStep++, vector<int>(), vecBool, vecStr	);
	    
	    snfmutex->lock();
	    snfAntigens.push_back(auxAntigen);
	    snfmutex->unlock();
	}}
}}

void Sniffer::snifferRun(){{

	//cout << "D: SNIFFER" << endl;


	const char *device = "wlan0";
	char error_buffer[PCAP_ERRBUF_SIZE];
	pcap_t *handle;
	/* Snapshot length is how many bytes to capture from each packet. This includes*/
	int snapshot_length = 1024;
	/* End the loop after this many packets are captured */
	int total_packet_count = 0;
	u_char *my_arguments = NULL;

	handle = pcap_open_live(device, snapshot_length, 0, 0, error_buffer);
	pcap_set_rfmon(handle, 1);
	pcap_set_promisc(handle, 1); 

	int res;
	const u_char *packet;
	struct pcap_pkthdr *header;

	while (!snfStop){{
		res = pcap_next_ex(handle, &header, &packet);
		if (res == 1){{
			my_packet_handler(header, packet);
		}}

	}}

	//thread th1(pcap_loop, handle, total_packet_count, my_packet_handler, my_arguments);
	//system("pause");
	//pcap_breakloop(handle);
	pcap_close(handle);
	//pcap_loop(handle, total_packet_count, my_packet_handler, my_arguments);	
}}

