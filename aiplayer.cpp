#include "tanim.h"
#include "aiplayer.h"

////////////////////////////////////
// Aiplayer::Aiplayer(unsigned char id, unsigned char x, unsigned char y)
// Aiplayer snfnn constructor'
// ilk de§erleri veriyor
Aiplayer::Aiplayer(unsigned char id, unsigned char x, unsigned char y, Talan *a)
: Tplayer(id,x,y,a)
{
	speed=30; //default speed
	stun=false;
	face=al_load_bitmap(BMP_AIPLAYER1);// default face
	array->settype(x,y,TYPE_AIPLAYER);
}

////////////////////////////////////
// Aiplayer::~Aiplayer()
// Aiplayer snfnn destructor'
// Ÿimdilik boŸ
Aiplayer::~Aiplayer()
{
}

////////////////////////////////////
// void Aiplayer::go(unsigned char hx, unsigned char hy)
// tehlikede de§ilse hx,hy ye gider (follow(hx,hy))
// tehlikedeyse ka‡ar (flee())
void Aiplayer::go(unsigned char hx, unsigned char hy)
{
	extern Tut *tut;
	TIME_T h;

	GETTIME(&h);
	int tt=SECOND(h);

	if (tt>=last_move+speed && stun==false)
	{
		if ((x==hx) && (y==hy))
		{
			Tobj *o;
			o=array->getobj(hx,hy);
			((Tplayer *)o)->dead=true;
		}
		else
		{
			last_move=tt;
			hide();

			array->settype(x,y,dtype);
			array->setchar(x,y,dbmp);
			array->putobj(x,y,dobj);

			if (array->getdanger(x,y)>0)
				flee();
			else
				follow(hx,hy);

			show();
		}

		if ((x==hx) && (y==hy))
			((Tplayer *)tut->plist[(int)array->gettype(x,y)])->dead=true;

		dtype=array->gettype(x,y);
		dbmp=array->getchar(x,y);
		dobj=array->getobj(x,y);
		array->settype(x,y,TYPE_AIPLAYER);
		array->setchar(x,y,face);
		array->putobj(x,y,this);
	}
}

void Aiplayer::flee()
{
	unsigned char min_danger=255;
	unsigned char yon=5;
	if ((array->getdanger(x+1,y) < min_danger) && (array->gettype(x+1,y) <= TYPE_EMPTY))
	{
		min_danger=array->getdanger(x+1,y);
		yon=0;
	}
	if ((array->getdanger(x-1,y) < min_danger) && (array->gettype(x-1,y) <= TYPE_EMPTY))
	{
		min_danger=array->getdanger(x-1,y);
		yon=1;
	}
	if ((array->getdanger(x,y+1) < min_danger) && (array->gettype(x,y+1) <= TYPE_EMPTY))
	{
		min_danger=array->getdanger(x,y+1);
		yon=2;
	}
	if ((array->getdanger(x,y-1) < min_danger) && (array->gettype(x,y-1) <= TYPE_EMPTY))
	{
		min_danger=array->getdanger(x,y-1);
		yon=3;
	}

	if (yon==0) x+=1;
	else if (yon==1) x-=1;
	else if (yon==2) y+=1;
	else if (yon==3) y-=1;
}

void Aiplayer::follow(unsigned char &hx, unsigned char &hy)
{
	int dx=x-hx;
	int dy=y-hy;
	int ox=x;
	int oy=y;

	if (abs(dy)>abs(dx))
	{
		if (array->gettype(x,y-abs(dy)/dy)<=TYPE_EMPTY)
			y-=abs(dy)/dy;
		else if ((dx!=0) && (array->gettype(x-abs(dx)/dx,y)<=TYPE_EMPTY))
			x-=abs(dx)/dx;
	}
	else
	{
		if (array->gettype(x-abs(dx)/dx,y)<=TYPE_EMPTY)
			x-=abs(dx)/dx;
		else if ((dy!=0) && (array->gettype(x,y-abs(dy)/dy)<=TYPE_EMPTY))
			y-=abs(dy)/dy;
	}

	if (array->getdanger(x,y) > 0)
	{
		x=ox;
		y=oy;
	}
}
