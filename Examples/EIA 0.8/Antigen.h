#ifndef ANTIGEN_H
#define ANTIGEN_H

#include <bits/stdc++.h>
using namespace std;

class Antigen{
private:
	bool type;
	int step;
	vector<int> value_int;
	vector<bool> value_bool;

public:
	Antigen(bool type, int step, vector<int> value_int, vector<bool> value_bool);
	~Antigen();
	bool getType();
	int getStep();
	vector<int> getValueInt();
	vector<bool> getValueBool();
};

#endif