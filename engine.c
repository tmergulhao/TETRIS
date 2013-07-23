#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "engine.h"
#include "peca.h"
#include "metronomo.h"
#include "tabuleiro.h"

#define Desligar_Espera() 	metronomy(0,0)
#define Tempo_Espera() 		metronomy(-1,0)
#define Tempo_Jogo() 		metronomy(-1,1)
#define Ver_T_Jogo()		metronomy(-2,1)
#define Passar_Ciclo()		metronomy(-3,1)
#define Mudar_Tempo_Jogo(X) if(BETWEEN((Ver_T_Jogo()+X),1,5)) metronomy(Ver_T_Jogo() + X,1)

#define KEY_SPACE			32
#define numlen(X) 			((X > 9) ? (X > 99) ? (X > 999) ? (X > 9999) ? (X > 99999) ? (X > 999999) ? (X > 9999999) ? 8 : 7 : 6 : 5 : 4 : 3 : 2 : 1)
#define SCREEN_WIDTH 		sizeWidth()
#define SCREEN_HEIGHT 		sizeHeight()
#define SCR_WIDTH_ADD		(SCREEN_WIDTH - 22)/2 + 1
#define SCR_HEIGHT_ADD		(SCREEN_HEIGHT - 22)/2 + 1
#define CENTER(X)			SCR_WIDTH_ADD + (CANVAS_WIDTH*2 - (X))/2
#define SCREEN_BOTTOM		SCR_HEIGHT_ADD + 19

#define name				"+ TETRIS +"
#define email				"me@tmergulhao.com"
#define dev_name			"Tiago Mergulhão"

#define final_words			"BYE!"

#define clrline_a()			clrline(0)

#define Mostrar_Peca()		display_piece(1)
#define Apagar_Peca()		display_piece(0)

#define BLOC_LOCATION_X(Y)	PECA_ATUAL->X + BLOCO[Y].X
#define BLOC_LOCATION_Y(X)	PECA_ATUAL->Y + BLOCO[X].Y

#define Inver_Bloco(Y,X)	Acessar_Bloco(Y,X,1)
#define Valor_Bloco(Y,X)	Acessar_Bloco(Y,X,0)
#define Reciclar_Tabul()	Reciclar_Linha(-1)

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

void display_piece (int ON) {
	PECA* PECA_ATUAL = Chamar_Peca_Principal();
	BLOCO_TIPO* BLOCO = PECA_ATUAL->BLOCO;
	
	int i;
	
	for (i = 0; i < 4; i++) if (BETWEEN((BLOC_LOCATION_Y(i)),0,20) && BETWEEN((BLOC_LOCATION_X(i)),0,9)) {
		if (ON) mvaddstr((SCR_HEIGHT_ADD + PECA_ATUAL->Y + BLOCO[i].Y), (SCR_WIDTH_ADD + (PECA_ATUAL->X + BLOCO[i].X)*2), 	"[]");
		else mvaddstr((SCR_HEIGHT_ADD + PECA_ATUAL->Y + BLOCO[i].Y), (SCR_WIDTH_ADD + (PECA_ATUAL->X + BLOCO[i].X)*2), 	"  ");
	}
}
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
	int j = SCR_HEIGHT_ADD + 3 + i*4;
	clrline(j);
	if (i == 0) mvaddstr(j,CENTER(strlen("PLAY")), "PLAY");
	if (i == 1) mvaddstr(j,CENTER(strlen("SCORE")), "SCORE");
	if (i == 2) mvaddstr(j,CENTER(strlen("TIMEOUT")), "TIMEOUT");
	if (i == 3) mvaddstr(j,CENTER(strlen("EXIT")), "EXIT");
}
void turn_on (int i) {
	int j = SCR_HEIGHT_ADD + 3 + i*4;
	clrline(j);
	if (i == 0) mvaddstr(j,CENTER(strlen("+ PLAY +")), "+ PLAY +");
	if (i == 1) mvaddstr(j,CENTER(strlen("+ SCORE +")), "+ SCORE +");
	if (i == 2) mvprintw(j,CENTER(1 + strlen("+  SECONDS +")), "- %.0f SECONDS +", Ver_T_Jogo());
	if (i == 3) mvaddstr(j,CENTER(strlen("+ EXIT +")), "+ EXIT +");
}
void clean_menu_interface () {
	int i;
	clrline(SCREEN_BOTTOM - 1);
	clrline(SCR_HEIGHT_ADD+15);
	for(i = 0; i < 4; i++) {
		mvaddch(SCR_HEIGHT_ADD+11+i, CENTER(8) + 8, ' ');
		mvaddch(SCR_HEIGHT_ADD+11+i, CENTER(8) - 1, ' ');
	}
}

