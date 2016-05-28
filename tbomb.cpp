#include "tanim.h"
#include <allegro.h>

/////////////////////////////////////////////////
// Tbomb::Tbomb()
// Tbomb sinifinin constructor'i
// dˆrt  yˆndeki sinirlari sifirliyor
// BITMAP leri y¸kl¸yor
Tbomb::Tbomb()
:Tobj(0,0) //x=0;y=0
{
	xilimit=0;
	xglimit=0;
	yilimit=0;
	yglimit=0;
	face=al_load_bitmap(BMP_BOMB);
	fire=al_load_bitmap(BMP_FIRE);
}

/////////////////////////////////////////////////
// Tbomb::~Tbomb() :
// Tbomb sinifinin destructor'i
// ayirdigi BITMAP* leri siliyor
Tbomb::~Tbomb()
{
	al_destroy_bitmap(fire);
}

/////////////////////////////////////////////////
// Tbomb::explode() :
// alevleri Áiziyor
// danger seviyesini d¸s¸r¸yor
// ve menzildeki duvarlari yikip
// adamlari ˆld¸r¸yor.
void Tbomb::explode()
{
	if (owner->x==x && owner->y==y) owner->dead=true;
	array->settype(x,y,TYPE_FREE);
	array->setchar(x,y,array->bmp_free);
	//TODO:
	//blit(fire, screen,0,0,x*16,y*16,16,16);
	setlimits();
	
	for (char i=1; i<=owner->bomb_length; i++)
	{
		DELAY(40);
		//------x-ileri--------
		if (i<=xilimit)
	 	{
			if (array->gettype(x+i,y)!=TYPE_BOMB)
				;//blit(fire, screen,0,0,(x+i)*16,y*16,16,16);
		}
		//------x-geri---------
   	if (i<=xglimit)
	 	{
			if (array->gettype(x-i,y)!=TYPE_BOMB)
				;//blit(fire, screen,0,0,(x-i)*16,y*16,16,16);
		}
		//------y-ileri--------
   	if (i<=yilimit)
	 	{
		 	if (array->gettype(x,y+i)!=TYPE_BOMB)
				;//blit(fire, screen,0,0,x*16,(y+i)*16,16,16);
		}
		//------y-geri---------
   	if (i<=yglimit)
	 	{
			if (array->gettype(x,y-i)!=TYPE_BOMB)
				;//blit(fire, screen,0,0,x*16,(y-i)*16,16,16);
		}
	}

	Tobj *o;
	//blit(array->bmp_free, screen,0,0,x*16,y*16,16,16);

	for (char i=1; i<=owner->bomb_length; i++)
	{
		//--------x-ileri-------------

		char at=array->gettype(x+i,y);
		if (i<=xilimit)
	 	{
			if ((at==TYPE_UPLAYER) || (at==TYPE_AIPLAYER))
			{
				o=array->getobj(x+i,y);
				((Tplayer *)o)->dead=true;
			}
			else if (at!=TYPE_BOMB)
				;//blit(array->bmp_free, screen,0,0,(x+i)*16,y*16,16,16);
		}
		else if (xilimit==(i-1) && at==TYPE_STONE)
		{
			array->settype(x+i,y,TYPE_FREE);
			array->setchar(x+i,y,array->bmp_free);
			array->setdanger(x+i,y,0);
			//blit(array->bmp_free, screen,0,0,(x+i)*16,y*16,16,16);
		}

		//--------x-geri--------------

		at=array->gettype(x-i,y);
		if (i<=xglimit)
	 	{
			if ((at==TYPE_UPLAYER) || (at==TYPE_AIPLAYER))
			{
				o=array->getobj(x-i,y);
				((Tplayer *)o)->dead=true;
			}
			else if (at!=TYPE_BOMB)
				;//blit(array->bmp_free, screen,0,0,(x-i)*16,y*16,16,16);
		}
		else if (xglimit==(i-1) && at==TYPE_STONE)
		{
			array->settype(x-i,y,TYPE_FREE);
			array->setchar(x-i,y,array->bmp_free);
			array->setdanger(x-i,y,0);
			//blit(array->bmp_free, screen,0,0,(x-i)*16,y*16,16,16);
		}

		//--------y-ileri-------------

		at=array->gettype(x,y+i);
		if (i<=yilimit)
	 	{
			if ((at==TYPE_UPLAYER) || (at==TYPE_AIPLAYER))
			{
				o=array->getobj(x,y+i);
				((Tplayer *)o)->dead=true;
			}
			else if (at!=TYPE_BOMB)
				;//blit(array->bmp_free, screen,0,0,x*16,(y+i)*16,16,16);
		}
		else if (yilimit==(i-1) && at==TYPE_STONE)
		{
			array->settype(x,y+i,TYPE_FREE);
			array->setchar(x,y+i,array->bmp_free);
			array->setdanger(x,y+i,0);
			//blit(array->bmp_free, screen,0,0,x*16,(y+i)*16,16,16);
		}

		//--------y-geri--------------

		at=array->gettype(x,y-i);
		if (i<=yglimit)
	 	{
			if ((at==TYPE_UPLAYER) || (at==TYPE_AIPLAYER))
			{
				o=array->getobj(x,y-i);
				((Tplayer *)o)->dead=true;
			}
			else if (at!=TYPE_BOMB)
				;//blit(array->bmp_free, screen,0,0,x*16,(y-i)*16,16,16);
		}
		else if (yglimit==(i-1) && at==TYPE_STONE)
		{
			array->settype(x,y-i,TYPE_FREE);
			array->setchar(x,y-i,array->bmp_free);
			array->setdanger(x,y-i,0);
			//blit(array->bmp_free, screen,0,0,x*16,(y-i)*16,16,16);
		}
	}

	cleardanger();

	xilimit=0;
	xglimit=0;
	yilimit=0;
	yglimit=0;
}

