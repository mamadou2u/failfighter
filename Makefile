fail : fail.o ennemi.o 
	gcc -g fail.o ennemi.o -o fail `sdl-config --cflags --libs` -lm
 
fail.o : fail.c ennemi.c ennemi.h
	gcc -g -c fail.c -o fail.o `sdl-config --cflags --libs` -lm

ennemi.o : ennemi.c
	gcc -g -c ennemi.c -o ennemi.o `sdl-config --cflags --libs` -lm
