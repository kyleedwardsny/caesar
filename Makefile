all: hw3
clean:
	rm -f hw3 caesar.o

hw3: caesar.o
	gcc -o hw3 caesar.o

caesar.o: caesar.c
	gcc -c -o caesar.o caesar.c
