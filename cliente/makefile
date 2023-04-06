#Makefile CLIENT
all: program

program: main.o Cliente.o 
	gcc -o main.o Cliente.o 

main.o: main.c Cliente.h
	gcc -c main.c

Cliente.o: Cliente.c Cliente.h
	gcc -c Cliente.c

clean:
	rm -f *.o