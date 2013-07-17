OBJECTS = engine.o
SOURCES = ${OBJECTS,  .o=.c}
HEADERS = ${OBJECTS,  .o=.h}
SELF = ${@, .o=.c} ${@, .o=.h}

all: compile
	./compiled.out
	read null
	clean

compile: main.o ${OBJECTS}
	gcc $? -lncurses -o compiled.out

clean:
	rm *.o compiled.out

main.o: main.c ${SOURCES} ${HEADERS}
	gcc -c main.c

engine.o: ${SELF}
	gcc -c engine.c
