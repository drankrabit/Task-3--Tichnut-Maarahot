all: main

main: main.o StrList.o
	gcc -Wall main.o StrList.o -o main

main.o: main.c StrList.h
	gcc -c -Wall main.c -o main.o

StrList.o: StrList.c StrList.h
	gcc -c -Wall StrList.c -o StrList.o

clean:
	rm -f *.o main