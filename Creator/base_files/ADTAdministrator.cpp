#include "Administrator.h"
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 

template <class Container>
void split(const std::string& str, Container& cont, char delim = ' ')
{{
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {{
        cont.push_back(token);
    }}
}}

void Administrator::AdministratorConstructor(bool snfbool, bool dngbool, string selfip, string brip){{

	selfIP = new char[selfip.length()];
	broadcastIP = new char[brip.length()];

	strcpy(selfIP, selfip.c_str()); 
	strcpy(broadcastIP, brip.c_str()); 

{2}
}}

void Administrator::AdministratorDestructor(){{
	{0}

	delete selfIP;
	delete broadcastIP;	
}}

int Administrator::updateResponse(int option){{
	return 0;
}}

{1} Administrator::getCell(){{
	return {1}();
}}

int Administrator::startConnection(){{
	return 0;
}}

int Administrator::finish(){{
	return 0;
}}

int Administrator::sendDiscovery(){{
	int sock;                         /* Socket */
    struct sockaddr_in broadcastAddr; /* Broadcast address */
    int broadcastPermission;          /* Socket opt to set permission to broadcast */
    unsigned int sendStringLen;       /* Length of string to broadcast */

    /* Create socket for sending/receiving datagrams */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        return -1;

    /* Set socket to allow broadcast */
    broadcastPermission = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission, 
          sizeof(broadcastPermission)) < 0){{
    	cout <<"setsockopt() failed" << endl;
    	return -1;
    }}
        
    /* Construct local address structure */
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));   /* Zero out structure */
    broadcastAddr.sin_family = AF_INET;                 /* Internet address family */
    broadcastAddr.sin_addr.s_addr = inet_addr(broadcastIP);/* Broadcast IP address */
    broadcastAddr.sin_port = htons(broadcastPort);         /* Broadcast port */

    string str = "0" + string(selfIP);
    char sendString[str.length()];
    strcpy(sendString, str.c_str());

    sendStringLen = strlen(sendString);  /* Find length of sendString */
    for (int i = 0; i < 3; ++i)
    {{
         if (sendto(sock, sendString, sendStringLen, 0, (struct sockaddr *) 
               &broadcastAddr, sizeof(broadcastAddr))){{
          cout << "send package " << i+1 << endl;
         }}
         else{{
          cout << "sendto() sent a different number of bytes than expected" << endl;
          return -1;
         }}
             
        sleep(2);   /* Avoids flooding the network */
    }}
    close(sock);
    
    return 0;
}}

int Administrator::recvDiscovery(char* sendIp){{
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	char buffer[1024] = {{0}}; 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	}} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(tcpPort); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, sendIp, &serv_addr.sin_addr)<=0) 
	{{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	}} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	}} 

	string strSend = "0" + string(selfIP);
	char charSend[strSend.length()];
	strcpy(charSend, strSend.c_str()); 

	send(sock , charSend , strlen(charSend) , 0 ); 
	valread = read( sock , buffer, 1024); 

	string ips(buffer);
	split(ips, redIp, '-');

	close(sock);

	string ownIp(selfIP);
	string otherIp(sendIp);

	for(string strIp: redIp){{
		if (strIp != ownIp && strIp != otherIp) updateDisc(strIp);
	}}

	return 0; 
}}

int Administrator::updateDisc(string sendIp){{
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	}} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(tcpPort); 

	char sendIpChar[sendIp.length()];
	strcpy(sendIpChar, sendIp.c_str()); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, sendIpChar, &serv_addr.sin_addr)<=0) 
	{{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	}} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	}} 

	string strSend = "1" + string(selfIP);
	char charSend[strSend.length()];
	strcpy(charSend, strSend.c_str()); 

	send(sock , charSend , strlen(charSend) , 0 ); 

	close(sock);

	return 0;
}}

