#ifndef ANTIGEN_H
#define ANTIGEN_H

#include <bits/stdc++.h>
using namespace std;

class Antigen{
private:
	bool type;
	int step;

	int size_int;
	int size_bool;
	int size_char;

	vector<int> value_int;
	vector<bool> value_bool;
	vector<string> value_string;

public:
	Antigen(bool type, int step, vector<int> value_int, vector<bool> value_bool, vector<string> value_string);
	~Antigen();

	bool getType();
	int getStep();

	vector<int> getValueInt();
	vector<bool> getValueBool();
	vector<string> getValueString();
};

#endif