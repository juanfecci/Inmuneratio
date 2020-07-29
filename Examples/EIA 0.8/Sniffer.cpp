#include "Sniffer.h"
#include <bits/stdc++.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <netinet/tcp.h>
#include <netinet/ether.h>
#include <pcap.h>
#include <stdlib.h>

#define SIZE_ETHERNET 14

using namespace std;


struct arphdr2 { 
    u_int16_t htype;    /* Hardware Type           */ 
    u_int16_t ptype;    /* Protocol Type           */ 
    u_char hlen;        /* Hardware Address Length */ 
    u_char plen;        /* Protocol Address Length */ 
    u_int16_t oper;     /* Operation Code          */ 
    u_char sha[6];      /* Sender hardware address */ 
    u_char spa[4];      /* Sender IP address       */ 
    u_char tha[6];      /* Target hardware address */ 
    u_char tpa[4];      /* Target IP address       */ 
};

mutex snfmutex;
vector<Antigen> snfAntigens;
int snfStep = 0;
bool snfStop = false;

vector<Antigen> getSnifferAntigens(){

	
	snfmutex.lock();
	vector<Antigen> aux(snfAntigens);
	snfAntigens = vector<Antigen>();
	snfmutex.unlock();

	return aux;
}

void stopSniffer(){
	snfStop = true;
}

void my_packet_handler(
		const struct pcap_pkthdr *header,
		const u_char *packet){

	/* First, lets make sure we have an IP packet */
	struct ether_header *eth_header;
	eth_header = (struct ether_header *) packet;
	vector<bool> vecBool;

	if (ntohs(eth_header->ether_type) == ETHERTYPE_IP) {
	    struct ip *ip_header;
	    ip_header = (struct ip*)(packet + SIZE_ETHERNET);

	    if (!(ip_header -> ip_p == IPPROTO_TCP) or (ip_header -> ip_p == IPPROTO_UDP)){
	        //cout << "Not a TCP\n";
	        return;
	    }

	    struct tcphdr *tcp_header;
	    // cout << "IP lenght: " << ip_header->ip_hl << endl;
	    tcp_header = (struct tcphdr *) (packet + SIZE_ETHERNET + (ip_header->ip_hl * 4));

	    //file << "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ";

	    int sp = ntohs(tcp_header->th_sport);
	    int dp = ntohs(tcp_header->th_dport);
	    //cout << sp << "--" << dp << endl;
	    //int dp = ntohs(tcp_header->th_dport);

	    if (sp == 23 || dp == 23){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 22 || dp == 22){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 21 || dp == 21){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 139 || dp == 139){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp >= 512 && sp <= 514){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 111 || dp == 111){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 2049 || dp == 2049){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 4045 || dp == 4045){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 135 || dp == 135 || sp == 137 || dp == 137 || sp == 138 || dp == 138 || sp == 139 || dp == 139 || sp == 445 || dp == 445){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 6000 || dp == 6000 || sp == 6255 || dp == 6255){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 53 || dp == 53){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 389 || dp == 389){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 25 || dp == 25){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 109 || dp == 109){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 143 || dp == 143){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 80 || dp == 80){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 443 || dp == 443){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 8000 || dp == 8000 || sp == 8080 || dp == 8080 || sp == 8888 || dp == 8888){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp <= 20){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}    

	    if (sp == 37 || dp == 37){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 69 || dp == 69){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 79 || dp == 79){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 119 || dp == 119){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 123 || dp == 123){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 515 || dp == 515){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 514 || dp == 514){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 161 || dp == 161 || sp == 162 || dp == 162){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 179 || dp == 179){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    if (sp == 1080 || dp == 1080){ vecBool.push_back(true);}
	    else{vecBool.push_back(false);}

	    Antigen auxAntigen = Antigen(true, snfStep++, vector<int>(), vecBool);
	    
	    snfmutex.lock();
	    snfAntigens.push_back(auxAntigen);
	    snfmutex.unlock();

	    //cout << "BOOOOOL" << snfAntigens.size() <<endl;

	    //cout << "Sourcer port: " << ntohs(tcp_header->th_sport) << "\n";
	    //cout << "Destination port: " << ntohs(tcp_header->th_dport) << "\n";

	    return;
	}

	else if (ntohs(eth_header->ether_type) == ETHERTYPE_ARP){

		return;

	    struct arphdr2 *arpheader;
	    arpheader = (struct arphdr2*)(packet + SIZE_ETHERNET);

	    //printf("\nTarget MAC: "); 
	    int aux = 0;
	    for(int i=0; i<6;i++){
	        //printf("%c:", arpheader->tha[i]); 
	        aux = aux + (int)arpheader->tha[i];
	    }	    

	    //file << "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ";
	    

	    if (ntohs(arpheader->oper) == 1) vecBool.push_back(true);
	    else vecBool.push_back(false);

	    if (aux == 0) vecBool.push_back(true);
	    else vecBool.push_back(false);

	    Antigen auxAntigen = Antigen(true, snfStep++, vector<int>(), vecBool);
	    
	    snfmutex.lock();
	    snfAntigens.push_back(auxAntigen);
	    snfmutex.unlock();
	}
}

void snifferRun(){

	//cout << "D: SNIFFER" << endl;


	char *device = "wlan0";
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

	while (!snfStop){
		//cout << snfAntigens.size() << ":SIZE1" << endl;
		res = pcap_next_ex(handle, &header, &packet);
		if (res == 1){
			my_packet_handler(header, packet);
		}

		//cout << snfAntigens.size() << ":SIZE2" << endl;

	}

	//thread th1(pcap_loop, handle, total_packet_count, my_packet_handler, my_arguments);
	//system("pause");
	//pcap_breakloop(handle);
	pcap_close(handle);
	//pcap_loop(handle, total_packet_count, my_packet_handler, my_arguments);	
}

