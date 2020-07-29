#ifndef SNIFFER_H
#define SNIFFER_H

#include "Antigen.h"
#include <pcap.h>

vector<Antigen> getSnifferAntigens();

void my_packet_handler(
        u_char *args,
        const struct pcap_pkthdr *header,
        const u_char *packet);

void snifferRun();

void stopSniffer();

/*
class Sniffer {

private:
	mutex mtx;
	static vector<Antigen> antigens;
	static int step;

public:
	Sniffer();
	~Sniffer();
	vector<Antigen> getAntigens();
	void operate();
	static void my_packet_handler(
		u_char *args,
    	const struct pcap_pkthdr *header,
    	const u_char *packet);
};
*/
#endif