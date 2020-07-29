#include "{0}.h"
#include "Antigen.h"
#include "{1}.h"
#include "Administrator.h"

template <class CellT, class AdminT>
{0}<CellT, AdminT>::{0}(int nCell, AdminT *admin){{

	populationConstructor(nCell, admin);

}}

template <class CellT, class AdminT>
{0}<CellT, AdminT>::{0}(){{
	
}}

template <class CellT, class AdminT>
{0}<CellT, AdminT>::~{0}(){{
	
}}

template <class CellT, class AdminT>
int {0}<CellT, AdminT>::go(vector<Antigen> antigens){{
	// Para entregar los antigenos a las celulas de forma automatica, se usa: cellsGo(antigens)
	for (Antigen antigen: antigens){{
		if (antigen.getType()){{
			//cout << "Antigeno de red" << endl;
		}}
		else{{
			//cout << "Antigeno de peligro" << endl;	
		}}
		// Para entregar los antigenos por separado a cada celula, se usa: cellsGo(antigen)
	}}
	return 0;
}}

template class {0}<{1}, Administrator>;