#include "metronomo.h++"
#include "tabuleiro.h++"
#include "peca.h++"
#include "game.h++"
#include "main.h++"

#include <ncurses.h>

ClassGame::ClassGame () {
	srand (time(NULL));
	Game_Play = false;
	Game_Pause = false;
	Game_Score = 0;
}
void ClassGame::Events() {
	int ch;
	static bool render = true;
	
	Game_Pause = false;
	if (!Game_Play) {
		PECA_PRI.Iniciar_Peca(rand()%7);
		TABULEIRO_PRI.Reciclar_Tabul();
		Game_Score = 0;
		Game_Play = true;
	}
	
	while (!render && (ch = getch()) != KEY_SPACE) {
		switch (ch) {
			case KEY_UP:
				render = Rotacionar_Peca_Check();
				break;
			case KEY_LEFT:
				render = Mover_Peca(-1);
				break;
			case KEY_RIGHT:
				render = Mover_Peca(+1);
				break;
			case KEY_DOWN:
				Game_Score += Descer_Peca()*60/(TEMPO.ViewTempo());
				TEMPO.FalseFire();
				render = true;
				break;
			default:
				if (TEMPO.Tempo()) {
					Game_Score += Descer_Peca()*60/(TEMPO.ViewTempo());
					render = true;
				}
				break;
		}
	} if (ch == KEY_SPACE) Game_Pause = true;
	
	render = false;
}
bool ClassGame::Mover_Peca (int i) {
	bool ALERT_INTERSECTION = false;
	
	int j;
	
	for (j = 0; j < 4; j++) {
		if (	!(BETWEEN(PECA_PRI.CoordX(j) + i, 0, CANVAS_WIDTH-1)) ||
				TABULEIRO_PRI.Valor_Bloco(PECA_PRI.CoordY(j) , PECA_PRI.CoordX(j) + i)	) ALERT_INTERSECTION = true;
	}
	
	if (ALERT_INTERSECTION == false) PECA_PRI.X += i;
	else return false;
	
	return true;
}
int ClassGame::Descer_Peca () {
	int LINES_WRAPPED = 0;
	bool 	ALERT_INTERSECTION = false,
			ALERT_OVER = false, 
			CHECK_LINES[] = {false, false, false, false};
	
	if (PECA_PRI.Y < 19) { 
		for (int i = 0; i < 4; i++) {
			if (TABULEIRO_PRI.Valor_Bloco(PECA_PRI.CoordY(i) + 1 , PECA_PRI.CoordX(i)))
				ALERT_INTERSECTION = true;
			if (PECA_PRI.CoordY(i) < 0)
				ALERT_OVER = true;
		}
	} else ALERT_INTERSECTION = true;
	
	if (!ALERT_INTERSECTION) PECA_PRI.Y++;
	else if (ALERT_OVER) Game_Play = false;
	else {
		for (int i = 0; i < 4; i++) {
			TABULEIRO_PRI.Inver_Bloco(PECA_PRI.CoordY(i) , PECA_PRI.CoordX(i));
			CHECK_LINES[PECA_PRI.BLOCO[i].Y + 3] = true;
		}
		for (int i = 0; i < 4; i++) 
			if(CHECK_LINES[i])
				LINES_WRAPPED = (TABULEIRO_PRI.Reciclar_Linha(PECA_PRI.Y + i - 3)) ? LINES_WRAPPED+1 : LINES_WRAPPED;
		
		PECA_PRI.Iniciar_Peca(rand()%7);
	}
	
	return LINES_WRAPPED;
}
bool ClassGame::Rotacionar_Peca_Check () {
	bool 	ALERT_INTERSECTION = false,
			ALERT_INTERSECTION_LEFT = false, 
			ALERT_INTERSECTION_RIGHT = false;
	
	ClassPeca PECA_ATUAL = PECA_PRI;
	
	PECA_ATUAL.Rotacionar_Peca();
	
	for (int i = 0; i < 4; i++) {
		if (!(BETWEEN(PECA_ATUAL.CoordX(i), 0, CANVAS_WIDTH-1)) ||
			(TABULEIRO_PRI.Valor_Bloco(PECA_ATUAL.CoordY(i) , PECA_ATUAL.CoordX(i)))) ALERT_INTERSECTION = true;
		if (!(BETWEEN(PECA_ATUAL.CoordX(i)-1, 0, CANVAS_WIDTH-1)) ||
			(TABULEIRO_PRI.Valor_Bloco(PECA_ATUAL.CoordY(i) , PECA_ATUAL.CoordX(i)-1))) ALERT_INTERSECTION_LEFT = true;
		if (!(BETWEEN(PECA_ATUAL.CoordX(i)+1, 0, CANVAS_WIDTH-1)) ||
			(TABULEIRO_PRI.Valor_Bloco(PECA_ATUAL.CoordY(i) , PECA_ATUAL.CoordX(i)+1))) ALERT_INTERSECTION_RIGHT = true;
	}

	if (ALERT_INTERSECTION) {
		if (!(ALERT_INTERSECTION_LEFT)) {
			PECA_PRI.X--;
			PECA_PRI.Rotacionar_Peca();
		} else if (!(ALERT_INTERSECTION_RIGHT)) {
			PECA_PRI.X++;
			PECA_PRI.Rotacionar_Peca();
		} else return false;
	} else PECA_PRI.Rotacionar_Peca();
	
	return true;
}
