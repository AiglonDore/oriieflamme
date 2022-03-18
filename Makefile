CC=gcc
FLAGS=-std=c99 -Wall -Wextra

all : oriieflamme.out

oriieflamme.out : main.o carte.o faction.o interface.o plateau.o
	$(CC) $(FLAGS) -o $@ $^

%.o : %.c
	$(CC) $(FLAGS) -c -o $@ $<

main.o : carte.h faction.h interface.h plateau.h

carte.o : carte.h

faction.o : faction.h carte.h

interface.o : carte.h faction.h interface.h plateau.h

plateau.o : plateau.h carte.h faction.h