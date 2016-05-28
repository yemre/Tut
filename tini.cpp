#include "tini.h"
#include "tanim.h"

using namespace std;

Tini::Tini()
{
	char *lvalue=new char[10];
	ftutini.open(INIFILE,ios::in);
 	if (ftutini.rdstate())
	{
		cerr << "dosya a‡ma hatas" << endl;
		exit(-1);
	}
	ftutini >> lvalue;
	if (strcmp(lvalue,"[tut]")!=0)
	{
		cerr << INIFILE <<" dosyasnn ilk satr \"[tut]\" de§il" << endl;
		exit(-1);
	}
}

Tini::~Tini()
{
	ftutini.close();
}

void Tini::parse()
{
	char *rvalue=new char[10];
	char *lvalue=new char[10];
	ftutini >> lvalue;

	while (!ftutini.eof() && strcmp(lvalue,"[alan]")!=0)
	{
		ftutini >> lvalue;
		cerr << lvalue << endl;
	}
	ftutini.clear();
	while (!ftutini.eof() || lvalue[0]=='[')
	{
		ftutini >> lvalue;
		if (strcmp(lvalue,"duvarbmp")==0)
		{
			ftutini >> rvalue;
			cerr << lvalue <<"="<< rvalue << endl;
		}
	}
}
