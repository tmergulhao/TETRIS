OBJECTS = engine.o peca.o
SOURCES = ${OBJECTS,  .o=.c}
HEADERS = ${OBJECTS,  .o=.h}
SELF = ${@, .o=.c} ${@, .o=.h}

all: compile
	./compiled.out
	read null
	rm *.o *.out

compile: main.o ${OBJECTS}
	gcc $? -lncurses -o compiled.out

main.o: main.c ${SOURCES} ${HEADERS}
	gcc -c main.c

engine.o: ${SELF} peca.c peca.h
	gcc -c engine.c

peca.o: ${SELF}
	gcc -c peca.c
