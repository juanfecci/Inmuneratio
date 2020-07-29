#include "Antigen.h"

Antigen::Antigen(bool type, int step, vector<int> value_int, vector<bool> value_bool, vector<string> value_string){
	this->type = type;
	this->step = step;
	this->value_int = value_int;
	this->value_bool = value_bool;
	this->value_string = value_string;
}

Antigen::~Antigen(){

}

bool Antigen::getType(){
	return type;
}

int Antigen::getStep(){
	return step;
}

vector<int> Antigen::getValueInt(){
	return value_int;
}

vector<bool> Antigen::getValueBool(){
	return value_bool;
}

vector<string> Antigen::getValueString(){
	return value_string;
}
