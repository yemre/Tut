#include "tanim.h"

Tut *tut;

int main()
{
//---------allegro---------------------
	al_init();
	//TODO:
	//set_color_depth(16);
	//set_gfx_mode(GFX_AUTODETECT/*GFX_VESA1*/, 640, 480, 0,0);
//---------allegro-son-----------------

	tut=new Tut;
	strncpy(tut->versionstr, "atut! 0.0.5.1 26/1/2000 Zebani", 64);
	tut->looser=tut->loop();

	//clear(screen);
	//set_gfx_mode(GFX_TEXT,80,25,0,0);

	tut->quit();
	return 0;
}
