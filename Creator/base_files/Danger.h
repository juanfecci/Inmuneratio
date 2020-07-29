#ifndef DANGER_H
#define DANGER_H

#include "Antigen.h"

class Danger{

private:
	mutex *dngmutex;
	vector<Antigen> dngAntigens;
	int dngStep = 0;
	bool dngStop = false;

	vector<bool> valueRun;

	int getDISKValue();
	int getCPUValue();
	int getRAMValue();
	pair<int, int> getNETValue(string device);
	int getCONNValue();
	int getPROCValue();
	int getLOGValue();
	int getFAILValue();
	
public:

	Danger(vector<bool> valr);
	Danger();
	~Danger();

	vector<Antigen> getDangerAntigens();
	void dangerRun();
	void stopDanger();
};



#endif