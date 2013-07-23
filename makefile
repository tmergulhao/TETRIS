OBJECTS = engine.o peca.o metronomo.o tabuleiro.o
SOURCES = ${OBJECTS,  .o=.c}
HEADERS = ${OBJECTS,  .o=.h}
SELF = ${@, .o=.c} ${@, .o=.h}
GCOVFLAGS = -fprofile-arcs -ftest-coverage

all: compile run clean

test: cover assert clean

compile: main.o ${OBJECTS}
	gcc $? -lncurses ${GCOV} -o compiled.out

run:
	./compiled.out
	read null

cover: main.o ${OBJECTS}
	gcc $? -lncurses ${GCOVFLAGS} -o compiled.out
	./compiled.out
	gcov *.c

assert: test.main.o ${OBJECTS}
	gcc $? -lcunit -lncurses -o test.compiled.out
	./test.compiled.out

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

test.main.o: ${SELF} ${SOURCES} ${HEADERS}
	gcc -c test.main.c