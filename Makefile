CC=gcc
FLAGS=-std=c99 -Wall -Wextra
FLAGS_RELEASE=-s -O2


all : oriieflamme.out

oriieflamme.out : obj/main.o obj/structure.o obj/carte.o obj/faction.o obj/interface.o obj/plateau.o
	$(CC) $(FLAGS) -o bin/$@ $^


obj/main.o: src/main.c headers/carte.h headers/faction.h headers/interface.h headers/plateau.h
	$(CC) $(FLAGS) -c -o $@ $<

obj/carte.o: src/carte.c headers/carte.h
	$(CC) $(FLAGS) -c -o $@ $<

obj/faction.o : src/faction.c headers/faction.h headers/carte.h
	$(CC) $(FLAGS) -c -o $@ $<

obj/interface.o : src/interface.c headers/carte.h headers/faction.h headers/interface.h headers/plateau.h
	$(CC) $(FLAGS) -c -o $@ $<

obj/plateau.o : src/plateau.c headers/plateau.h headers/carte.h headers/faction.h
	$(CC) $(FLAGS) -c -o $@ $<

obj/structure.o : src/structure.c headers/structure.h headers/carte.h headers/faction.h
	$(CC) $(FLAGS) -c -o $@ $<

clean :
	cd bin
	rm -f -i -v *.out
	cd ..\obj
	rm -f -i -v *.o
	cd ..