OBJECTS = peca.o metronomo.o tabuleiro.o
SOURCES = ${OBJECTS,  .o=.c}
HEADERS = ${OBJECTS,  .o=.h}
SELF = ${@, .o=.c} ${@, .o=.h}
COMPILER = g++

TOPFLAGS = -lncurses

GCOVFLAGS = -fprofile-arcs -ftest-coverage

all: compile run clean

clear: DFLAGS = -DNDEBUG
clear: all

test: DFLAGS = -lcunit -fprofile-arcs -ftest-coverage
test: compile-test run cover clean

compile: main.o ${OBJECTS}
	${COMPILER} $? ${TOPFLAGS} ${DFLAGS} -o compiled.out

compile-test: main.test.o ${OBJECTS}
	${COMPILER} $? ${TOPFLAGS} ${DFLAGS} -o compiled.out

run:
	./compiled.out
	read null

cover:
	gcov ${OBJECTS}
	read null

clean:
	rm *.o *.out *.gcov *.gcda *.gcno

main.o: main.c ${SOURCES} ${HEADERS}
	${COMPILER} -c ${DFLAGS} main.c

main.test.o: ${SELF} ${SOURCES} ${HEADERS}
	${COMPILER} -c ${DFLAGS} main.test.c

peca.o: ${SELF} main.h
	${COMPILER} -c ${DFLAGS} peca.c

tabuleiro.o: ${SELF} main.h
	${COMPILER} -c ${DFLAGS} tabuleiro.c

metronomo.o: ${SELF}
	${COMPILER} -c ${DFLAGS} metronomo.c
