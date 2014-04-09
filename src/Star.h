#ifndef STAR_H
#define STAR_H

#include "Planet.h"

class Star : public Planet
{
public:
	Star() : Planet() {};
	void draw();
	char * getDisplayText();
private:
};

#endif