CC=gcc
FLAGS=-std=c99 -Wall -Wextra


all : oriieflamme.out

oriieflamme.out : obj/main.o obj/structure.o obj/carte.o obj/faction.o obj/interface.o obj/plateau.o
	$(CC) $(FLAGS) -o bin/$@ $^

%.o: src/%.c
	$(CC) $(FLAGS) -c -o $@ $<

obj/main.o: headers/carte.h headers/faction.h headers/interface.h headers/plateau.h main.o

obj/carte.o: headers/carte.h carte.o

obj/faction.o : headers/faction.h headers/carte.h faction.o

obj/interface.o : headers/carte.h headers/faction.h headers/interface.h headers/plateau.h interface.o

obj/plateau.o : headers/plateau.h headers/carte.h headers/faction.h plateau.o

obj/structure.o : headers/structure.h headers/carte.h headers/faction.h structure.o

clean :
	cd bin
	rm -f -i -v *.out
	cd ..\obj
	rm -f -i -v *.o
	cd ..