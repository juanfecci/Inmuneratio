#include "Cell.h"

double Cell::energia_inicial = 200;

double Cell::consumo_energia_basal = 1;

double Cell::energia_maxima = 800;

double Cell::energia_nuevo = 40;

double Cell::toxicidad_incremental = 18;

double Cell::maximo_aporte = 200;

void Cell::cellConstructor(vector<Cell> *cellsC, int ind){
	cells = cellsC;
	index = ind;
}

Cell& Cell::getCell(int ind){
	return cells->at(ind);
}

int Cell::setCell(Cell cell, int ind){
	cells->at(ind) = cell;
	return 0;
}


Cell::Cell(vector<Cell> *cellsC, int ind){

	cellConstructor(cellsC, ind);
	int nGen = 20;

	int aux;
	geneticCode = vector<double>();

	for (int i = 0; i < nGen; ++i)
	{
		geneticCode.push_back((double) i);
	}
	random_shuffle(geneticCode.begin(), geneticCode.end());

	internalVar.push_back(energia_inicial);
}

Cell::Cell(){

}

Cell::~Cell(){

}

int Cell::go(Antigen antigen){

	double energia_ann = 0;

	vector<bool> aux = antigen.getValueBool();
	for (int i = 0; i < geneticCode.size(); ++i)
	{
		if (aux[i]){
			for (int j = 0; j < geneticCode.size(); ++j){
				if (geneticCode[j] == i){
					energia_ann += maximo_aporte - (toxicidad_incremental * j);
				}
			}
		}
	}

	int prev, next, total = cells->size();

	prev = (index == 0) ? total - 1 : index - 1;
	next = (index == total - 1) ? 0 : index + 1;

	internalVar[0] = internalVar[0] + energia_ann - consumo_energia_basal;
	if (internalVar[0] >= energia_maxima) internalVar[0] = energia_maxima;
	if (internalVar[0] < 0) internalVar[0] = 0;

	//Metabolismo



	return 0;
}

vector <double> Cell::getGeneticCode(){
	return geneticCode;
}

int Cell::setInternalVar(double var, int ind){
	internalVar[ind] == var;
	return 0;
}	

double Cell::getInternalVar(int ind){
	return internalVar[ind];
}	