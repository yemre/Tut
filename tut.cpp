#include "tanim.h"

Tut::Tut()
{
	maxuplayer=1;
	maxaiplayer=0;
	looser=0;
	a=new Alan(39,27);

	plist=new Tplayer*[maxuplayer+1];

	up=new Uplayer(1,4,4,a);
	aip=new Aiplayer(0,36,26,a);

	plist[up->id]=up;
	plist[aip->id]=aip;

	a->fill(1);
	a->draw();

	up->show();
	aip->show();
}

Tut::~Tut()
{
	delete []plist;
	delete a;
	delete up;
	delete aip;
}

unsigned int Tut::loop()
{
	unsigned int i;
	unsigned char tus;
	tus=0;

	while (tus!=27)
	{
		for (i=maxaiplayer+1; i<=maxuplayer; i++)
			((Uplayer *)plist[i])->chk_bomb();

		//TODO:
		if (false)//KBHIT()!=0)
		{
			//tus=GETCH();
			for (i=maxaiplayer+1; i<=maxuplayer; i++)
				((Uplayer *)plist[i])->go(tus);
		}

		for (i=0; i<=maxuplayer; i++)
		{
			if (((Tplayer *)plist[i])->dead==true)
				return ((Tplayer *)plist[i])->id;
		}

		for (i=0; i<=maxaiplayer; i++)
			((Aiplayer *)plist[i])->go(up->x,up->y);
	}
	return 0;    
}

void Tut::quit()
{
	//TODO:
	//std::cout << allegro_id << std::endl;
	std::cout << versionstr << std::endl;
	std::cout << "kaybeden : " << this->looser << std::endl;
	exit(this->looser);
}
