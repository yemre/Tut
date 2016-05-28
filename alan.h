#ifndef __alan_h__
#define __alan_h__

#include "talan.h"

class Alan: public Talan
{
	public:

	Alan(unsigned char x, unsigned char y);
	~Alan();
	void fill(unsigned int seed);
	void draw();
};

#endif
