CFLAGS=-c -g -Wall

run: compile
	./metro
	
valgrind: compile
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./metro
	
compile: metro.o lire_ecrire.o graphe.o 
	gcc -Wall -o metro metro.o lire_ecrire.o graphe.o

metro.o: metro.c graphe.h lire_ecrire.h types.h 
	gcc $(CFLAGS) metro.c
	
lire_ecrire.o: lire_ecrire.c lire_ecrire.h graphe.h types.h 
	gcc $(CFLAGS) lire_ecrire.c
	
graphe.o: graphe.c graphe.h lire_ecrire.h types.h 
	gcc $(CFLAGS) graphe.c
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