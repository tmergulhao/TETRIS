OBJECTS = engine.o peca.o metronomo.o
SOURCES = ${OBJECTS,  .o=.c}
HEADERS = ${OBJECTS,  .o=.h}
SELF = ${@, .o=.c} ${@, .o=.h}

all: compile run clean

compile: main.o ${OBJECTS}
	gcc $? -lncurses -o compiled.out

run:
	./compiled.out
	read null

clean:
	rm *.o *.out

main.o: main.c ${SOURCES} ${HEADERS}
	gcc -c main.c

engine.o: ${SOURCES} ${HEADERS}
	gcc -c engine.c

peca.o: ${SELF}
	gcc -c peca.c

metronomo.o: ${SELF}
	gcc -c metronomo.c

