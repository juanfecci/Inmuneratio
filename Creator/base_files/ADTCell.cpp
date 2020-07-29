#include "{0}.h"

void {0}::cellConstructor(vector<{0}*> *cellsC, int ind){{
	cells = cellsC;
	index = ind;
}}

void {0}::cellConstructor2(vector<{0}*> *cellsC, int ind, vector<double> genetic){{
	cells = cellsC;
	index = ind;
	geneticCode = genetic;
}}

{0} *{0}::getCell(int ind){{
	return cells->at(ind);
}}

int {0}::setCell({0} *cell, int ind){{
	cells->at(ind) = cell;
	return 0;
}}

vector <double> {0}::getGeneticCode(){{
	return geneticCode;
}}

int {0}::setInternalVar(double var, int ind){{
	internalVar[ind] == var;
	return 0;
}}	

double {0}::getInternalVar(int ind){{
	return internalVar[ind];
}}	