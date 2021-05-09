CFLAGS=-g -Wall
CC = gcc
VAL =  --leak-check=full --show-leak-kinds=all --track-origins=yes 
FILES=src/*.c

run: metro 
	./metro
	
all: metro
	
metro: $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o $@

valgrind: compile
	valgrind $(VAL) ./metro

indent: 
	indent -linux *.h
	indent -linux *.c
	rm -f *.h~
	rm -f *.c~
	
clean:
	rm -f metro
	ls -a