/////////////////////////////////////////////////
// void Tbomb::markdanger() :
// bombançn dîrt yîndeki sçnçrlarçna kadar danger
// seviyesini dÅzgÅn azalacak üekilde arttçrçyor
void Tbomb::markdanger()
{
	unsigned char d;
	array->incdanger(x,y,owner->bomb_length+1);

	for (unsigned char i=1; i<=owner->bomb_length; i++)
	{
		d=owner->bomb_length-i+1;

		//--------------x-ileri----------
		if (i<=xilimit) array->incdanger(x+i,y,d);

		//--------------x-geri-----------
		if (i<=xglimit) array->incdanger(x-i,y,d);

		//--------------y-ileri----------
		if (i<=yilimit) array->incdanger(x,y+i,d);

		//--------------y-geri-----------
		if (i<=yglimit) array->incdanger(x,y-i,d);
	}
}

/////////////////////////////////////////////////
// void Tbomb::cleardanger()
// bombançn dîrt yîndeki sçnçrlarçna kadar danger
// seviyesini dÅzgÅn azalacak üekilde azaltçyor
void Tbomb::cleardanger()
{
	unsigned char d;
	array->decdanger(x,y,owner->bomb_length+1);

	for (unsigned char i=1; i<=owner->bomb_length; i++)
	{
		d=owner->bomb_length-i+1;

		//--------------x-ileri----------
		if (i<=xilimit && array->getdanger(x+i,y)!=0) array->decdanger(x+i,y,d);

		//--------------x-geri-----------
		if (i<=xglimit && array->getdanger(x-i,y)!=0) array->decdanger(x-i,y,d);

		//--------------y-ileri----------
		if (i<=yilimit && array->getdanger(x,y+i)!=0) array->decdanger(x,y+i,d);

		//--------------y-geri-----------
		if (i<=yglimit && array->getdanger(x,y-i)!=0) array->decdanger(x,y-i,d);
	}
}

/////////////////////////////////////////////////
// void Tbomb::setlimits() :
// bombançn dîrt yîndeki sçnçrlarçnç buluyor ve
// bombançn xilimit, xglimit, yilimit, yglimit
// Åye deßiükenlerine atçyor
void Tbomb::setlimits()
{
	bool xibos,xgbos,yibos,ygbos;
	xibos=xgbos=yibos=ygbos=true;

	xilimit=0;
	xglimit=0;
	yilimit=0;
	yglimit=0;

	for (unsigned char i=1; i<=owner->bomb_length; i++)
	{
		char at;
		//--------------x-ileri----------
		at=array->gettype(x+i,y);
		if (xibos==true)
		{
			if (at<=TYPE_EMPTY || at==TYPE_BOMB) xilimit+=1;
			else xibos=false;
		}

		//--------------x-geri-----------
		at=array->gettype(x-i,y);
		if (xgbos==true)
		{
			if (at<=TYPE_EMPTY || at==TYPE_BOMB) xglimit+=1;
			else xgbos=false;
		}

		//--------------y-ileri----------
		at=array->gettype(x,y+i);
		if (yibos==true)
		{
			if (at<=TYPE_EMPTY || at==TYPE_BOMB) yilimit+=1;
			else yibos=false;
		}

		//--------------y-geri-----------
		at=array->gettype(x,y-i);
		if (ygbos==true)
		{
			if (at<=TYPE_EMPTY || at==TYPE_BOMB) yglimit+=1;
			else ygbos=false;
		}
	}
}
