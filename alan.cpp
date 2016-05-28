#include "tanim.h"
#include "alan.h"

Alan::Alan(unsigned char x, unsigned char y)
:Talan(x,y)
{
	strncpy(file_wall, BMP_WALL, 13);
	strncpy(file_stone, BMP_STONE, 13);
	strncpy(file_free, BMP_EMPTY, 13);
	bmp_wall=al_load_bitmap(file_wall);
	bmp_stone=al_load_bitmap(file_stone);
	bmp_free=al_load_bitmap(file_free);
}

Alan::~Alan()
{
	al_destroy_bitmap(bmp_wall);
	al_destroy_bitmap(bmp_stone);
	al_destroy_bitmap(bmp_free);
}

void Alan::draw()
{
	for (unsigned char j=1; j<=getmaxy(); j++)
	{
		for (unsigned char i=1; i<=getmaxx(); i++)
		{
			//TODO: fix blit
				if (gettype(i,j)==TYPE_WALL)
					;//blit(bmp_wall,screen,0,0,i*16,j*16,16,16);
				if (gettype(i,j)==TYPE_STONE)
					;//blit(bmp_stone,screen,0,0,i*16,j*16,16,16);
				if (gettype(i,j)==TYPE_FREE)
					;//blit(bmp_free,screen,0,0,i*16,j*16,16,16);
		}
	}
}

void Alan::fill(unsigned int seed)
{
	int i,j;
	for (j=1; j<=getmaxy(); j++)
	{
		for (i=1; i<=getmaxx(); i++)
		{
			setchar(i,j,bmp_free);
			settype(i,j,TYPE_FREE);
			setdanger(i,j,0);
		}
	}
	for (i=1; i<=getmaxx(); i++)
	{
		setchar(i,1,bmp_wall);
		settype(i,1,TYPE_WALL);
		setdanger(i,1,127);
		setchar(i,getmaxy(),bmp_wall);
		settype(i,getmaxy(),TYPE_WALL);
		setdanger(i,getmaxy(),127);
	}
	for (i=2; i<=getmaxy()-1; i++)
	{
		setchar(1,i,bmp_wall);
		settype(1,i,TYPE_WALL);
		setdanger(1,i,127);
		setchar(getmaxx(),i,bmp_wall);
		settype(getmaxx(),i,TYPE_WALL);
		setdanger(getmaxx(),i,127);
	}
	for (j=3; j<=getmaxy()-2; j+=2)
	{
   	for (i=3; i<=getmaxx()-2; i+=2)
      {
      	setchar(i,j,bmp_wall);
      	settype(i,j,TYPE_WALL);
      	setdanger(i,j,127);
      }
   }
	srand(seed);
	for (i=1; i<=100; i++)
	{
		unsigned char x=rand()%getmaxx();
		unsigned char y=rand()%getmaxy();
		if (gettype(x,y)==TYPE_FREE)
		{
			setchar(x,y,bmp_stone);
			settype(x,y,TYPE_STONE);
			setdanger(x,y,127);
		}
		else i--;
	}
}
