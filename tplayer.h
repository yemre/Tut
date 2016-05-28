#ifndef __tplayer_h__
#define __tplayer_h__

#include <allegro.h>

class Tplayer: public Tobj
{
	protected:

	unsigned char ddanger;
	unsigned char speed;
	int last_move;

	public:

	ALLEGRO_BITMAP *dbmp;
	unsigned char dtype;
	Tobj *dobj;
	bool dead;
	unsigned char id;
	Talan *array;

	Tplayer(unsigned char id, unsigned char x, unsigned char y, Talan *array);
	~Tplayer();
	void show();
	void hide();
};

#endif
