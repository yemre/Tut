#ifndef __tobj_h__
#define __tobj_h__

#include <allegro.h>

class Tobj{
	public:
	unsigned char x;
	unsigned char y;
	ALLEGRO_BITMAP *face;

	Tobj(unsigned char x, unsigned char y);
	~Tobj();
};

#endif
