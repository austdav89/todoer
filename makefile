all:bin/todoer

bin/todoer: obj/todoer.o obj/main.o
	gcc -o bin/todoer obj/main.o obj/todoer.o

obj/todoer.o: src/todoer.c
	gcc -Wall -c -o obj/todoer.o src/todoer.c

obj/main.o: src/main.c
	gcc -Wall -c -o obj/main.o src/main.c

go: bin/todoer.exe
	bin/todoer.exe

clean: 
	rm obj/*.o bin/todoer.exe
