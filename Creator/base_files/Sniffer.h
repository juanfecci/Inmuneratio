#ifndef SNIFFER_H
#define SNIFFER_H

#include "Antigen.h"
#include <pcap.h>

class Sniffer{

private:
	void my_packet_handler(
		const struct pcap_pkthdr *header,
		const u_char *packet);

	mutex *snfmutex;
	vector<Antigen> snfAntigens;
	int snfStep = 0;
	bool snfStop = false;

public:

	Sniffer();
	~Sniffer();

	vector<Antigen> getSnifferAntigens();	
	void snifferRun();
	void stopSniffer();
};

#endif