#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <assert.h>

#include "main.h"
#include "peca.h"
#include "metronomo.h"
#include "tabuleiro.h"

#define KEY_SPACE			32
#define numlen(X) 			((X > 9) ? (X > 99) ? (X > 999) ? (X > 9999) ? (X > 99999) ? (X > 999999) ? (X > 9999999) ? 8 : 7 : 6 : 5 : 4 : 3 : 2 : 1)
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

#define SHAR_MESSAGE		"- FREAK +"
#define HARD_MESSAGE		"- HARD +"
#define NORM_MESSAGE		"- NOMAL +"
#define EASY_MESSAGE		"- EASY +"


// Global Vars
ClassPeca PECA_PRI;
int SCREEN_WIDTH, SCREEN_HEIGHT;

void display_piece (int ON) {
	for (int i = 0; i < 4; i++) if (BETWEEN(PECA_PRI.CoordY(i),0,20) && BETWEEN(PECA_PRI.CoordX(i),0,9)) {
		if (ON) mvaddstr((SCR_HEIGHT_ADD + PECA_PRI.CoordY(i)), (SCR_WIDTH_ADD + (PECA_PRI.CoordX(i))*2), 	"[]");
		else 	mvaddstr((SCR_HEIGHT_ADD + PECA_PRI.CoordY(i)), (SCR_WIDTH_ADD + (PECA_PRI.CoordX(i))*2), 	"  ");
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
	int j = SCR_HEIGHT_ADD + 3 + i*4, k;
	clrline(j);
	if (i == 0) mvaddstr(j,CENTER(strlen("+ PLAY +")), "+ PLAY +");
	if (i == 1) mvaddstr(j,CENTER(strlen("+ SCORE +")), "+ SCORE +");
	if (i == 2) {
		switch (k = 10*Espera_Jogo()) {
			case 3:
				mvaddstr(j,CENTER(strlen(SHAR_MESSAGE)), SHAR_MESSAGE);
				break;
			case 5:
				mvaddstr(j,CENTER(strlen(HARD_MESSAGE)), HARD_MESSAGE);
				break;
			case 10:
				mvaddstr(j,CENTER(strlen(NORM_MESSAGE)), NORM_MESSAGE);
				break;
			case 20:
				mvaddstr(j,CENTER(strlen(EASY_MESSAGE)), EASY_MESSAGE);
				break;
		}
	}
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
long Score(long i) {
	static long score;
	if (i < 0) {
		score = 0;
		// ADD SCORE TO BOARD
	}
	else score += i*60/(Espera_Jogo());

	return score;
}
void Mover_Peca (int i) {
	bool ALERT_INTERSECTION = false;
	
	int j;
	
	for (j = 0; j < 4; j++) {
		if (	!(BETWEEN(PECA_PRI.CoordX(j) + i, 0, CANVAS_WIDTH-1)) ||
				Valor_Bloco(PECA_PRI.CoordY(j) , PECA_PRI.CoordX(j) + i)	) ALERT_INTERSECTION = true;
	}
	
	if (ALERT_INTERSECTION == false) PECA_PRI.X += i;
}
int Descer_Peca () {
	
	int i, LINES_WRAPPED = 0, min_y = 1;
	
	bool ALERT_INTERSECTION = false, ALERT_OVER = false, CHECK_LINES[4];
	
	if (PECA_PRI.Y < 19) { 
		for (i = 0; i < 4; i++) {
			if (Valor_Bloco(PECA_PRI.CoordY(i) + 1 , PECA_PRI.CoordX(i))) ALERT_INTERSECTION = true;
			if (PECA_PRI.CoordY(i) < 0) ALERT_OVER = true;
		}
		if (ALERT_INTERSECTION) {
			if (ALERT_OVER) return -1;
		} else {
			PECA_PRI.Y++;
			Passar_Ciclo();
			
			return 0;
		}
	}
	
	for (i = 0; i < 4; i++) {
		Inver_Bloco(PECA_PRI.CoordY(i) , PECA_PRI.CoordX(i));
		
		CHECK_LINES[PECA_PRI.BLOCO[i].Y + 3] = true;
	}
	
	for (i = 0; i < 4; i++) if(CHECK_LINES[i])
		LINES_WRAPPED = (Reciclar_Linha(PECA_PRI.Y + i - 3)) ? LINES_WRAPPED+1 : LINES_WRAPPED;
	
	PECA_PRI.Iniciar_Peca(rand()%7);
	
	Passar_Ciclo();
	
	return LINES_WRAPPED;
}
void Rotacionar_Peca_Check () {
	bool ALERT_INTERSECTION = false, ALERT_INTERSECTION_LEFT = false, ALERT_INTERSECTION_RIGHT = false;
	int i;
	
	ClassPeca PECA_ATUAL = PECA_PRI;
	
	PECA_ATUAL.Rotacionar_Peca();
	
	for (i = 0; i < 4; i++) {
		if (!(BETWEEN(PECA_ATUAL.CoordX(i), 0, CANVAS_WIDTH-1)) ||
			(Valor_Bloco(PECA_ATUAL.CoordY(i) , PECA_ATUAL.CoordX(i)))) ALERT_INTERSECTION = true;
		if (!(BETWEEN(PECA_ATUAL.CoordX(i)-1, 0, CANVAS_WIDTH-1)) ||
			(Valor_Bloco(PECA_ATUAL.CoordY(i) , PECA_ATUAL.CoordX(i)-1))) ALERT_INTERSECTION_LEFT = true;
		if (!(BETWEEN(PECA_ATUAL.CoordX(i)+1, 0, CANVAS_WIDTH-1)) ||
			(Valor_Bloco(PECA_ATUAL.CoordY(i) , PECA_ATUAL.CoordX(i)+1))) ALERT_INTERSECTION_RIGHT = true;
	}

	if (ALERT_INTERSECTION) {
		if (!(ALERT_INTERSECTION_LEFT)) {
			PECA_PRI.X--;
			PECA_PRI.Rotacionar_Peca();
		} else if (!(ALERT_INTERSECTION_RIGHT)) {
			PECA_PRI.X++;
			PECA_PRI.Rotacionar_Peca();
		}
	} else PECA_PRI.Rotacionar_Peca();
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
	getmaxyx(stdscr,SCREEN_HEIGHT,SCREEN_WIDTH); // just in case you wonder: it's a MACRO
	
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
	Desligar_Espera();
	
	// NCURSES
	endwin();				// end curses mode
}
int Capturar_Opcao() {
	int ch, j, i;

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
				if (i == 2) {
					switch (j = 10*Espera_Jogo()) {
						case 5:
							Mudar_Tempo_Jogo(0.3);
							break;
						case 10:
							Mudar_Tempo_Jogo(0.5);
							break;
						case 20:
							Mudar_Tempo_Jogo(1);
							break;
						default:
							break;
					}
				}
				turn_on(i);
				break;
			case KEY_RIGHT:
				if (i == 2) {
					switch (j = 10*Espera_Jogo()) {
						case 3:
							Mudar_Tempo_Jogo(0.5);
							break;
						case 5:
							Mudar_Tempo_Jogo(1);
							break;
						case 10:
							Mudar_Tempo_Jogo(2);
							break;
						default:
							break;
					}
				}
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
		PECA_PRI.Iniciar_Peca(rand()%7);
		Reciclar_Tabul();
		end = 0;
	}
	
	Mostrar_Tabuleiro();
	Mostrar_Peca();
	
	while ( (end != -1) && (ch = getch()) != KEY_SPACE) {
		switch (ch) {
			case KEY_UP:
				Apagar_Peca();
				Rotacionar_Peca_Check();
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

		assert(Score(0) < LONG_MAX - 120);
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

	metronomy(0.05,0);
	for (i = 0; i < CANVAS_HEIGHT+1; i++) {
		Mostrar_Tabuleiro();refresh();
		Reciclar_Linha(19);
		while( !(Tempo_Espera()) && (getch()) != KEY_SPACE) {}
	}
	metronomy(4,0);
	
	mvaddstr(SCR_HEIGHT_ADD + 1, CENTER(strlen(name)),name);
	
	mvaddstr(SCR_HEIGHT_ADD + 3, CENTER(strlen("_______________")), "_______________");

	mvaddstr(SCR_HEIGHT_ADD + 6, CENTER(strlen(dev_name)), dev_name);
	mvaddstr(SCR_HEIGHT_ADD + 7, CENTER(strlen(email)), email);

	mvaddstr(SCREEN_BOTTOM - 1, CENTER(strlen("USE ARROW KEYS")), "USE ARROW KEYS");
	
	PECA_PRI.Iniciar_Peca(rand()%7);
	
	PECA_PRI.Y = 14;
	PECA_PRI.X = 5;
	
	refresh();
	
	while ( (i = Tempo_Espera()) || (ch = getch()) != KEY_SPACE ) {
		
		switch (ch) {
			case KEY_UP:
				clean_menu_interface();
				mvaddstr(SCREEN_BOTTOM - 1,(SCREEN_WIDTH - strlen("UP"))/2, "UP");
				
				Apagar_Peca();
				PECA_PRI.Rotacionar_Peca();
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
					
					PECA_PRI.Iniciar_Peca(rand()%7);
					
					PECA_PRI.Y = 14;
					PECA_PRI.X = 5;
					
					Mostrar_Peca();
				}
		}
		
		
		refresh();
	}
	
	return 1;
}
void Mostrar_Score() {
	
}

int main (int argc, char *argv[]) {
	int i;

	Iniciar_Modulos();
	
	if ((i = Testar_Interface())) {
		while ((i = Capturar_Opcao()) != 3) {
			if (i == 0) Jogar();
			if (i == 1) Mostrar_Score();
		}
	}
	
	Finalizar_Modulos();

	return 0;
}
