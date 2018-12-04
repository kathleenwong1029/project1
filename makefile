all: shell.o
	gcc -o test shell.o

shell.o: shell.c
	gcc -c shell.c

run:
	./test

clean:
	rm *.o
