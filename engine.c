#define KEY_SPACE		32
#define numlen(X) 		((X > 9) ? (X > 99) ? (X > 999) ? (X > 9999) ? (X > 99999) ? (X > 999999) ? (X > 9999999) ? 8 : 7 : 6 : 5 : 4 : 3 : 2 : 1)
#define SCREEN_WIDTH 	sizeWidth()
#define SCREEN_HEIGHT 	sizeHeight()
#define SCR_WIDTH_ADD	(SCREEN_WIDTH - 22)/2 + 1
#define SCR_HEIGHT_ADD	(SCREEN_HEIGHT - 22)/2 + 1
#define CENTER(X)		SCR_WIDTH_ADD + (20 - (X))/2
#define SCREEN_BOTTOM	SCR_HEIGHT_ADD + 19
#define ESPERA_INPUT 	5 // seconds

#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
// #include <stdbool.h>

#include "engine.h"
/* #include "tela.h" */
#include "peca.h"

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
void Centralizar_Peca () {
	PECA* PECA_ATUAL = Chamar_Peca();
	PECA_ATUAL->Y = 11;
	PECA_ATUAL->X = 5;
}
void display_piece (int i) {
	PECA* PECA_ATUAL = Chamar_Peca();

	int j;
	
	for (j = 0; j < 4; j++) {
		if (i) mvaddstr((SCR_HEIGHT_ADD + PECA_ATUAL->Y + PECA_ATUAL->BLOCO[j].Y), (SCR_WIDTH_ADD + (PECA_ATUAL->X + PECA_ATUAL->BLOCO[j].X)*2), "[]");
		else mvaddstr((SCR_HEIGHT_ADD + PECA_ATUAL->Y + PECA_ATUAL->BLOCO[j].Y), (SCR_WIDTH_ADD + (PECA_ATUAL->X + PECA_ATUAL->BLOCO[j].X)*2), "  ");
	}
}
void Mostrar_Peca () {	display_piece(1);	}
void Apagar_Peca() {	display_piece(0);	}

void clrline (int i) {
	if (i) mvaddstr(i, SCR_WIDTH_ADD, "                    ");
	else for (i = 0; i<20; i++) clrline (SCR_HEIGHT_ADD + i); // CLEARS ALL GAME LINES 20*20
}
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
void turn_off (int i) {
	if (i == 0) mvaddstr(SCR_HEIGHT_ADD+3,CENTER(strlen("  PLAY  ")), "  PLAY  ");
	if (i == 1) mvaddstr(SCR_HEIGHT_ADD+7,CENTER(strlen("  SCORE  ")), "  SCORE  ");
	if (i == 2) mvaddstr(SCR_HEIGHT_ADD+11,CENTER(strlen("  EXIT  ")), "  EXIT  ");
}
void turn_on (int i) {
	if (i == 0) mvaddstr(SCR_HEIGHT_ADD+3,CENTER(strlen("+ PLAY +")), "+ PLAY +");
	if (i == 1) mvaddstr(SCR_HEIGHT_ADD+7,CENTER(strlen("+ SCORE +")), "+ SCORE +");
	if (i == 2) mvaddstr(SCR_HEIGHT_ADD+11,CENTER(strlen("+ EXIT +")), "+ EXIT +");
}
bool set_metronomy (int i) {
	static clock_t *timer;
	static int espera;
	
	if (timer == NULL) {
		if (espera <= 0) espera = ESPERA_INPUT; // 5 sec default
		
		timer = (clock_t*)malloc(sizeof(clock_t));
		*timer = clock() +  CLOCKS_PER_SEC * espera;
	}
	if (i < 0 && *timer < clock()) {
		if (espera <= 0) espera = ESPERA_INPUT; // 5 sec default
		
		*timer = clock() +  CLOCKS_PER_SEC * espera;
		return TRUE;
	} else if (i > 0) espera = i;
	else if (i == 0) free(timer);
	
	return FALSE;
}
void Desligar_Espera () {					set_metronomy(0);	}
void Valor_Espera (int i) {		if (i > 0) 	set_metronomy(i);	}
bool Tempo_Espera () {			return 		set_metronomy(-1);	}

