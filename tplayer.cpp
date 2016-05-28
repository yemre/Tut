#include "tanim.h"
#include "tplayer.h"

Tplayer::Tplayer(unsigned char id, unsigned char x, unsigned char y, Talan* array)
:Tobj(x,y)
{
	TIME_T t;
	GETTIME(&t);
	last_move=SECOND(t);
	this->array=array;
	this->id=id;
	dbmp=al_load_bitmap(BMP_EMPTY);
	dtype=TYPE_FREE;
	ddanger=0;
	dobj=new Tobj(0,0);
	dead=false;
}

Tplayer::~Tplayer()
{
	al_destroy_bitmap(dbmp);
}

void Tplayer::show()
{
	//TODO:fix blit
	//blit(face, screen,0,0,x*16,y*16,16,16);
}

void Tplayer::hide()
{
	//TODO:fix blit
	//blit(dbmp, screen,0,0,x*16,y*16,16,16);
}

