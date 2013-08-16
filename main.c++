#include <ncurses.h>
#include <limits.h>
#include <assert.h>
#include <string.h>

#include "main.h++"
#include "peca.h++"
#include "metronomo.h++"
#include "tabuleiro.h++"
#include "game.h++"

#define KEY_SPACE			32
#define SCR_WIDTH_ADD		(SCREEN_WIDTH - 22)/2 + 1
#define SCR_HEIGHT_ADD		(SCREEN_HEIGHT - 22)/2 + 1
#define CENTER(X)			SCR_WIDTH_ADD + (CANVAS_WIDTH*2 - (X))/2
#define SCREEN_BOTTOM		SCR_HEIGHT_ADD + 19

#define GAME_NAME			"+ TETRIS +"
#define DEV_MAIL			"me@tmergulhao.com"
#define DEV_NAME			"Tiago Mergulhão"
#define final_words			"BYE!"

#define SHAR_MESSAGE		"- FREAK +"
#define HARD_MESSAGE		"- HARD +"
#define NORM_MESSAGE		"- NOMAL +"
#define EASY_MESSAGE		"- EASY +"

class ClassCurses {
		ClassGame* GAME;
		ClassMetronomy T_INTERFACE, T_JOGO;
		int SCREEN_WIDTH, SCREEN_HEIGHT;
	public:
		ClassCurses();
		~ClassCurses();
		
		void Mostrar_Score() {}
		int Testar_Interface(ClassGame *GAME_DUM);
		int Capturar_Opcao();
		void Jogar(ClassGame *GAME_DUM);
		
		void Apagar_Peca();
		void Mostrar_Peca();
		void clrline (int i);
		void set_frame ();
		void turn_on (int i);
		void turn_off (int i);
		void clean_menu_interface ();
		void Mostrar_Tabuleiro ();
};
ClassCurses::ClassCurses() {
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
}
ClassCurses::~ClassCurses() {
	clrline(0);
	mvaddstr(SCR_HEIGHT_ADD+(20/2), CENTER(strlen(final_words)), final_words);
	while( !(T_INTERFACE.Tempo()) && (getch()) != KEY_SPACE) {}
	
	endwin();
}

