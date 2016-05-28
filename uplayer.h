#ifndef __uplayer_h__
#define __uplayer_h__

#include "tplayer.h"
#include "tbomb.h"

class Uplayer : public Tplayer{
	private:
	class Tbomb *Bomb;
	unsigned char etime;
	unsigned char max_bomb;

	void parse_ini();

	public:

	unsigned char bomb_length;

	Uplayer(unsigned char id, unsigned char x, unsigned char y, Talan *a);
	~Uplayer();
	void go(unsigned char tus);
	void lay_bomb();
	void chk_bomb();
};

#endif
