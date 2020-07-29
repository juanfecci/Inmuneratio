#include "Administrator.h"

Administrator::Administrator(){
	population1 = Population<Cell, Administrator>(100, this);
	start = clock();
	Npaquete = 0;
	verif = false;
	//thread thSniffer(snifferRun);
	//thread thDanger(dangerRun);

	//threads.push_back(thread(snifferRun));
	//threads.push_back(thread(dangerRun));

}

Administrator::~Administrator(){

}

int Administrator::updateResponse(int option){
	return 0;
}

int Administrator::updateCell(int idHost, Cell cell, int option){
	return 0;
}

Cell Administrator::getCell(){
	return Cell();
}

int Administrator::startConnection(){
	return 0;
}

int Administrator::finish(){
	return 0;
}

int Administrator::main(){
	while(true){
		vector<Antigen> anti = getSnifferAntigens();

		for (Antigen antigen: anti){

			vector<Antigen> aux;
			aux.push_back(antigen);

			population1.go(aux);

			if (verif && population1.getStats(0) <= 25000){
				cout << "---------------------" << endl;
				cout << "Se presenta amenaza:" << " Energía: " << population1.getStats(0) << " -- Número de células: " << population1.getStats(1) << endl;
				cout << "---------------------" << endl;
				verif = false;
			}
			
			double duration = (clock() - start) / (double) CLOCKS_PER_SEC;
			if (duration > 5){
				verif = true;
				cout << "Energía de la poblacion: " << population1.getStats(0) << " -- Número de células vivas: " << population1.getStats(1) << endl;
				start = clock();
			}
		}		
	}
	return 0;
}

int Administrator::startHost(){
	return 0;
}

int Administrator::addHost(){
	return 0;
}

int Administrator::quit(){
	return 0;
}