#ifndef {0}_H
#define {0}_H

#include <bits/stdc++.h>
//#include "Administrator.h"
#include "{1}.h"
using namespace std;


template <class CellT, class AdminT>
class {0}{{

private:
	vector<CellT*> cells;
	vector<CellT*> cellsRecv;
	vector<double> stats;
	AdminT *administrator;
	mutex *popmutex;

	void populationConstructor(int nCells, AdminT *admin);
	int cellsGo(Antigen antigen);
	int cellsGo(vector<Antigen> antigens);

	//Declaration of private atributes and methods:	
	

public:
	int idPopulation;
	
	{0}();
	~{0}();

	{0}(int nCells, AdminT *admin);

	int go(vector<Antigen> antigens);

	CellT* getCell(int ind);
	int setCell(CellT *cell, int ind);

	int sendCell();
	void reciveCell(vector <double> genetic);
	vector<CellT*> getRecvCells();

	double getStats(int ind);
}};



#endif