// SUB INTERFACES

void Mostrar_Tabuleiro () {
	TABULEIRO* TABULEIRO_PRINCIPAL = Chamar_Tabuleiro();
	LINHA *LINHA_ATUAL = TABULEIRO_PRINCIPAL->ENTER;
	
	int i, j;
	
	for (i = 0; i < CANVAS_HEIGHT; i++) {
		for (j = 0; j < CANVAS_WIDTH; j++) {
			if (LINHA_ATUAL->VALOR[j]) 	mvaddstr((SCR_HEIGHT_ADD + i), (SCR_WIDTH_ADD + j*2), 	"[]");
			else						mvaddstr((SCR_HEIGHT_ADD + i), (SCR_WIDTH_ADD + j*2), 	"  ");
		}
		LINHA_ATUAL = LINHA_ATUAL->NEXT;
	}
}
void Centralizar_Peca () {
	PECA* PECA_ATUAL = Chamar_Peca_Principal();
	PECA_ATUAL->Y = 14;
	PECA_ATUAL->X = 5;
}
long Score(long i) {
	static long score;
	if (i < 0) {
		score = 0;
		// ADD SCORE TO BOARD
	}
	else score += i*60/(Ver_T_Jogo());

	return score;
}
void Mover_Peca (int i) {
	PECA* PECA_ATUAL = Chamar_Peca_Principal();
	BLOCO_TIPO* BLOCO = PECA_ATUAL->BLOCO;
	bool ALERT_INTERSECTION = false;
	
	int j;
	
	for (j = 0; j < 4; j++) {
		if ((	Valor_Bloco(BLOC_LOCATION_Y(j) , BLOC_LOCATION_X(j) + i))
			||	!(BETWEEN((BLOC_LOCATION_X(j)) + i, 0, CANVAS_WIDTH-1)	)) ALERT_INTERSECTION = true;
	}
	
	if (ALERT_INTERSECTION == false) PECA_ATUAL->X += i;
}
int Descer_Peca () {
	PECA* PECA_ATUAL = Chamar_Peca_Principal();
	BLOCO_TIPO* BLOCO = PECA_ATUAL->BLOCO;
	
	int i, LINES_WRAPPED = 0, min_y = 1;
	
	bool ALERT_INTERSECTION = false, ALERT_OVER = false, CHECK_LINES[4];
	
	if (PECA_ATUAL->Y < 19) { 
		for (i = 0; i < 4; i++) {
			if (Valor_Bloco(BLOC_LOCATION_Y(i)+1 , BLOC_LOCATION_X(i))) ALERT_INTERSECTION = true;
			if (BLOC_LOCATION_Y(i) < 0) ALERT_OVER = true;
		}
		if (ALERT_INTERSECTION) {
			if (ALERT_OVER) return -1;
		} else {
			PECA_ATUAL->Y++;
			Passar_Ciclo();
			
			return 0;
		}
	}
	
	for (i = 0; i < 4; i++) {
		Inver_Bloco(BLOC_LOCATION_Y(i) , BLOC_LOCATION_X(i));
		
		CHECK_LINES[BLOCO[i].Y + 3] = true;
	}
	
	for (i = 0; i < 4; i++) if(CHECK_LINES[i])
		LINES_WRAPPED = (Reciclar_Linha(PECA_ATUAL->Y + i - 3)) ? LINES_WRAPPED+1 : LINES_WRAPPED;
	
	Iniciar_Peca(rand()%7);
	Passar_Ciclo();
	
	return LINES_WRAPPED;
}

