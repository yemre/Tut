#ifndef __tut_h__
#define __tut_h__

//#include "alan.h"
//#include "uplayer.h"
//#include "aiplayer.h"
#include "tanim.h"

class Tut
{
	public:

	unsigned int maxaiplayer;
	unsigned int maxuplayer;
	class Tplayer **plist;
	class Alan *a;
	class Uplayer *up;
	class Aiplayer *aip;
	char versionstr[64];
	unsigned int looser;

	Tut();
	~Tut();
	unsigned int loop();
	void quit();
};

#endif
