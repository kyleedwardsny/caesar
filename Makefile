all: hw3

hw3: caesar.o
	gcc -o hw3 caesar.o

caesar.o: caesar.c
	gcc -c -o caesar.o caesar.c