// INTERFACES EXTERNAS

void Iniciar_Modulos() {
	// NCURSES
	initscr(); 				// initiate
	cbreak(); 				// direct input, no ENTER
	noecho(); 				// nonverbose
	keypad(stdscr, TRUE); 	// get special keystrokes
	start_color(); 			// colors
	timeout(0000); 			// miliseconds, timeout outset
	curs_set(0);			// invisible cursor
	
	// PHOSPHORUS TERMINAL GREEN
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_color(COLOR_GREEN, 0, 1000, 0);
	attron(COLOR_PAIR(1));

	// TIME
	srand (time(NULL));
}
void Finalizar_Modulos() {
	//MESSAGE
	clrline(0);mvaddstr(SCR_HEIGHT_ADD+(20/2), CENTER(strlen(final_words)), final_words);
	while( !(Tempo_Espera()) && (getch()) != KEY_SPACE) {}
	
	// MEMORY FREE
	Liberar_Tabuleiro();
	free(Chamar_Peca_Principal());
	Desligar_Espera();
	
	// NCURSES
	endwin();				// end curses mode
}
int Capturar_Opcao() {
	int ch, i = 0;

	clrline(0);
	for (i = 4; i; i--) turn_off(i-1);
	turn_on(i);
	refresh();

	while ((ch = getch())) {
		switch (ch) {
			case KEY_UP:
				turn_off(i);
				i = (i == 0) ? 3 : (i-1)%4;
				turn_on(i);
				break;
			case KEY_DOWN:
				turn_off(i);
				i = (i+1)%4;
				turn_on(i);
				break;
			case KEY_SPACE:
				return i;
				break;
			case KEY_LEFT:
				if (i == 2) Mudar_Tempo_Jogo(-1);
				turn_on(i);
				break;
			case KEY_RIGHT:
				if (i == 2) Mudar_Tempo_Jogo(+1);
				turn_on(i);
				break;
			default:
				if (Tempo_Espera()) mvaddstr(SCREEN_BOTTOM - 1,CENTER(strlen("SELECT WITH SPACE")), "SELECT WITH SPACE");
		}
		refresh();
	}
	Desligar_Espera();
	return 0;
}
void Jogar() {
	int ch;
	static int end;
	
	clear();
	set_frame();
	
	if (Score(0) == 0 || end == -1) {
		Iniciar_Peca(rand()%7);
		Reciclar_Tabul();
		end = 0;
	}
	
	Mostrar_Tabuleiro();
	Mostrar_Peca();
	
	while ( (end != -1) && (ch = getch()) != KEY_SPACE) {
		switch (ch) {
			case KEY_UP:
				Apagar_Peca();
				Rotacionar_Peca();
				Mostrar_Peca();
				break;
			case KEY_LEFT:
				Apagar_Peca();
				Mover_Peca(-1);
				Mostrar_Peca();
				break;
			case KEY_RIGHT:
				Apagar_Peca();
				Mover_Peca(+1);
				Mostrar_Peca();
				break;
			
			case KEY_DOWN:
				Apagar_Peca();
				if ((end = Descer_Peca()) != -1 && end >= 0) Score(end);
				Mostrar_Tabuleiro();
				Mostrar_Peca();
				break;
			default:
				Apagar_Peca();
				if (Tempo_Jogo()) if ((end = Descer_Peca()) != -1 && end >= 0) Score(end);
				Mostrar_Tabuleiro();
				Mostrar_Peca();
				break;
		}
		mvprintw(SCREEN_BOTTOM+1, CENTER(18),"%.18i", Score(0)); refresh();
	}
	
	if (end == -1) {
		mvaddstr(SCR_HEIGHT_ADD-1, CENTER(strlen("GAME OVER")),"GAME OVER");
		Score(-1);
	}
	else mvaddstr(SCR_HEIGHT_ADD-1, CENTER(strlen("PAUSED")),"PAUSED");
	
	refresh();
}
int Testar_Interface() {
	int ch, i, j;
	
	if (SCREEN_HEIGHT < 22 || SCREEN_WIDTH < 22) return 0;
	
	set_frame();
	
	for (i = 0; i < CANVAS_HEIGHT; i++) for (j = 0; j < CANVAS_WIDTH; j++) Inver_Bloco(i,j);
	Mostrar_Tabuleiro();refresh();

	metronomy(0.1,0);
	for (i = 0; i < CANVAS_HEIGHT+1; i++) {
		Mostrar_Tabuleiro();refresh();
		Reciclar_Linha(19);
		while( !(Tempo_Espera()) && (getch()) != KEY_SPACE) {}
	}
	metronomy(3,0);
	
	mvaddstr(SCR_HEIGHT_ADD + 1, CENTER(strlen(name)),name);
	// mvprintw(SCR_HEIGHT_ADD + 2, CENTER(strlen("Width: ") + numlen(SCREEN_WIDTH)),"Width: %i", SCREEN_WIDTH); // %.3i
	// mvprintw(SCR_HEIGHT_ADD + 3, CENTER(strlen("Height: ") + numlen(SCREEN_HEIGHT)),"Height: %i", SCREEN_HEIGHT);
	
	mvaddstr(SCR_HEIGHT_ADD + 3, CENTER(strlen("_______________")), "_______________");

	mvaddstr(SCR_HEIGHT_ADD + 6, CENTER(strlen(dev_name)), dev_name);
	mvaddstr(SCR_HEIGHT_ADD + 7, CENTER(strlen(email)), email);

	mvaddstr(SCREEN_BOTTOM - 1, CENTER(strlen("USE ARROW KEYS")), "USE ARROW KEYS");
	
	Iniciar_Peca(rand()%7);
	Centralizar_Peca();
	Mostrar_Peca();
	
	refresh();
	
	while ( (i = Tempo_Espera()) || (ch = getch()) != KEY_SPACE ) {
		
		switch (ch) {
			case KEY_UP:
				clean_menu_interface();
				mvaddstr(SCREEN_BOTTOM - 1,(SCREEN_WIDTH - strlen("UP"))/2, "UP");
				
				Apagar_Peca();
				Rotacionar_Peca();
				Mostrar_Peca();
				break;
			case KEY_DOWN:
				clean_menu_interface();
				mvaddstr(SCR_HEIGHT_ADD+15,CENTER(8), "vvvvvvvv");
				mvaddstr(SCREEN_BOTTOM - 1,CENTER(strlen("DOWN")), "DOWN");
				break;
			case KEY_LEFT:
				clean_menu_interface();
				for(i = 0; i < 4; i++) mvaddch(SCR_HEIGHT_ADD+11+i,CENTER(8) - 1, '<');
				mvaddstr(SCREEN_BOTTOM - 1,CENTER(strlen("LEFT")), "LEFT");
				break;
			case KEY_RIGHT:
				clean_menu_interface();
				for(i = 0; i < 4; i++) mvaddch(SCR_HEIGHT_ADD+11+i,CENTER(8) + 8, '>');
				mvaddstr(SCREEN_BOTTOM - 1,CENTER(strlen("RIGHT")), "RIGHT");
				break;
			default:
				if(i) {
					clean_menu_interface();
					mvaddstr(SCREEN_BOTTOM - 1,CENTER(strlen("SCAPE WITH SPACE")), "SCAPE WITH SPACE");
					
					Apagar_Peca();
					Iniciar_Peca(rand()%7);
					Centralizar_Peca();
					Mostrar_Peca();
				}
		}
		
		
		refresh();
	}
	
	return 1;
}
void Mostrar_Score() {
	
}
