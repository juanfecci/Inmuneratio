#ifndef RESPONSE_H
#define RESPONSE_H

#include "Antigen.h"
#include <bits/stdc++.h>
using namespace std;


class Response {

public:
	Response();
	~Response();

	int notify(int value);

	int blockAntigen(int option, Antigen antigen);

	int blockPort(bool option, string arg);
	int blockIp(bool option, string arg);

	int dropAll();	
};

#endif