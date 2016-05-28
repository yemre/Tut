#ifndef __tbomb_h__
#define __tbomb_h__

#include "uplayer.h"

class Tbomb: public Tobj
{
	public:

	unsigned char xilimit;
	unsigned char xglimit;
	unsigned char yilimit;
	unsigned char yglimit;
	int ltime;
	int rtime;
	int last_check;
	class Uplayer *owner;
	ALLEGRO_BITMAP *fire;
	Talan *array;

	Tbomb();
	~Tbomb();
	void explode();
	void markdanger();
	void cleardanger();
	void setlimits();
};

#endif
