#include "tanim.h"
#include "uplayer.h"

Uplayer::Uplayer(unsigned char id, unsigned char x, unsigned char y, Talan *a)
:Tplayer(id,x,y,a)
{
	speed=5; //default speed
	etime=3; //default explode time
	max_bomb=5; //default max_bomb
	bomb_length=4; //default bomb_length

	parse_ini();

	Bomb=new Tbomb[max_bomb];
	for (unsigned char i=0; i<=max_bomb; i++)
	{
		Bomb[i].owner=this;
		Bomb[i].rtime=0;
		Bomb[i].array=array;
	}
	face=al_load_bitmap(BMP_UPLAYER1);
	array->settype(x,y,TYPE_UPLAYER);
}

Uplayer::~Uplayer()
{
	delete Bomb;
}

void Uplayer::parse_ini()
{
	char *lvalue=new char[15];
	char *rvaluec=new char[15];
	int rvaluei;
	std::ifstream ftutini;
	ftutini.open(INIFILE,std::ios::in);
 	if (ftutini.rdstate())
	{
		std::cerr << "dosya açma hatasi" << std::endl;
		exit(-1);
	}
	ftutini >> lvalue;
	if (strcmp(lvalue,"[tut]")!=0)
	{
		std::cerr << INIFILE <<" dosyasinin ilk satiri \"[tut]\" degil" << std::endl;
		exit(-1);
	}

	ftutini >> lvalue;

	while (!ftutini.eof() && strcmp(lvalue,"[uplayer]")!=0)
	{
//		cerr << lvalue << endl;
		ftutini >> lvalue;
	}
//	ftutini.clear();

	while (!ftutini.eof() || lvalue[0]=='[')
	{
		ftutini >> lvalue;
		if (strcmp(lvalue,"hareket_hizi")==0)
		{
			ftutini >> rvaluei;
			std::cerr << lvalue <<"="<< rvaluei << std::endl;
			speed=(unsigned char)rvaluei;
		}
		else if (strcmp(lvalue,"bitmap")==0)
		{
			ftutini >> rvaluec;
			std::cerr << lvalue <<"="<< rvaluec << std::endl;
		}
		else if (strcmp(lvalue,"bomba_menzili")==0)
		{
			ftutini >> rvaluei;
			std::cerr << lvalue <<"="<< rvaluei << std::endl;
			bomb_length=(unsigned char)rvaluei;
		}
		else if (strcmp(lvalue,"bomba_sayisi")==0)
		{
			ftutini >> rvaluei;
			std::cerr << lvalue <<"="<< rvaluei << std::endl;
			max_bomb=(unsigned char)rvaluei;
		}
		else if (strcmp(lvalue,"bomba_suresi")==0)
		{
			ftutini >> rvaluei;
			std::cerr << lvalue <<"="<< rvaluei << std::endl;
			etime=(unsigned char)rvaluei;
		}
	}
	ftutini.close();
}

void Uplayer::go(unsigned char tus)
{
	extern Tut *tut;
	TIME_T h;

	GETTIME(&h);
	int tt=SECOND(h);

	array->settype(x,y,dtype);
	array->setchar(x,y,dbmp);
	array->putobj(x,y,dobj);
	
	hide();

	switch (tus){
	case 't':	if ((tt>=last_move+speed) && (array->gettype(x,y-1)<=TYPE_EMPTY))
						{
							y-=1;
							last_move=tt;
						}
						break;
	case 'g':	if ((tt>=last_move+speed) && (array->gettype(x,y+1)<=TYPE_EMPTY))
						{
							y+=1;
							last_move=tt;
						}
						break;
	case 'f':	if ((tt>=last_move+speed) && (array->gettype(x-1,y)<=TYPE_EMPTY))
						{
							x-=1;
							last_move=tt;
						}
						break;
	case 'h':	if ((tt>=last_move+speed) && (array->gettype(x+1,y)<=TYPE_EMPTY))
						{
							x+=1;
							last_move=tt;
						}
						break;
	case 'q':	lay_bomb();
						break;
	case 'p':	show();
						//TODO:
						//textout(screen,font,"mola",300,460,makecol(255,255,255));
						while	(GETCH()!='p');
						//textout(screen,font,"    ",300,460,makecol(0,0,0));
						hide();
						break;
	case 'o':	if (((Aiplayer *)tut->plist[tut->maxaiplayer])->stun==true)
						{
							for (unsigned char i=0; i<=tut->maxaiplayer; i++) ((Aiplayer *)tut->plist[i])->stun=false;
							//textout(screen,font,"   ",100,460,makecol(0,0,0));
						}
						else
						{
							for (unsigned char i=0; i<=tut->maxaiplayer; i++) ((Aiplayer *)tut->plist[i])->stun=true;
							//textout(screen,font,"don",100,460,makecol(255,255,255));
						}
						break;
	}
	dtype=array->gettype(x,y);
	dbmp=array->getchar(x,y);
	dobj=array->getobj(x,y);
	array->settype(x,y,TYPE_UPLAYER);
	array->setchar(x,y,face);
	array->putobj(x,y,this);
	show();
}

void Uplayer::lay_bomb()
{
	TIME_T t;
	bool buldu;
	buldu=false;

	if (array->gettype(x,y)<=TYPE_EMPTY)
	{
		for (int i=0; i<max_bomb; i++)
		{
			if ((buldu==false) && (Bomb[i].rtime==0))
			{
				GETTIME(&t);

				Bomb[i].rtime=etime;
				Bomb[i].ltime=SECOND(t);
				Bomb[i].last_check=SECOND(t);
				Bomb[i].x=x;
				Bomb[i].y=y;
				array->settype(x,y,TYPE_BOMB);
				array->setchar(x,y,Bomb[i].face);

				buldu=true;
				Bomb[i].setlimits();
				Bomb[i].markdanger();
			}
		}
	}
}

void Uplayer::chk_bomb()
{
	TIME_T t;
	GETTIME(&t);
	for (int i=0; i<max_bomb; i++)
	{
		if (Bomb[i].rtime!=0)
		{
			if (Bomb[i].last_check < SECOND(t))
			   Bomb[i].rtime = Bomb[i].rtime-(SECOND(t)-Bomb[i].last_check);

			Bomb[i].last_check=SECOND(t);

			if (Bomb[i].rtime<=0)
			{
				Bomb[i].rtime=0;
				Bomb[i].explode();
			}
		}
	}
}
