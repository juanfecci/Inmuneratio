#include "{0}.h"
#include "Antigen.h"
#include "{1}.h"
#include "Administrator.h"
//#include "Administrator.h"

template <class CellT, class AdminT>
void {0}<CellT, AdminT>::populationConstructor(int nCell, AdminT *admin){{
	popmutex = new mutex();
	administrator = admin;
	for (int i = 0; i < nCell; ++i)
	{{
		cells.push_back(new CellT(&cells, i));
	}}
}}

template <class CellT, class AdminT>
int {0}<CellT, AdminT>::cellsGo(Antigen antigen){{
	for (CellT *cellt: cells){{
		cellt->go(antigen);
	}}
}}

template <class CellT, class AdminT>
int {0}<CellT, AdminT>::cellsGo(vector<Antigen> antigens){{
	for (Antigen antigen: antigens){{
		cellsGo(antigen);	
	}}
	
}}


template <class CellT, class AdminT>
CellT* {0}<CellT, AdminT>::getCell(int ind){{
	return cells.at(ind);
}}

template <class CellT, class AdminT>
int {0}<CellT, AdminT>::setCell(CellT *cell, int ind){{
	cells[ind] = cell;
	return 0;
}}

template <class CellT, class AdminT>
int {0}<CellT, AdminT>::sendCell(){{
	return 0;
}}

template <class CellT, class AdminT>
void {0}<CellT, AdminT>::reciveCell(vector <double> genetic){{
	cellsRecv.push_back(new CellT(&cells, -1, genetic));
}}

template <class CellT, class AdminT>
vector<CellT*> {0}<CellT, AdminT>::getRecvCells(){{
	popmutex->lock();
	vector<CellT*> aux(cellsRecv);
	cellsRecv = vector<CellT*>();
	popmutex->unlock();

	return aux;
}}

template <class CellT, class AdminT>
double {0}<CellT, AdminT>::getStats(int ind){{
	return stats[ind];
}}

template class {0}<{1}, Administrator>;