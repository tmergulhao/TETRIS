OBJECTS = engine.o peca.o metronomo.o tabuleiro.o
SOURCES = ${OBJECTS,  .o=.c}
HEADERS = ${OBJECTS,  .o=.h}
SELF = ${@, .o=.c} ${@, .o=.h}

TOPFLAGS = -lncurses
CFLAGS = 

GCOVFLAGS = -fprofile-arcs -ftest-coverage

all: compile run clean

assert: CFLAGS += -DASSERT
assert: all

cunit: TOPFLAGS += -lcunit
cunit: CFLAGS += -fprofile-arcs -ftest-coverage
cunit: compile-test run cover clean

compile: main.o ${OBJECTS}
	gcc $? ${TOPFLAGS} ${CFLAGS} -o compiled.out

compile-test: main.test.o ${OBJECTS}
	gcc $? ${TOPFLAGS} ${CFLAGS} -o compiled.out

run:
	./compiled.out
	read null

cover:
	gcov *.c

clean:
	rm *.o *.out *.gcov *.gcda *.gcno

main.o: main.c ${SOURCES} ${HEADERS}
	gcc -c ${CFLAGS} main.c

main.test.o: ${SELF} ${SOURCES} ${HEADERS}
	gcc -c ${CFLAGS} main.test.c

engine.o: ${SOURCES} ${HEADERS}
	gcc -c ${CFLAGS} engine.c

peca.o: ${SELF} engine.h
	gcc -c ${CFLAGS} peca.c

tabuleiro.o: ${SELF} engine.h
	gcc -c ${CFLAGS} tabuleiro.c

metronomo.o: ${SELF}
	gcc -c ${CFLAGS} metronomo.c
