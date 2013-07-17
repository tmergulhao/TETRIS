OBJECTS =
SOURCES = ${OBJECTS,  .o=.c}
HEADERS = ${OBJECTS,  .o=.h}
SELF = ${@, .o=.c} ${@, .o=.h}

all: compile
	./compiled
	read null
	clean

compile: main.o ${OBJECTS}
	gcc $? -lncurses -o compiled

clean:
	rm compiled
	rm *.o

main.o: main.c ${SOURCES} ${HEADERS}
	gcc -c main.c
