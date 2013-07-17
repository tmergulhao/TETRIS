#include <stdio.h>
#include <string.h>
#include <ncurses.h>

#define numlen(X) 		((X > 9) ? (X > 99) ? (X > 999) ? (X > 9999) ? (X > 99999) ? (X > 999999) ? (X > 9999999) ? 8 : 7 : 6 : 5 : 4 : 3 : 2 : 1)

#define KEY_SPACE		32
#define SCREEN_WIDTH 	sizeWidth()
#define SCREEN_HEIGHT 	sizeHeight()
#define SCR_WIDTH_ADD	(SCREEN_WIDTH-22)/2+1
#define SCR_HEIGHT_ADD	(SCREEN_HEIGHT-22)/2+1

void set_frame () {
	int i;
	
	for (i = 0; i < 20; i++) {
		mvaddch(SCR_HEIGHT_ADD+i, SCR_WIDTH_ADD-1, '|');
		mvaddch(SCR_HEIGHT_ADD+i, SCR_WIDTH_ADD-1+21, '|');
	}
	mvaddstr(SCR_HEIGHT_ADD-1,SCR_WIDTH_ADD-1, "/¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\\");
	mvaddstr(SCR_HEIGHT_ADD+20,SCR_WIDTH_ADD-1, "\\____________________/");
	
	refresh();
}


// BASICS
void clrline (int i) {
	mvaddstr(i, SCR_WIDTH_ADD, "                    ");
}
void beep_screen (int i) {
	for(; i; i--) {
		printf("\a");
	}
}
int sizeWidth() {
	static int width;
	int row;
	if (!width) getmaxyx(stdscr,row,width); // just in case you wonder: it's a MACRO
	return width;
}
int sizeHeight() {
	static int height;
	int col;
	if (!height) getmaxyx(stdscr,height,col); // just in case you wonder: it's a MACRO
	return height;
}

// INICIA E FINALIZA NCURSES
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
int Testar_Interface() {
	char 	hello[]="+TETRIS",
			line[]="_______________";
	int ch;

	if (SCREEN_HEIGHT < 22 || SCREEN_WIDTH < 22) return 0;

	mvprintw(SCREEN_HEIGHT/3,(SCREEN_WIDTH - strlen(hello))/2,"%s",hello);
	mvprintw(SCREEN_HEIGHT/3+2,(SCREEN_WIDTH - strlen("Width: ") - numlen(SCREEN_WIDTH))/2,"Width: %i", SCREEN_WIDTH); // %.3i
	mvprintw(SCREEN_HEIGHT/3+3,(SCREEN_WIDTH - strlen("Height: ") - numlen(SCREEN_HEIGHT))/2,"Height: %i", SCREEN_HEIGHT);
	mvaddstr(SCREEN_HEIGHT/3-2,(SCREEN_WIDTH - strlen(line))/2, line);
	mvaddstr(SCREEN_HEIGHT/3+4,(SCREEN_WIDTH - strlen(line))/2, line);
	refresh();

	mvaddstr(2*SCREEN_HEIGHT/3,(SCREEN_WIDTH - strlen("USE ARROW KEYS"))/2, "USE ARROW KEYS");
	
	while ((ch = getch()) != KEY_SPACE) {
		clrline(2*SCREEN_HEIGHT/3+3);

		switch (ch) {
			case KEY_UP:
				mvaddstr(2*SCREEN_HEIGHT/3+3,(SCREEN_WIDTH - strlen("UP"))/2, "UP");
				break;
			case KEY_DOWN:
				mvaddstr(2*SCREEN_HEIGHT/3+3,(SCREEN_WIDTH - strlen("DOWN"))/2, "DOWN");
				break;
			case KEY_LEFT:
				mvaddstr(2*SCREEN_HEIGHT/3+3,(SCREEN_WIDTH - strlen("LEFT"))/2, "LEFT");
				break;
			case KEY_RIGHT:
				mvaddstr(2*SCREEN_HEIGHT/3+3,(SCREEN_WIDTH - strlen("RIGHT"))/2, "RIGHT");
				break;
			default:
				mvaddstr(2*SCREEN_HEIGHT/3,(SCREEN_WIDTH - strlen("USE ARROW KEYS"))/2, "USE ARROW KEYS");
				mvaddstr(2*SCREEN_HEIGHT/3 + 3,(SCREEN_WIDTH - strlen("SCAPE WITH SPACE"))/2, "SCAPE WITH SPACE");
		}
		refresh();
	}

	return 1;

	// Create a WDSA-Q fallback
}

// MENU
void turn_off (int i) {
	if (i == 0) mvaddstr((i+1)*SCREEN_HEIGHT/5,(SCREEN_WIDTH - strlen("  PLAY  "))/2, "  PLAY  ");
	if (i == 1) mvaddstr((i+1)*SCREEN_HEIGHT/5,(SCREEN_WIDTH - strlen("  SCORE  "))/2, "  SCORE  ");
	if (i == 2) mvaddstr((i+1)*SCREEN_HEIGHT/5,(SCREEN_WIDTH - strlen("  EXIT  "))/2, "  EXIT  ");
}
void turn_on (int i) {
	if (i == 0) mvaddstr((i+1)*SCREEN_HEIGHT/5,(SCREEN_WIDTH - strlen("+ PLAY +"))/2, "+ PLAY +");
	if (i == 1) mvaddstr((i+1)*SCREEN_HEIGHT/5,(SCREEN_WIDTH - strlen("+ SCORE +"))/2, "+ SCORE +");
	if (i == 2) mvaddstr((i+1)*SCREEN_HEIGHT/5,(SCREEN_WIDTH - strlen("+ EXIT +"))/2, "+ EXIT +");
}

int Capturar_Opcao() {
	int ch, i = 0;
	
	erase();
	
	for (i = 3; i; i--) turn_off(i-1);
	turn_on(i);
	refresh();
	
	while ((ch = getch())) {
		switch (ch) {
			case KEY_UP:
				turn_off(i);
				i = (i == 0) ? 2 : (i-1)%3;
				break;
			case KEY_DOWN:
				turn_off(i);
				i = (i+1)%3;
				break;
			case KEY_SPACE:
				return i;
				break;
			default:
				mvaddstr(SCREEN_HEIGHT-3,(SCREEN_WIDTH - strlen("USE ARROW KEYS"))/2, "USE ARROW KEYS");
				mvaddstr(SCREEN_HEIGHT-2,(SCREEN_WIDTH - strlen("SELECT WITH SPACE"))/2, "SELECT WITH SPACE");
		}
		turn_on(i);
		refresh();
	}
}

int main (int argc, char *argv[]) {
	int i;
	Iniciar_Modulos();
	
	set_frame();getch();
	
	if (Testar_Interface()) {
		while ((i = Capturar_Opcao()) != 2) {
			/*
			if (i == 0) Mostrar_Score();
			if (i == 1) Jogar();
			*/
			beep_screen(i+1);
		}
	}
	else {
		Finalizar_Modulos();
		printf("MINIMUM TERMINAL SIZE IS 22 BY 22\a");
		getchar();

		return 1;
	}
	
	erase();
	mvaddstr(SCREEN_HEIGHT/2,(SCREEN_WIDTH - strlen("BYE!"))/2, "BYE!");
	getch();
	
	Finalizar_Modulos();

	return 0;
}
