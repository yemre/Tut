#ifndef __tanim_h__
#define __tanim_h__

#include <allegro.h>
#include <stdio.h>
#include <cstdlib>
//#include <stream>
#include <iostream>
#include <fstream>

#ifdef __DOS__
#warning Compiling for DOS
#include <dos.h>
#include <conio.h>
#include <dosalleg.h>
typedef struct time_t TIME_T;

#define GETTIME(t) gettime(t)
#define SECOND(t) (((t.ti_hour*60+t.ti_min)*60+t.ti_sec)*100+t.ti_hund)
#define GETCH() getch()
#define DELAY(t) delay(t)
#define KBHIT() kbhit()
#endif

//#ifdef __GNU__
//#warning Compiling for Linux
#include <linux/types.h>
#include <time.h>

typedef time_t TIME_T;

#define GETTIME(t) time(t)
#define SECOND(t) (t)
#define GETCH() getchar()
#define DELAY(t) sleep(t)
#define KBHIT() keypressed()
//#endif

#define INIFILE "tut.ini"

#define TYPE_BOMB 127
#define TYPE_WALL 126
#define TYPE_STONE 125
#define TYPE_EMPTY 100
#define TYPE_FREE 70
#define TYPE_AIPLAYER 1
#define TYPE_UPLAYER 0

#define BMP_UPLAYER1 "p1.bmp"
#define BMP_AIPLAYER1 "a1.bmp"
#define BMP_BOMB "bomba.bmp"
#define BMP_FIRE "alev.bmp"
#define BMP_EMPTY "bos.bmp"
#define BMP_WALL "duvar.bmp"
#define BMP_STONE "tas.bmp"

#include "tobj.h"
#include "tut.h"
#include "talan.h"
#include "alan.h"
#include "tplayer.h"
#include "tbomb.h"
#include "uplayer.h"
#include "aiplayer.h"
#include "tini.h"
#endif
