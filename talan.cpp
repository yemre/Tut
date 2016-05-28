#include "tanim.h"
#include "talan.h"

Talan::Talan(unsigned char x, unsigned char y)
{
	this->maxx=x;
	this->maxy=y;
	obja=new Tobj*[(maxy+1)*(maxx+1)];
	typea=new unsigned char[(maxy+1)*(maxx+1)];
	dangera=new unsigned char[(maxy+1)*(maxx+1)];
	chara=new ALLEGRO_BITMAP*[(maxy+1)*(maxx+1)];
}

Talan::~Talan()
{
	delete []obja;
	delete typea;
	delete []chara;
	delete dangera;
}

unsigned char Talan::getmaxx()
{
	return maxx;
}

unsigned char Talan::getmaxy()
{
	return maxy;
}

char Talan::gettype(unsigned char x, unsigned char y)
{
	return typea[(x-1)+(y-1)*maxx];
}

char Talan::getdanger(unsigned char x, unsigned char y)
{
	return dangera[(x-1)+(y-1)*maxx];
}

ALLEGRO_BITMAP *Talan::getchar(unsigned char x, unsigned char y)
{
	return chara[(x-1)+(y-1)*maxx];
}

Tobj *Talan::getobj(unsigned char x, unsigned char y)
{
	return obja[(x-1)+(y-1)*maxx];
}

void Talan::settype(unsigned char x, unsigned char y, unsigned char type)
{
	typea[(x-1)+(y-1)*maxx]=type;
}

void Talan::setdanger(unsigned char x, unsigned char y, char danger)
{
	dangera[(x-1)+(y-1)*maxx]=danger;
}

void Talan::setchar(unsigned char x, unsigned char y, ALLEGRO_BITMAP *ch)
{
	chara[(x-1)+(y-1)*maxx]=ch;
}

void Talan::putobj(unsigned char x, unsigned char y, Tobj *op)
{
	obja[(x-1)+(y-1)*maxx]=op;
}

void Talan::incdanger(unsigned char x, unsigned char y)
{
	dangera[(x-1)+(y-1)*maxx]+=1;
}

void Talan::incdanger(unsigned char x, unsigned char y, unsigned char d)
{
	dangera[(x-1)+(y-1)*maxx]+=d;
}

void Talan::decdanger(unsigned char x, unsigned char y)
{
	dangera[(x-1)+(y-1)*maxx]-=1;
}

void Talan::decdanger(unsigned char x, unsigned char y, unsigned char d)
{
	dangera[(x-1)+(y-1)*maxx]-=d;
}

