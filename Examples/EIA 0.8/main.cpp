#include <bits/stdc++.h>
#include "Population.h"
#include "Cell.h"
#include "Administrator.h"
#include "Sniffer.h"
#include "Danger.h"

using namespace std;

//g++ *.cpp -lpcap -pthread

int main(){

	thread thSniffer(snifferRun);
	thread thDanger(dangerRun);

	Administrator admin = Administrator();
	admin.main();

	/*
	Cell cell;
	cell.go();

	Population population;
	population.go();

	//dangerRun();

	thread thDanger(dangerRun);
	this_thread::sleep_for(chrono::milliseconds(5000));

	vector<Antigen> anti = getDangerAntigens();
	for (Antigen antigen: anti){
		vector<int> b2 = antigen.getValueInt();
		for(auto b: b2){
			cout << b << " ";
		}
		cout << endl;
	}

	this_thread::sleep_for(chrono::milliseconds(5000));
	stopDanger();
	thDanger.join();	

	anti = getDangerAntigens();
	for (Antigen antigen: anti){
		vector<int> b2 = antigen.getValueInt();
		for(auto b: b2){
			cout << b << " ";
		}
		cout << endl;
	}

	/*
	thread thSniffer(snifferRun);
	this_thread::sleep_for(chrono::milliseconds(5000));
	stopSniffer();
	thSniffer.join();	

	vector<Antigen> anti = getSnifferAntigens();
	for (Antigen antigen: anti){
		vector<bool> b2 = antigen.getValueBool();
		for(bool b: b2){
			cout << b << " ";
		}
		cout << endl;
	}
	*/


	
	
	return 0;
}