#Makefile CLIENT
all: program_client

program_client: test_client.o Cliente.o 
	gcc -o test_client.o Cliente.o 

test_client.o: test_client.c Cliente.h
	gcc -c test_client.c

Cliente.o: Cliente.c Cliente.h
	gcc -c Cliente.c

clean:
	rm -f *.o