#ifndef POPULATION_H
#define POPULATION_H

#include <bits/stdc++.h>
//#include "Administrator.h"
#include "Cell.h"
using namespace std;


template <class CellT, class AdminT>
class Population{

private:
	vector<CellT> cells;
	vector<double> stats;
	AdminT *administrator;

	void populationConstructor(int nCells, AdminT *admin);

	//EIA
	static double penalizacion;
	static double razon_produccion;
/*
	int idPopulation;
	//Administrator admin;
	vector<Cell> cells;
	vector<double> stats;
*/
public:
	int idPopulation;
	
	Population();
	~Population();

	Population(int nCells, AdminT *admin);

	int go(vector<Antigen> antigens);

	CellT* getCell(int ind);
	int setCell(CellT cell, int ind);

	int sendCell();
	vector<CellT> reciveCell();

	double getStats(int ind);
};

#endif