CC=gcc
FLAGS=-std=c99 -Wall -Wextra


all : oriieflamme.out

oriieflamme.out : main.o carte.o faction.o interface.o plateau.o
	cd obj
	$(CC) $(FLAGS) -o ../bin/$@ $^
	cd ..

%.o : %.c
	$(CC) $(FLAGS) -c -o obj/$@ src/$<

main.o : hearders/carte.h hearders/faction.h hearders/interface.h hearders/plateau.h

carte.o : hearders/carte.h

faction.o : hearders/faction.h hearders/carte.h

interface.o : hearders/carte.h hearders/faction.h hearders/interface.h hearders/plateau.h

plateau.o : hearders/plateau.h hearders/carte.h hearders/faction.h