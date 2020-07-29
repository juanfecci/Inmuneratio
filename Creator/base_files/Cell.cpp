#include "{0}.h"

{0}::{0}(vector<{0}*> *cellsC, int ind){{

	cellConstructor(cellsC, ind);

	
}}

{0}::{0}(vector<{0}*> *cellsC, int ind, vector<double> genetic){{

	cellConstructor2(cellsC, ind, genetic);

	
}}

{0}::{0}(){{

}}

{0}::~{0}(){{

}}

int {0}::go(Antigen antigen){{
	if (antigen.getType()){{
		//cout << "Antigeno de red" << endl;
	}}
	else{{
		//cout << "Antigeno de peligro" << endl;	
	}}
	return 0;
}}