int Administrator::updateCell(int idHost, {1} cell, int option){{

	if (idHost < 0) for (int i = 0; i < redIp.size(); ++i) updateCell(i, cell, option);		
	else{{
		int sock = 0, valread; 
		struct sockaddr_in serv_addr; 

		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
		{{ 
			printf("\n Socket creation error \n"); 
			return -1; 
		}} 

		serv_addr.sin_family = AF_INET; 
		serv_addr.sin_port = htons(tcpPort); 

		char sendIpChar[redIp[idHost].length()];
		strcpy(sendIpChar, redIp[idHost].c_str()); 
		
		// Convert IPv4 and IPv6 addresses from text to binary form 
		if(inet_pton(AF_INET, sendIpChar, &serv_addr.sin_addr)<=0) 
		{{ 
			printf("\nInvalid address/ Address not supported \n"); 
			return -1; 
		}} 

		if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
		{{ 
			printf("\nConnection Failed \n"); 
			return -1; 
		}} 

		vector<double> vecD= cell.getGeneticCode();
		string gen = "";
		for (int i = 0; i < vecD.size(); ++i)
		{{
			if (i == 0) gen += to_string(vecD[i]);
			else gen += "-" + to_string(vecD[i]);	
		}}

		string strSend = "1" + to_string(option) + gen;
		char charSend[strSend.length()];
		strcpy(charSend, strSend.c_str()); 

		send(sock , charSend , strlen(charSend) , 0 ); 

		close(sock);
	}}
	return 0;

	
}}


void Administrator::serverDiscovery(){{
	int sock;                         /* Socket */
    struct sockaddr_in broadcastAddr; /* Broadcast Address */
    char recvString[20]; /* Buffer for received string */
    int recvStringLen;                /* Length of received string */

    /* Create a best-effort datagram socket using UDP */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){{
        cout << "socket() failed" << endl;
        return;
    }}

    /* Construct bind structure */
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));   /* Zero out structure */
    broadcastAddr.sin_family = AF_INET;                 /* Internet address family */
    broadcastAddr.sin_addr.s_addr = htonl(INADDR_ANY);  /* Any incoming interface */
    broadcastAddr.sin_port = broadcastPort;     /* Broadcast port */

    if (bind(sock, (struct sockaddr *) &broadcastAddr, sizeof(broadcastAddr)) < 0){{
        cout << "bind() failed" << endl;
    	return;
    }}

    while(!StopServerD){{
    	/* Receive a single datagram from the server */
    	if ((recvStringLen = recvfrom(sock, recvString, 20, 0, NULL, 0)) < 0){{
    	    cout << "recvfrom() failed" << endl;
    	}}
    	else{{
    		recvString[recvStringLen] = '\0';
    		printf("Received: %s\n", recvString);    /* Print the received string */		
    	}}
    	
    }} 
    close(sock);
}}

void Administrator::serverTCP(){{
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {{0}}; 
	
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{{ 
		cout << "socket failed" <<endl; 
		return;
	}} 
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt, sizeof(opt))) 
	{{ 
		cout << "setsockopt" << endl; 
		return;
	}} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = tcpPort; 

	if (bind(server_fd, (struct sockaddr *)&address, 
								sizeof(address))<0) 
	{{ 
		cout << "bind failed" << endl;
		return;
	}} 
	
	while(!StopServerTCP){{
		
		if (listen(server_fd, 3) < 0) 
		{{ 
			cout << "listen" << endl;
		}} 
		else{{
			if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
							(socklen_t*)&addrlen))<0) 
			{{ 
				cout << "accept" << endl;
			}} 

			std::string s;

			int n;
			char buf[256];

			while((n = recv(new_socket, buf, sizeof(buf), 0)) > 0)
			    s.append(buf, buf + n);

			if(n < 0) cout << "Recv error" << '\n';
			else{{
				//Discovery section
				if (s[0] == '0'){{
					string recIp = s.substr(1, s.length()-1);
					redIp.push_back(recIp);

					string sendstr = "";
					for(string auxStr: redIp){{
						sendstr += auxStr;
					}}

					char sendChar[sendstr.length()];
					strcpy(sendChar, sendstr.c_str());

					send(new_socket, sendChar, strlen(sendChar), 0);
					//Envio de direcciones
				}}
				
				else if(s[0] == '1'){{
					int pop = s[1] - '0';
					string genetic = s.substr(2, s.length()-1);
					vector<string> vs;
					split(genetic, vs, '-');

					vector<double> gen;
					for(string auxstr: vs) gen.push_back(atof(auxstr.c_str()));

					//Set thing in python

					if (pop == 1){{
						population1.reciveCell(gen);
					}}
				}}
				else if(s[0] == '2'){{
					string recIp = s.substr(1, s.length()-1);
					bool verif = true;
					for(string auxStr: redIp){{
						if (auxStr == recIp){{
							verif = false;
							break;
						}}
					}}
					if (verif) redIp.push_back(recIp);
				}}	
			}}

			close(new_socket);
			
			std::cout << "received: " << s << '\n';	
		}}
		
			
	}}
	close(server_fd);
	close(new_socket);
}}