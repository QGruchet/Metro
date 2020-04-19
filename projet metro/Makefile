# Clément Caumes 21501810
# Yassin Doudouh 21500127
# 05 mai 2017
# Projet Metro IN403

# Makefile du projet Metro

CFLAGS=-c -g -Wall
SDL=`sdl-config --cflags` 

run: compile
	./metro
	
valgrind: 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./metro
	
compile: metro.o lire_ecrire.o graphe.o #affichage.o
	gcc -Wall -o metro metro.o lire_ecrire.o graphe.o #affichage.o

metro.o: metro.c graphe.h lire_ecrire.h types.h #affichage.h
	gcc $(CFLAGS) $(SDL) metro.c
	
lire_ecrire.o: lire_ecrire.c lire_ecrire.h graphe.h types.h #affichage.h
	gcc $(CFLAGS) $(SDL) lire_ecrire.c
	
graphe.o: graphe.c graphe.h lire_ecrire.h types.h #affichage.h
	gcc $(CFLAGS) $(SDL) graphe.c
	
indent: 
	indent -linux *.h
	indent -linux *.c
	rm -f *.h~
	rm -f *.c~
	
clean:
	rm -f metro
	rm -f metro.o
	rm -f lire_ecrire.o
	rm -f graphe.o
	#rm -f affichage.o