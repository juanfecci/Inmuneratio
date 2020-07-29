#include "Population.h"
#include "Antigen.h"
#include "Cell.h"
#include "Administrator.h"

//Crear create Cell

template <class CellT, class AdminT>
double Population<CellT, AdminT>::penalizacion = 100;

template <class CellT, class AdminT>
double Population<CellT, AdminT>::razon_produccion = 0.7;

template <class CellT, class AdminT>
void Population<CellT, AdminT>::populationConstructor(int nCell, AdminT *admin){
	administrator = admin;
	for (int i = 0; i < nCell; ++i)
	{
		CellT aux = CellT(&cells, i);
		cells.push_back(aux);
	}
}

template <class CellT, class AdminT>
Population<CellT, AdminT>::Population(int nCell, AdminT *admin){

	populationConstructor(nCell, admin);

	//energia promedio, numero celulas
	stats = vector<double>(2,0);
}

template <class CellT, class AdminT>
Population<CellT, AdminT>::Population(){
	
}

template <class CellT, class AdminT>
Population<CellT, AdminT>::~Population(){
	
}

template <class CellT, class AdminT>
int Population<CellT, AdminT>::go(vector<Antigen> antigens){

	stats = vector<double>(2,0);

	double energia;
	int numerp;
	int sizeV;
	for(Antigen antigen: antigens){

		for (int i = 0; i < cells.size(); ++i)
		{
			cells[i].go(antigen);
			sizeV = cells[i].getGeneticCode().size();

			if (cells[i].getInternalVar(0) > 0){
				stats[0] += cells[i].getInternalVar(0);
				stats[1] += 1;
			}
		}	

		/*
		//Penalizacion
		vector<double> vec1, vec2, vec3;
		int fin = cells.size() - 1;
		
		for (int i = 0; i < cells.size(); ++i)
		{
			if (cells[i].internalVar[0] == 0) continue;
			vec2 = cells[i].getGeneticCode();

			// Down

			if (i != 0){
				if (cells[i-1].internalVar[0] != 0){
					vec1 = cells[i-1].getGeneticCode();	
					int sum = 0;
					for (int j = 0; j < sizeV; ++j) if (vec1[j] == vec2[j]) sum++;
					if (sum >= sizeV - 10){
						cells[i].internalVar[0] -= penalizacion;
					}	
				}
			} 

			else if (cells[fin].internalVar[0] != 0){
				vec1 = cells[fin].getGeneticCode();
				int sum = 0;
				for (int j = 0; j < sizeV; ++j) if (vec1[j] == vec2[j]) sum++;
				if (sum >= sizeV - 10){
					cells[i].internalVar[0] -= penalizacion;
				}
			}

			//Up

			if (i != fin) {
				if (cells[i-1].internalVar[0] != 0){
					vec3 = cells[i+1].getGeneticCode();	
					int sum = 0;
					for (int j = 0; j < sizeV; ++j) if (vec3[j] == vec2[j]) sum++;
					if (sum >= sizeV - 10){
						cells[i].internalVar[0] -= penalizacion;
					}			
				}
				
			}

			else if (cells[0].internalVar[0] != 0){
				vec3 = cells[0].getGeneticCode();
				int sum = 0;
				for (int j = 0; j < sizeV; ++j) if (vec3[j] == vec2[j]) sum++;
				if (sum >= sizeV - 10){
					cells[i].internalVar[0] -= penalizacion;
				}			
			} 			

		}

		*/


	}

	//cout << stats[0] << "  +  " << stats[1] << endl;

	return 0;
}

template <class CellT, class AdminT>
CellT* Population<CellT, AdminT>::getCell(int ind){
	return &(cells.at(ind));
}

template <class CellT, class AdminT>
int Population<CellT, AdminT>::setCell(CellT cell, int ind){
	cells[ind] = cell;
	return 0;
}

template <class CellT, class AdminT>
int Population<CellT, AdminT>::sendCell(){
	return 0;
}

template <class CellT, class AdminT>
double Population<CellT, AdminT>::getStats(int ind){
	return stats[ind];
}

template class Population<Cell, Administrator>;