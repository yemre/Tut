#ifndef __aiplayer_h__
#define __aiplayer_h__

#include "tplayer.h"

class Aiplayer: public Tplayer{
	public:
	bool stun;

	Aiplayer(unsigned char id, unsigned char x, unsigned char y, Talan *a);
	~Aiplayer();
	void go(unsigned char hx, unsigned char hy);

	private:
	
	void flee();
	void follow(unsigned char &hx, unsigned char &hy);
};

#endif
