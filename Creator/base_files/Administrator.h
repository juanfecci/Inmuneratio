#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <bits/stdc++.h>

{0}
#include "Response.h"
#include "Sniffer.h"
#include "Danger.h"

using namespace std;


class Administrator{{
private:
	queue<vector <double> > cellsQueue;
	{1}
	vector<string> redIp;

	char *selfIP;
	char *broadcastIP;

	unsigned short broadcastPort = 7750;
	unsigned short tcpPort = 7751;

	bool StopServerD = false;
	bool StopServerTCP = false;

	{3}

	//Response response;

	int sendDiscovery();
	int recvDiscovery(char* sendIp);
	int updateDisc(string sendIp);

	void serverDiscovery();
	void serverTCP();

	void AdministratorConstructor(bool snfbool, bool dngbool, string selfip = string("0.0.0.0"), string brip = string("255.255.255.255"));
	void AdministratorDestructor();

	//Declaration of private atributes and methods:	


	

public:
	Administrator();
	~Administrator();
	int updateResponse(int option);
	int updateCell(int idHost, {2} cell, int option);
	{2} getCell();
	int startConnection();
	int finish();
	int main();
}};

#endif