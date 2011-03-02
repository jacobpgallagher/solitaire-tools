CCFLAGS=-g -pedantic -pg -O3
LIBS=-lgmp
OBJS=solitaire.o main.o nfront.o addmod.o

all:solitaire bench alphabreaker solpipe numbreaker matcher hasher dumper

solitaire:$(OBJS)
	g++ $(CCFLAGS) -lncurses  $(OBJS) -o solitaire 

solpipe:solpipe.cc solitaire.o addmod.o
	g++ $(CCFLAGS) solpipe.cc solitaire.o addmod.o -o solpipe

main.o:main.cc nfront.h solitaire.h
	g++ $(CCFLAGS) -c main.cc

nfront.o:nfront.h nfront.cc addmod.h
	g++ $(CCFLAGS) -c nfront.cc

addmod.o:addmod.h addmod.cc
	g++ $(CCFLAGS) -c addmod.cc

solitaire.o:solitaire.h solitaire.cc
	g++ $(CCFLAGS) -c solitaire.cc

bench:bench.cc solitaire.o
	g++ $(CCFLAGS)  solitaire.o bench.cc -o bench

hasher:hasher.cc solitaire.o
	g++ $(CCFLAGS)  solitaire.o hasher.cc -o hasher

dumper:dumper.cc solitaire.o
	g++ $(CCFLAGS)  solitaire.o dumper.cc -o dumper

alphabreaker:alphabreaker.cc solitaire.o addmod.o
	g++ $(CCFLAGS) alphabreaker.cc solitaire.o addmod.o -o alphabreaker

numbreaker:numbreaker.cc solitaire.o addmod.o Integer.o
	g++ $(CCFLAGS) $(LIBS)  numbreaker.cc solitaire.o addmod.o Integer.o -o numbreaker

matcher:matcher.cc addmod.o solitaire.o
	g++ $(CCFLAGS) matcher.cc solitaire.o addmod.o -o matcher

Integer.o:Integer.h Integer.cc
	g++ $(CCFLAGS) -c Integer.cc

clean:
	rm -f *.o *~ core

mrproper:
	rm -f *.o *~ core $(all)
