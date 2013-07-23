OBJECTS = engine.o peca.o metronomo.o tabuleiro.o
SOURCES = ${OBJECTS,  .o=.c}
HEADERS = ${OBJECTS,  .o=.h}
SELF = ${@, .o=.c} ${@, .o=.h}
GCOVFLAGS = -fprofile-arcs -ftest-coverage

all: compile run clean

compile: main.o ${OBJECTS}
	gcc $? -lncurses ${GCOV} -o compiled.out

run:
	./compiled.out
	read null

cover: main.o ${OBJECTS}
	gcc $? -lncurses ${GCOVFLAGS} -o compiled.out
	./compiled.out
	gcov *.c

clean:
	rm *.o *.out *.gcov *.gcda *.gcno

main.o: main.c ${SOURCES} ${HEADERS}
	gcc -c ${GCOVFLAGS} main.c

engine.o: ${SOURCES} ${HEADERS}
	gcc -c ${GCOVFLAGS} engine.c

peca.o: ${SELF} engine.h
	gcc -c ${GCOVFLAGS} peca.c

tabuleiro.o: ${SELF} engine.h
	gcc -c ${GCOVFLAGS} tabuleiro.c

metronomo.o: ${SELF}
	gcc -c ${GCOVFLAGS} metronomo.c
