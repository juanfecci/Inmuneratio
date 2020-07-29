#ifndef CELL_H
#define CELL_H

#include <bits/stdc++.h>
#include "Antigen.h"
using namespace std;

//EIA
class Cell {

private:
	vector<double> geneticCode;
	vector<double> internalVar;

	vector<Cell> *cells;
	int index;

	//EIA
	static double energia_inicial;
	static double consumo_energia_basal;
	static double energia_maxima;
	static double energia_nuevo;
	static double toxicidad_incremental;
	static double maximo_aporte;

	void cellConstructor(vector<Cell> *cellsC, int ind);
	Cell& getCell(int ind);
	int setCell(Cell cell, int ind);

public:
	
	Cell(vector<Cell> *cellsC, int ind);
	//Cell(vector<double> vecD, PopT *pop, int ind); //EIA

	Cell();
	~Cell();

	int go(Antigen antigen);

	vector <double> getGeneticCode();

	int setInternalVar(double var, int ind);
	double getInternalVar(int ind);
};

#endif