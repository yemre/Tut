#include "tanim.h"
//#include "tobj.h"
#include <allegro_primitives.h>

Tobj::Tobj(unsigned char x, unsigned char y)
{
	this->x=x;
	this->y=y;
	face = NULL;
}

Tobj::~Tobj()
{
	al_destroy_bitmap(face);
}
