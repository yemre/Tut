#ifndef __talan_h__
#define __talan_h__

#include <allegro.h>
#include "tanim.h"

class Talan
{
	private:

	Tobj **obja;
	unsigned char *typea;
	unsigned char *dangera;
	ALLEGRO_BITMAP **chara;
	unsigned char maxx;
	unsigned char maxy;

	protected:

	char file_wall[13];
	char file_stone[13];
	char file_free[13];

	public:

	ALLEGRO_BITMAP *bmp_wall;
	ALLEGRO_BITMAP *bmp_stone;
	ALLEGRO_BITMAP *bmp_free;

	Talan(unsigned char x,unsigned char y);
	virtual ~Talan();
	unsigned char getmaxx();
	unsigned char getmaxy();
	virtual void draw()=0;
	char gettype(unsigned char x, unsigned char y);
	char getdanger(unsigned char x, unsigned char y);
	ALLEGRO_BITMAP *getchar(unsigned char x, unsigned char y);
	Tobj *getobj(unsigned char x, unsigned char y);
	void settype(unsigned char x, unsigned char y, unsigned char type);
	void setdanger(unsigned char x, unsigned char y, char danger);
	void setchar(unsigned char x, unsigned char y, ALLEGRO_BITMAP *ch);
	void putobj(unsigned char x, unsigned char y, Tobj *op);
	void incdanger(unsigned char x, unsigned char y);
	void incdanger(unsigned char x, unsigned char y, unsigned char d);
	void decdanger(unsigned char x, unsigned char y);
	void decdanger(unsigned char x, unsigned char y, unsigned char d);
	virtual void fill(unsigned int seed)=0;
};


#endif
