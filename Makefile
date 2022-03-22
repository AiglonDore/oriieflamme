CC=gcc
FLAGS=-std=c99 -Wall -Wextra


all : oriieflamme.out

oriieflamme.out : main.o carte.o faction.o interface.o plateau.o
	cd obj
	$(CC) $(FLAGS) -o ../bin/$@ $^
	cd ..

%.o : %.c
	$(CC) $(FLAGS) -c -o obj/$@ src/$<

main.o : headers/carte.h headers/faction.h headers/interface.h headers/plateau.h

carte.o : headers/carte.h

faction.o : headers/faction.h headers/carte.h

interface.o : headers/carte.h headers/faction.h headers/interface.h headers/plateau.h

plateau.o : headers/plateau.h headers/carte.h headers/faction.h

clean :
	cd bin
	rm -f -i -v *.out
	cd ..\obj
	rm -f -i -v *.o
	cd ..