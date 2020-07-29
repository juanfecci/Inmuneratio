#ifndef CELL_H
#define CELL_H

class ADTCell {

	public:
		virtual void setup() = 0;
		virtual void go() = 0;
		virtual void setGenetic() = 0;
};

#endif