#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <bits/stdc++.h>

#include "Population.h"
#include "Cell.h"
#include "Response.h"
#include "Sniffer.h"
#include "Danger.h"

using namespace std;


class Administrator{
private:
	queue<vector <double> > cellsQueue;
	Population<Cell, Administrator> population1;

	//vector<thread> threads;

	//Pueden haber aqui más poblaciones, pero en el adt no hay referencia a ello

	//variavles especificas de EIA

	int salida_banda;
	int factor_aumento_alerta;
	int factor_disminucion_alerta;
	int umbral_alerta;
	bool verif;

	int Npaquete;
	clock_t start;

	bool ataque_detectado;


	//Response response;

	int startHost();
	int addHost();
	int quit();

public:
	Administrator();
	~Administrator();
	int updateResponse(int option);
	int updateCell(int idHost, Cell cell, int option);
	Cell getCell();
	int startConnection();
	int finish();
	int main();
};

#endif