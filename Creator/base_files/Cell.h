#ifndef {0}_H
#define {0}_H

#include <bits/stdc++.h>
#include "Antigen.h"
using namespace std;

class {0} {{

private:
	vector<double> geneticCode;
	vector<double> internalVar;
	vector<{0}*> *cells;
	int index;

	void cellConstructor(vector<{0}*> *cellsC, int ind);
	void cellConstructor2(vector<{0}*> *cellsC, int ind, vector<double> genetic);
	int setCell({0} *cell, int ind);
	{0}* getCell(int ind);

public:
	{0}(vector<{0}*> *cellsC, int ind);
	{0}(vector<{0}*> *cellsC, int ind, vector<double> genetic);

	{0}();
	~{0}();

	int go(Antigen antigen);
	vector <double> getGeneticCode();
	int setInternalVar(double var, int ind);
	double getInternalVar(int ind);
}};

#endif