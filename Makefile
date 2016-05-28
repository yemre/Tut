CXXFLAGS=-Wall -Werror -O2 -ggdb -I /usr/include/allegro5
CXX=g++
DEST=/usr/local/games
MAKE=make
ALLEGROLIBS = $(shell pkg-config --libs allegro-5.0)
ALLEGROINCS = $(shell pkg-config --cflags allegro-5.0) 

#export CXXFLAGS

MODULES=tobj.o talan.o alan.o tplayer.o uplayer.o aiplayer.o tut.o tbomb.o \
	tini.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(ALLEGROINCS) -c $<

all:
	echo $(ALLEGROLIBS)
	echo $(ALLEGROINCS)
	rm -f atut
	$(MAKE) atut

atut: $(MODULES)
	$(CXX) main.cpp -o atut $(CXXFLAGS) $(ALLEGROLIBS) $(ALLEGROINCS) $(MODULES)
#	chmod u+s atut

install: all
	install -c -m755 atut $(DEST)/bin

clean: 
	rm -f *.o atut
