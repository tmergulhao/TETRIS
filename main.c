#include <stdio.h>
#include <string.h>
#include <ncurses.h>

#define numlen(X) ((X > 9) ? (X > 99) ? (X > 999) ? (X > 9999) ? (X > 99999) ? (X > 999999) ? (X > 9999999) ? 8 : 7 : 6 : 5 : 4 : 3 : 2 : 1)

#define KEY_SPACE	32

// MÓDULO DE INICIAÇÃO
void Iniciar_Modulos() {
	initscr(); 				// initiate
	cbreak(); 				// direct input, no ENTER
	noecho(); 				// nonverbose
	keypad(stdscr, TRUE); 	// get special keystrokes
	start_color(); 			// colors
	timeout(5000); 			// miliseconds, timeout outset
	curs_set(0);			// invisible cursor
}
void Finalizar_Modulos() {
	endwin();				// end curses mode
}
void Testar_Interface() {
	char 	hello[]="+TETRIS",
			line[]="_______________";
	int row,col,ch;

	getmaxyx(stdscr,row,col);	// just in case you wonder: it's a MACRO

	mvprintw(row/3,(col - strlen(hello))/2,"%s",hello);
	mvprintw(row/3+2,(col - strlen("Width: ") - numlen(col))/2,"Width: %i", col); // %.3i
	mvprintw(row/3+3,(col - strlen("Height: ") - numlen(row))/2,"Height: %i", row);
	mvaddstr(row/3-2,(col - strlen(line))/2, line);
	mvaddstr(row/3+4,(col - strlen(line))/2, line);
	refresh();

	mvaddstr(2*row/3,(col - strlen("TEST THE ARROW KEYS"))/2, "TEST THE ARROW KEYS");
	while ((ch = getch()) != KEY_SPACE) {
		move(2*row/3,1);
		clrtoeol();
		move(2*row/3 + 1,1);
		switch (ch) {
			case KEY_UP:
				mvaddstr(2*row/3,(col - strlen("UP"))/2, "UP");
				break;
			case KEY_DOWN:
				mvaddstr(2*row/3,(col - strlen("DOWN"))/2, "DOWN");
				break;
			case KEY_LEFT:
				mvaddstr(2*row/3,(col - strlen("LEFT"))/2, "LEFT");
				break;
			case KEY_RIGHT:
				mvaddstr(2*row/3,(col - strlen("RIGHT"))/2, "RIGHT");
				break;
			default:
				mvaddstr(2*row/3,(col - strlen("TEST THE ARROW KEYS"))/2, "TEST THE ARROW KEYS");
				mvaddstr(2*row/3 + 3,(col - strlen("SCAPE WITH SPACE"))/2, "SCAPE WITH SPACE");
		}
		refresh();
	}
	printf("\a");

	// Create a WDSA-Q fallback
}


int main (int argc, char *argv[]) {

	int i;

	Iniciar_Modulos();

	Testar_Interface();

	while (i = Capturar_Opcao()) {
		if (i == 1) {
			Mostrar_Score();
		}
		if (i == 2) {

		}
	}

	Finalizar_Modulos();

	return 0;
}