/*INTERFACES EXTERNAS*/
void Iniciar_Modulos() {
	initscr(); 				// initiate
	cbreak(); 				// direct input, no ENTER
	noecho(); 				// nonverbose
	keypad(stdscr, TRUE); 	// get special keystrokes
	start_color(); 			// colors
	timeout(0000); 			// miliseconds, timeout outset
	curs_set(0);			// invisible cursor
	
	srand (time(NULL));
}
void Finalizar_Modulos() {
	clrline(0);mvaddstr(SCREEN_HEIGHT/2,(SCREEN_WIDTH - strlen("BYE!"))/2, "BYE!");getch();
	endwin();				// end curses mode
}
void clean_interface () {
	int i;
	clrline(SCREEN_BOTTOM - 1);
	clrline(17);
	for(i = 0; i < 4; i++) {
		mvaddch(13+i,(SCREEN_WIDTH - 8)/2 + 8, ' ');
		mvaddch(13+i,(SCREEN_WIDTH - 8)/2 - 1, ' ');
	}
}
int Testar_Interface() {
	char 	hello[]="+ TETRIS +",
			name[]="Tiago Mergulhão",
			email[]="me@tmergulhao.com",
			line[]="_______________";
	int ch, i;

	if (SCREEN_HEIGHT < 22 || SCREEN_WIDTH < 22) return 0;
	
	set_frame();
	
	mvaddstr(SCR_HEIGHT_ADD + 1, CENTER(strlen(hello)),hello);
	// mvprintw(SCR_HEIGHT_ADD + 2, CENTER(strlen("Width: ") + numlen(SCREEN_WIDTH)),"Width: %i", SCREEN_WIDTH); // %.3i
	// mvprintw(SCR_HEIGHT_ADD + 3, CENTER(strlen("Height: ") + numlen(SCREEN_HEIGHT)),"Height: %i", SCREEN_HEIGHT);
	
	mvaddstr(SCR_HEIGHT_ADD + 3, CENTER(strlen(line)), line);

	mvaddstr(SCR_HEIGHT_ADD + 6, CENTER(strlen(name)), name);
	mvaddstr(SCR_HEIGHT_ADD + 7, CENTER(strlen(email)), email);

	mvaddstr(SCREEN_BOTTOM - 1, CENTER(strlen("USE ARROW KEYS")), "USE ARROW KEYS");
	
	Iniciar_Peca(rand()%7);
	Centralizar_Peca();
	Mostrar_Peca();

	refresh();
	
	while ( (i = Tempo_Espera()) || (ch = getch()) != KEY_SPACE ) {
		
		switch (ch) {
			case KEY_UP:
				Apagar_Peca();
				Rotacionar_Peca();
				clean_interface();
				mvaddstr(SCREEN_BOTTOM - 1,(SCREEN_WIDTH - strlen("UP"))/2, "UP");
				Mostrar_Peca();
				break;
			case KEY_DOWN:
				clean_interface();
				mvaddstr(17,(SCREEN_WIDTH - 8)/2, "vvvvvvvv");
				mvaddstr(SCREEN_BOTTOM - 1,(SCREEN_WIDTH - strlen("DOWN"))/2, "DOWN");
				break;
			case KEY_LEFT:
				clean_interface();
				for(i = 0; i < 4; i++) mvaddch(13+i,(SCREEN_WIDTH - 8)/2 - 1, '<');
				mvaddstr(SCREEN_BOTTOM - 1,(SCREEN_WIDTH - strlen("LEFT"))/2, "LEFT");
				break;
			case KEY_RIGHT:
				clean_interface();
				for(i = 0; i < 4; i++) mvaddch(13+i,(SCREEN_WIDTH - 8)/2 + 8, '>');
				mvaddstr(SCREEN_BOTTOM - 1,(SCREEN_WIDTH - strlen("RIGHT"))/2, "RIGHT");
				break;
			default:
				if(i) {
					mvaddstr(SCREEN_BOTTOM - 1,CENTER(strlen("SCAPE WITH SPACE")), "SCAPE WITH SPACE");
					clean_interface();
					Apagar_Peca();
					// for (i = 0; i < 4; i++) clrline(13+i);
					Iniciar_Peca(rand()%7);
					Centralizar_Peca();
					Mostrar_Peca();
				}
		}
		refresh();
	}
	Desligar_Espera();
	free(Chamar_Peca());
	
	return 1;

	// Create a WDSA-Q fallback
}
int Capturar_Opcao() {
	int ch, i = 0;

	clrline(0);
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
				if (Tempo_Espera()) mvaddstr(SCREEN_BOTTOM - 1,CENTER(strlen("SELECT WITH SPACE")), "SELECT WITH SPACE");
		}
		turn_on(i);
		refresh();
	}
	Desligar_Espera();
	return 0;
}
void Jogar() {
	
}
void Mostrar_Score() {
	
}
