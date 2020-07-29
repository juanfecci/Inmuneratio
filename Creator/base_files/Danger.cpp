#include "Danger.h"
#include <bits/stdc++.h>
#include <sys/statvfs.h>
#include "sys/types.h"
#include "sys/sysinfo.h"
#include <unistd.h>

using namespace std;

Danger::Danger(){{
    valueRun = vector<bool>{0};
    dngmutex = new mutex();
}}

Danger::Danger(vector<bool> valr){{
    valueRun = valr;
}}

Danger::~Danger(){{
    dngmutex->lock();
    delete dngmutex;
}}

vector<Antigen> Danger::getDangerAntigens(){{

	dngmutex->lock();
    vector<Antigen> aux(dngAntigens);
	dngAntigens = vector<Antigen>();
	dngmutex->unlock();

	return aux;
}}

void Danger::dangerRun(){{

    while (!dngStop){{
        vector<int> vecInt;

        if (valueRun[0]) vecInt.push_back(getDISKValue());
        if (valueRun[1]) vecInt.push_back(getCPUValue());
        if (valueRun[2]) vecInt.push_back(getRAMValue());

        string deviceNet = "wlan0";
        pair<int, int> netPar = getNETValue(deviceNet);

        if (valueRun[3]) vecInt.push_back(netPar.first); //rx
        if (valueRun[4]) vecInt.push_back(netPar.second); //tx
        if (valueRun[5]) vecInt.push_back(getCONNValue());
        if (valueRun[6]) vecInt.push_back(getPROCValue());
        if (valueRun[7]) vecInt.push_back(getLOGValue());
        if (valueRun[8]) vecInt.push_back(getFAILValue());

        Antigen auxAntigen = Antigen(false, dngStep++, vecInt, vector<bool>(), vector<string>());
        dngmutex->lock();
        dngAntigens.push_back(auxAntigen);
        dngmutex->unlock();  
    }}
    
}}

int Danger::getDISKValue(){{
	struct statvfs fiData;
	struct statvfs *fpData;

	if((statvfs(".",&fiData)) < 0 ) {{
            return 0;
    }} else {{
            double prtg = (double)fiData.f_bfree / (double)fiData.f_blocks;
            prtg *= 100;
            return (int) prtg;
    }}
}}

int Danger::getCPUValue(){{
    long double a[4], b[4], loadavg;
    FILE *fp;

    fp = fopen("/proc/stat","r");
    fscanf(fp,"%*s %Lf %Lf %Lf %Lf",&a[0],&a[1],&a[2],&a[3]);
    fclose(fp);
    usleep(200000);

    fp = fopen("/proc/stat","r");
    fscanf(fp,"%*s %Lf %Lf %Lf %Lf",&b[0],&b[1],&b[2],&b[3]);
    fclose(fp);

    loadavg = ((b[0]+b[1]+b[2]) - (a[0]+a[1]+a[2])) / ((b[0]+b[1]+b[2]+b[3]) - (a[0]+a[1]+a[2]+a[3]));
    loadavg *= 100;

    return (int) loadavg;
}}

int Danger::getRAMValue(){{
    long long total, aval, ram;
    FILE *fp;

    fp = fopen("/proc/meminfo","r");
    fscanf(fp,"%*s %Ld %*s \n %*s %Ld %*s \n %*s %Ld",&total, &ram, &aval);
    fclose(fp);

    ram = total - aval;

    double aux = (double) ram / (double) total;
    aux *= 100;

    return (int) aux;
}}

pair<int, int> Danger::getNETValue(string device){{
    FILE*  fp;
    const int sizebuf=1234;
    char buff[sizebuf];
    if ((fp = popen ("sar -n DEV 1 1", "r"))== NULL){{
    	return 	{{0,0}};
	}}
    int cont = 0;

    double rx;
    double tx;

    int cont2 = 0;
    bool verif = false;
    while (fgets(buff, sizeof (buff), fp)) {{
    	if (cont++ >= 8){{

    		int size_buff = sizeof(buff) / sizeof(char);  
    		string s = ""; 
    		
    		for (int i = 0; i < size_buff; i++) {{ 
    		    s = s + buff[i]; 
    		}}     		

    		istringstream ss(s);
    		string token;

    		while(ss >> token) {{
    			if (cont2 == 4 && verif){{
    				cont2++;
    				stringstream convert(token);
    				convert >> rx;
    			}}
    			else if (cont2++ == 5 && verif){{
    				stringstream convert(token);
    				convert >> tx;
    			}}
    			else if (token == device) verif = true;    		     		    
    		}}
    		verif = false;
    		cont2 = 0;
    	}}
	}}
    pclose(fp);
    return {{(int) rx, (int) tx}};
}}

int Danger::getCONNValue(){{
    FILE*  fp;
    const int sizebuf=1234;
    char buff[sizebuf];
    if ((fp = popen ("netstat -an | wc -l", "r"))== NULL){{
    	return 	0;
	}}

	int value;

    while (fgets(buff, sizeof (buff), fp)) {{
    	int size_buff = sizeof(buff) / sizeof(char);  
    	string s = ""; 
    	
    	for (int i = 0; i < size_buff; i++) {{ 
    	    s = s + buff[i]; 
    	}}
    	istringstream ss(s);
    	ss >> value;
    	pclose(fp);
    	return value;
	}}
    pclose(fp);
    return 0;
}}

int Danger::getPROCValue(){{
    FILE*  fp;
    const int sizebuf=1234;
    char buff[sizebuf];
    if ((fp = popen ("ps -A --no-headers | wc -l", "r"))== NULL){{
    	return 	0;
	}}

	int value;

    while (fgets(buff, sizeof (buff), fp)) {{
    	int size_buff = sizeof(buff) / sizeof(char);  
    	string s = ""; 
    	
    	for (int i = 0; i < size_buff; i++) {{ 
    	    s = s + buff[i]; 
    	}}
    	istringstream ss(s);
    	ss >> value;
    	pclose(fp);
    	return value;
	}}
    pclose(fp);
    return 0;
}}

int Danger::getLOGValue(){{
    FILE*  fp;
    const int sizebuf=1234;
    char buff[sizebuf];
    if ((fp = popen ("cat /var/log/auth.log | wc -l", "r"))== NULL){{
    	return 	0;
	}}

	int value;

    while (fgets(buff, sizeof (buff), fp)) {{
    	int size_buff = sizeof(buff) / sizeof(char);  
    	string s = ""; 
    	
    	for (int i = 0; i < size_buff; i++) {{ 
    	    s = s + buff[i]; 
    	}}
    	istringstream ss(s);
    	ss >> value;
    	pclose(fp);
    	return value;
	}}
    pclose(fp);
    return 0;
}}

int Danger::getFAILValue(){{
    FILE*  fp;
    const int sizebuf=1234;
    char buff[sizebuf];
    if ((fp = popen ("cat /var/log/faillog | wc -l", "r"))== NULL){{
    	return 	0;
	}}

	int value;

    while (fgets(buff, sizeof (buff), fp)) {{
    	int size_buff = sizeof(buff) / sizeof(char);  
    	string s = ""; 
    	
    	for (int i = 0; i < size_buff; i++) {{ 
    	    s = s + buff[i]; 
    	}}
    	istringstream ss(s);
    	ss >> value;
    	pclose(fp);
    	return value;
	}}
    pclose(fp);
    return 0;
}}

void Danger::stopDanger(){{
	dngStop = true;
}}