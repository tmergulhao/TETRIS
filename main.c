#include <stdio.h>
#include <ncurses.h>

#define numlen()

// MÓDULO DE INICIAÇÃO
void Iniciar_Modulos() {
	initscr(); 				// initiate
	cbreak(); 				// direct input, no ENTER
	noecho(); 				// nonverbose
	keypad(stdscr, TRUE); 	// get special keystrokes
	start_color(); 			// colors
	timeout(5000); 			// miliseconds, timeout outset
}
void Finalizar_Modulos() {
	endwin();				// end curses mode
}

int main (int argc, char *argv[]) {

	Iniciar_Modulos();

	char 	hello[]="Hello World! Are you there?",
			line[]="_______________";
	int row,col;

	getmaxyx(stdscr,row,col);	// just in case you wonder: it's a MACRO
	mvprintw(row/2,(col - strlen(hello))/2 - 3,"%s %i %i",hello, row, col);
	mvprintw(row/2+1,(col - strlen("Width: ") - ((col > 9) ? (col > 99) ? (col > 999) ? 3 : 2 : 1 : 0))/2,"Width: %i", col);
	mvprintw(row/2+2,(col - strlen("Height:   "))/2,"Height: %i", row);
	mvaddstr(row/2-2,(col - strlen(line))/2, line);
	mvaddstr(row/2+3,(col - strlen(line))/2, line);

	// mvaddstr(2,3,"Hello World! Are you there?");
	refresh();

	getchar();

	Finalizar_Modulos();

	return 0;
}
