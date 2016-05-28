#ifndef __tini_h__
#define __tini_h__

#include "tanim.h"
#include <fstream>

class Tini{
	public:
	
	std::ifstream ftutini;

	Tini();
	~Tini();
	void parse();
};

#endif
