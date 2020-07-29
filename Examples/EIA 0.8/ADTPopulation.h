#ifndef POPULATION_H
#define POPULATION_H

class ADTPopulation {
public:
	virtual void setup() = 0;
	virtual void go() = 0;
	virtual void setGenetic() = 0;
};

#endif