void ClassCurses::Mostrar_Peca () {
	for (int i = 0; i < 4; i++) 
		if (BETWEEN(GAME->PECA_PRI.CoordY(i),0,20) && BETWEEN(GAME->PECA_PRI.CoordX(i),0,9))
			mvaddstr((SCR_HEIGHT_ADD + GAME->PECA_PRI.CoordY(i)), (SCR_WIDTH_ADD + (GAME->PECA_PRI.CoordX(i))*2), 	"[]");
}
void ClassCurses::Apagar_Peca () {
	for (int i = 0; i < 4; i++) 
		if (BETWEEN(GAME->PECA_PRI.CoordY(i),0,20) && BETWEEN(GAME->PECA_PRI.CoordX(i),0,9))
			mvaddstr((SCR_HEIGHT_ADD + GAME->PECA_PRI.CoordY(i)), (SCR_WIDTH_ADD + (GAME->PECA_PRI.CoordX(i))*2), 	"  ");
}
void ClassCurses::clrline (int i) {
	if (i) mvaddstr(i, SCR_WIDTH_ADD, "                    ");
	else for (i = 0; i<20; i++) clrline (SCR_HEIGHT_ADD + i); // CLEARS ALL GAME LINES 20*20
}
void ClassCurses::set_frame () {
	int i;

	for (i = 0; i < 20; i++) {
		mvaddch(SCR_HEIGHT_ADD+i, SCR_WIDTH_ADD-1, '|');
		mvaddch(SCR_HEIGHT_ADD+i, SCR_WIDTH_ADD-1+21, '|');
	}
	mvaddstr(SCR_HEIGHT_ADD-1,SCR_WIDTH_ADD-1, "/¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\\");
	mvaddstr(SCR_HEIGHT_ADD+20,SCR_WIDTH_ADD-1, "\\____________________/");

	refresh();
}
void ClassCurses::turn_off (int i) {
	int j = SCR_HEIGHT_ADD + 3 + i*4;
	clrline(j);
	if (i == 0) mvaddstr(j,CENTER(strlen("PLAY")), "PLAY");
	if (i == 1) mvaddstr(j,CENTER(strlen("SCORE")), "SCORE");
	if (i == 2) mvaddstr(j,CENTER(strlen("TIMEOUT")), "TIMEOUT");
	if (i == 3) mvaddstr(j,CENTER(strlen("EXIT")), "EXIT");
}
void ClassCurses::turn_on (int i) {
	int j = SCR_HEIGHT_ADD + 3 + i*4, k;
	clrline(j);
	if (i == 0) mvaddstr(j,CENTER(strlen("+ PLAY +")), "+ PLAY +");
	if (i == 1) mvaddstr(j,CENTER(strlen("+ SCORE +")), "+ SCORE +");
	if (i == 2) {
		switch (k = 10*T_JOGO.ViewTempo()) {
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
void ClassCurses::clean_menu_interface () {
	int i;
	clrline(SCREEN_BOTTOM - 1);
	clrline(SCR_HEIGHT_ADD+15);
	for(i = 0; i < 4; i++) {
		mvaddch(SCR_HEIGHT_ADD+11+i, CENTER(8) + 8, ' ');
		mvaddch(SCR_HEIGHT_ADD+11+i, CENTER(8) - 1, ' ');
	}
}
void ClassCurses::Mostrar_Tabuleiro () {
	for (int i = 0; i < CANVAS_HEIGHT; i++) 
		for (int j = 0; j < CANVAS_WIDTH; j++) 
			if (GAME->TABULEIRO_PRI.Valor_Bloco(i,j)) 
				mvaddstr((SCR_HEIGHT_ADD + i), (SCR_WIDTH_ADD + j*2), 	"[]");
			else
				mvaddstr((SCR_HEIGHT_ADD + i), (SCR_WIDTH_ADD + j*2), 	"  ");
}

// INTERFACES EXTERNAS
int ClassCurses::Capturar_Opcao() {
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
			case KEY_RIGHT:
				if (i == 2) {
					switch (j = T_JOGO.ViewTempo()*10) {
						case 5:
							T_JOGO.SetTempo(0.3);
							break;
						case 10:
							T_JOGO.SetTempo(0.5);
							break;
						case 20:
							T_JOGO.SetTempo(1);
							break;
						default:
							break;
					}
				}
				turn_on(i);
				break;
			case KEY_LEFT:
				if (i == 2) {
					switch (j = T_JOGO.ViewTempo()*10) {
						case 3:
							T_JOGO.SetTempo(0.5);
							break;
						case 5:
							T_JOGO.SetTempo(1);
							break;
						case 10:
							T_JOGO.SetTempo(2);
							break;
						default:
							break;
					}
				}
				turn_on(i);
				break;
			default:
				if (T_INTERFACE.Tempo()) mvaddstr(SCREEN_BOTTOM - 1,CENTER(strlen("SELECT WITH SPACE")), "SELECT WITH SPACE");
		}
		refresh();
	}
	return 0;
}
void ClassCurses::Jogar(ClassGame *GAME_DUM) {
	int ch;
	static int end;
	
	GAME = GAME_DUM;
	
	clear();
	set_frame();
	
	if (GAME->Game_Score == 0 || end == -1) {
		GAME->PECA_PRI.Iniciar_Peca(rand()%7);
		GAME->TABULEIRO_PRI.Reciclar_Tabul();
		end = 0;
	}
	
	Mostrar_Tabuleiro();
	Mostrar_Peca();
	
	while ( (end != -1) && (ch = getch()) != KEY_SPACE) {
		switch (ch) {
			case KEY_UP:
				Apagar_Peca();
				GAME->Rotacionar_Peca_Check();
				Mostrar_Peca();
				break;
			case KEY_LEFT:
				Apagar_Peca();
				GAME->Mover_Peca(-1);
				Mostrar_Peca();
				break;
			case KEY_RIGHT:
				Apagar_Peca();
				GAME->Mover_Peca(+1);
				Mostrar_Peca();
				break;
			
			case KEY_DOWN:
				Apagar_Peca();
				if ((end = GAME->Descer_Peca()) != -1 && end >= 0) {
					GAME->Game_Score += end*60/(T_JOGO.ViewTempo());
					T_JOGO.FalseFire();
				}
				Mostrar_Tabuleiro();
				Mostrar_Peca();
				break;
			default:
				Apagar_Peca();
				if (T_JOGO.Tempo()) if ((end = GAME->Descer_Peca()) != -1 && end >= 0) {
					GAME->Game_Score = 0;
					T_JOGO.FalseFire();
				}
				Mostrar_Tabuleiro();
				Mostrar_Peca();
				break;
		}
		mvprintw(SCREEN_BOTTOM+1, CENTER(18),"%.18i", GAME->Game_Score); refresh();

		assert(GAME->Game_Score < LONG_MAX - 120);
	}
	
	if (end == -1) {
		mvaddstr(SCR_HEIGHT_ADD-1, CENTER(strlen("GAME OVER")),"GAME OVER");
		GAME->Game_Score = 0;
	}
	else mvaddstr(SCR_HEIGHT_ADD-1, CENTER(strlen("PAUSED")),"PAUSED");
	
	refresh();
}
int ClassCurses::Testar_Interface(ClassGame *GAME_DUM) {
	int ch, i, j;
	
	GAME = GAME_DUM;
	
	if (SCREEN_HEIGHT < 22 || SCREEN_WIDTH < 22) return 0;
	
	set_frame();
	
	for (i = 0; i < CANVAS_HEIGHT; i++) for (j = 0; j < CANVAS_WIDTH; j++) GAME->TABULEIRO_PRI.Inver_Bloco(i,j);
	Mostrar_Tabuleiro();refresh();

	T_INTERFACE.SetTempo(0.05);
	for (i = 0; i < CANVAS_HEIGHT+1; i++) {
		Mostrar_Tabuleiro();refresh();
		GAME->TABULEIRO_PRI.Reciclar_Linha(19);
		while( !(T_INTERFACE.Tempo()) && (getch()) != KEY_SPACE) {}
	}
	T_INTERFACE.SetTempo(4);
	
	mvaddstr(SCR_HEIGHT_ADD + 1, CENTER(strlen(GAME_NAME)),GAME_NAME);
	
	mvaddstr(SCR_HEIGHT_ADD + 3, CENTER(strlen("_______________")), "_______________");

	mvaddstr(SCR_HEIGHT_ADD + 6, CENTER(strlen(DEV_NAME)), DEV_NAME);
	mvaddstr(SCR_HEIGHT_ADD + 7, CENTER(strlen(DEV_MAIL)), DEV_MAIL);

	mvaddstr(SCREEN_BOTTOM - 1, CENTER(strlen("USE ARROW KEYS")), "USE ARROW KEYS");
	
	GAME->PECA_PRI.Iniciar_Peca(rand()%7);
	
	GAME->PECA_PRI.Y = 14;
	GAME->PECA_PRI.X = 5;
	
	refresh();
	
	while ( (i = T_INTERFACE.Tempo()) || (ch = getch()) != KEY_SPACE ) {
		
		switch (ch) {
			case KEY_UP:
				clean_menu_interface();
				mvaddstr(SCREEN_BOTTOM - 1,(SCREEN_WIDTH - strlen("UP"))/2, "UP");
				
				Apagar_Peca();
				GAME->PECA_PRI.Rotacionar_Peca();
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
					
					GAME->PECA_PRI.Iniciar_Peca(rand()%7);
					
					GAME->PECA_PRI.Y = 14;
					GAME->PECA_PRI.X = 5;
					
					Mostrar_Peca();
				}
		}
		
		
		refresh();
	}
	
	return 1;
}

int main (int argc, char *argv[]) {
	ClassGame 		GAME;
	ClassCurses 	W_CURSES;
	
	int i;
	
	W_CURSES.Testar_Interface(&GAME);
	
	while ((i = W_CURSES.Capturar_Opcao()) != 3) {
		if (i == 0) W_CURSES.Jogar(&GAME);
		if (i == 1) W_CURSES.Mostrar_Score();
	}
	
	return 0;
}
