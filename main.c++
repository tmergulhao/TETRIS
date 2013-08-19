#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>

#include "main.h++"
#include "peca.h++"
#include "metronomo.h++"
#include "tabuleiro.h++"
#include "game.h++"
#include "textures.h++"

#define GAME_NAME			"+ TETRIS +"
#define DEV_MAIL			"me@tmergulhao.com"
#define DEV_NAME			"Tiago Mergulhão"
#define final_words			"BYE!"

#define SHAR_MESSAGE		"- FREAK +"
#define HARD_MESSAGE		"- HARD +"
#define NORM_MESSAGE		"- NOMAL +"
#define EASY_MESSAGE		"- EASY +"

#define BLOCK_SIZE			30

class ClassSDL {
		bool Running;
		
		SDL_Window* Window;
		SDL_Renderer* Renderer;
		
		ClassMetronomy TEMPO;
		
		void Mostrar_Tabuleiro();
		void Mostrar_Peca();
	public:
		ClassGame *GAME;
		
		ClassSDL(const char *title, int xpos, int ypos, int width, int height, int flags);
		~ClassSDL();
		
		void test();
		bool running() { return Running; }
		void render();
		void update(){}
		void handleEvents();
};
ClassSDL::ClassSDL (const char *title, int xpos, int ypos, int width, int height, int flags) {
	if(SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		Window = SDL_CreateWindow(	title,
									xpos,
									ypos,
									width, height,
									flags);
		if(Window != 0) Renderer = SDL_CreateRenderer(Window, -1, 0);
	}
	
	TEXTURES::instance()->load ("assets/blocks.png","blocks", Renderer);
	
	Running = true;
}
ClassSDL::~ClassSDL () {
	SDL_ShowSimpleMessageBox(1 , 
						"TETRIS", 
						"Thank you for playing TETRIS by Tiago Mergulhão.\n\nGo to tmergulhao.com/TETRIS for more info.",
						Window);
	
	SDL_DestroyWindow(Window);
	SDL_DestroyRenderer(Renderer);
	SDL_Quit();
}
/*
void ClassCurses::Mostrar_Score() {}
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
	for (int i = 0; i < 20; i++) {
		mvaddch(SCR_HEIGHT_ADD+i, SCR_WIDTH_ADD-1, '|');
		mvaddch(SCR_HEIGHT_ADD+i, SCR_WIDTH_ADD-1+21, '|');
	}
	mvaddstr(SCR_HEIGHT_ADD-1,SCR_WIDTH_ADD-1, "/¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\\");
	mvaddstr(SCR_HEIGHT_ADD+20,SCR_WIDTH_ADD-1, "\\____________________/");
	refresh();
}
void ClassCurses::TurnMenu (int i, bool ON) {
	int LOCATION;
	clrline(LOCATION = SCR_HEIGHT_ADD + 3 + i*4);
	
	switch (i) {
		case 0:
			if (ON) mvaddstr(LOCATION,CENTER(strlen("+ PLAY +")), "+ PLAY +");
			else mvaddstr(LOCATION,CENTER(strlen("PLAY")), "PLAY");
			break;
		case 1:
			if (ON) mvaddstr(LOCATION,CENTER(strlen("+ SCORE +")), "+ SCORE +");
			else mvaddstr(LOCATION,CENTER(strlen("SCORE")), "SCORE");
			break;
		case 3:
			if (ON) mvaddstr(LOCATION,CENTER(strlen("+ EXIT +")), "+ EXIT +");
			else if (i == 3) mvaddstr(LOCATION,CENTER(strlen("EXIT")), "EXIT");
			break;
		case 2:
			if (ON) {
				switch ((int)(10*GAME->TEMPO.ViewTempo())) {
					case 3:
						if (ON) mvaddstr(LOCATION,CENTER(strlen(SHAR_MESSAGE)), SHAR_MESSAGE);
						break;
					case 5:
						if (ON) mvaddstr(LOCATION,CENTER(strlen(HARD_MESSAGE)), HARD_MESSAGE);
						break;
					case 10:
						if (ON) mvaddstr(LOCATION,CENTER(strlen(NORM_MESSAGE)), NORM_MESSAGE);
						break;
					case 20:
						if (ON) mvaddstr(LOCATION,CENTER(strlen(EASY_MESSAGE)), EASY_MESSAGE);
						break;
				}
			} else mvaddstr(LOCATION,CENTER(strlen("TIMEOUT")), "TIMEOUT");
			break;
	}
}
void ClassCurses::clean_menu_interface () {
	clrline(SCREEN_BOTTOM - 1);
	for(int i = 0; i < 5; i++)
		clrline(SCR_HEIGHT_ADD+11+i);
}

// INTERFACES EXTERNAS
int ClassCurses::Capturar_Opcao(ClassGame *GAME_DUM) {
	int ch;
	static int i;
	GAME = GAME_DUM;
	
	clrline(0);
	for (int j = 0; j < 4; j++) TurnMenu(j, false);
							TurnMenu(i, true);
	refresh();
	
	while ((ch = getch()) != KEY_SPACE) {
		switch (ch) {
			case KEY_UP:
				TurnMenu(i, false);
				i = (i == 0) ? 3 : (i-1)%4;
				TurnMenu(i, true);
				break;
			case KEY_DOWN:
				TurnMenu(i, false);
				i = (i+1)%4;
				TurnMenu(i, true);
				break;
			case KEY_RIGHT:
				if (i != 2) break;
			case KEY_LEFT:
				if (i == 2) {
					switch ((int)(GAME->TEMPO.ViewTempo()*10)) {
						case 3:
							if (ch == KEY_LEFT) GAME->TEMPO.SetTempo(0.5);
							else if (ch == KEY_RIGHT) {}
							break;
						case 5:
							if (ch == KEY_LEFT) GAME->TEMPO.SetTempo(1);
							else if (ch == KEY_RIGHT) GAME->TEMPO.SetTempo(0.3);
							break;
						case 10:
							if (ch == KEY_LEFT) GAME->TEMPO.SetTempo(2);
							else if (ch == KEY_RIGHT) GAME->TEMPO.SetTempo(0.5);
							break;
						case 20:
							if (ch == KEY_LEFT) {}
							else if (ch == KEY_RIGHT)  GAME->TEMPO.SetTempo(1);
							break;
					}
					TurnMenu(2, true);
				}
				break;
			default:
				if (TEMPO.Tempo()) mvaddstr(SCREEN_BOTTOM - 1,CENTER(strlen("SELECT WITH SPACE")), "SELECT WITH SPACE");
		}
		refresh();
	}
	return i;
}
void ClassCurses::Render (ClassGame *GAME_DUM) {
	GAME = GAME_DUM;
	
	clear();
	set_frame();
	
	Mostrar_Tabuleiro();
	Mostrar_Peca();
	
	mvaddstr(SCR_HEIGHT_ADD - 1, CENTER(strlen(GAME_NAME)),GAME_NAME);
	mvprintw(SCREEN_BOTTOM+1, CENTER(18),"%.18i", GAME->Game_Score);
	assert(GAME->Game_Score < LONG_MAX - 120);
	
	if (!GAME->Game_Play) {
		mvaddstr(SCR_HEIGHT_ADD-1, CENTER(strlen("+ GAME OVER +")),"+ GAME OVER +");
	}
	else if (GAME->Game_Pause) {
		mvaddstr(SCR_HEIGHT_ADD-1, CENTER(strlen("+ PAUSED +")),"+ PAUSED +");
	}
	
	refresh();
}
*/
/*int ClassSDL::test(ClassGame *GAME_DUM) {
	GAME = GAME_DUM;
	int ch;
	
	
	
	if (SCREEN_HEIGHT < 22 || SCREEN_WIDTH < 22) return 0;
	
	set_frame();
	
	for (int i = 0; i < CANVAS_HEIGHT; i++) for (int j = 0; j < CANVAS_WIDTH; j++) GAME->TABULEIRO_PRI.Inver_Bloco(i,j);
	Mostrar_Tabuleiro();refresh();
	TEMPO.SetTempo(0.05);
	for (int i = 0; i < CANVAS_HEIGHT+1; i++) {
		Mostrar_Tabuleiro();refresh();
		GAME->TABULEIRO_PRI.Reciclar_Linha(19);
		while( !(TEMPO.Tempo()) && (getch()) != KEY_SPACE) {}
	}
	TEMPO.SetTempo(4);
	
	mvaddstr(SCR_HEIGHT_ADD + 1, CENTER(strlen(GAME_NAME)),GAME_NAME);
	
	mvaddstr(SCR_HEIGHT_ADD + 3, CENTER(strlen("_______________")), "_______________");

	mvaddstr(SCR_HEIGHT_ADD + 6, CENTER(strlen(DEV_NAME)), DEV_NAME);
	mvaddstr(SCR_HEIGHT_ADD + 7, CENTER(strlen(DEV_MAIL)), DEV_MAIL);

	mvaddstr(SCREEN_BOTTOM - 1, CENTER(strlen("USE ARROW KEYS")), "USE ARROW KEYS");
	
	GAME->PECA_PRI.Iniciar_Peca(rand()%7);
	GAME->PECA_PRI.Y = 14;
	GAME->PECA_PRI.X = 5;
	Mostrar_Peca();
	
	refresh();
	
	while ((ch = getch()) != KEY_SPACE ) {
		switch (ch) {
			case KEY_UP:
				clean_menu_interface();
				mvaddstr(SCREEN_BOTTOM - 1,(SCREEN_WIDTH - strlen("UP"))/2, "UP");
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
				for(int i = 0; i < 4; i++) mvaddch(SCR_HEIGHT_ADD+11+i,CENTER(8) - 1, '<');
				mvaddstr(SCREEN_BOTTOM - 1,CENTER(strlen("LEFT")), "LEFT");
				break;
			case KEY_RIGHT:
				clean_menu_interface();
				for(int i = 0; i < 4; i++) mvaddch(SCR_HEIGHT_ADD+11+i,CENTER(8) + 8, '>');
				mvaddstr(SCREEN_BOTTOM - 1,CENTER(strlen("RIGHT")), "RIGHT");
				break;
			default:
				if(TEMPO.Tempo()) {
					clean_menu_interface();
					mvaddstr(SCREEN_BOTTOM - 1,CENTER(strlen("SCAPE WITH SPACE")), "SCAPE WITH SPACE");
					
					GAME->PECA_PRI.Iniciar_Peca(rand()%7);
					
					GAME->PECA_PRI.Y = 14;
					GAME->PECA_PRI.X = 5;
					
					Mostrar_Peca();
				}
				break;
		}
		refresh();
	}
	return 1;
}*/

void ClassSDL::Mostrar_Tabuleiro () {
	for (int i = 0; i < CANVAS_HEIGHT; i++)
		for (int j = 0; j < CANVAS_WIDTH; j++) 
			if (GAME->TABULEIRO_PRI.Valor_Bloco(i,j)) {
				TEXTURES::instance()->drawframe("blocks",j*BLOCK_SIZE,i*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE,6,1,Renderer);
	}
}
void ClassSDL::Mostrar_Peca () {
	for (int i = 0; i < 4; i++)
		if (	BETWEEN(GAME->PECA_PRI.CoordY(i),0,CANVAS_HEIGHT-1)
			&& 	BETWEEN(GAME->PECA_PRI.CoordX(i),0,CANVAS_WIDTH-1)) {
			TEXTURES::instance()->drawframe("blocks",BLOCK_SIZE*GAME->PECA_PRI.CoordX(i),BLOCK_SIZE*GAME->PECA_PRI.CoordY(i),BLOCK_SIZE,BLOCK_SIZE,2,1,Renderer);
	}
}
void ClassSDL::test () {
	for (int i = 0; i < CANVAS_HEIGHT; i++) for (int j = 0; j < CANVAS_WIDTH; j++) if (!(GAME->TABULEIRO_PRI.Valor_Bloco(i,j))) GAME->TABULEIRO_PRI.Inver_Bloco(i,j);
	
	TEMPO.SetTempo(0.1);
	for (int i = 0; i < CANVAS_HEIGHT && running(); ) {
		if (TEMPO.Tempo() || i == 0) {
			GAME->TABULEIRO_PRI.Reciclar_Linha(i);
			i++;
			SDL_RenderClear(Renderer);
			Mostrar_Tabuleiro();
			SDL_RenderPresent(Renderer);
		}
		handleEvents(); 
	}
	TEMPO.SetTempo(5);
	
	SDL_RenderClear(Renderer);
	GAME->PECA_PRI.Iniciar_Peca();
	GAME->PECA_PRI.Y = CANVAS_HEIGHT*0.6;
	GAME->PECA_PRI.X = CANVAS_WIDTH/2;
	Mostrar_Peca();
	SDL_RenderPresent(Renderer);
	
	while (running()) {
		if (TEMPO.Tempo()) {
			GAME->Rotacionar_Peca_Check();
			
			SDL_RenderClear(Renderer);
			Mostrar_Tabuleiro();
			Mostrar_Peca();
			SDL_RenderPresent(Renderer);
		}
		handleEvents();
	}
}
void ClassSDL::render () {
	SDL_RenderClear(Renderer);
	
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255); // RGBA
	
	Mostrar_Tabuleiro();
	Mostrar_Peca();
	
	SDL_RenderPresent(Renderer);
}
void ClassSDL::handleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) if (event.type == SDL_QUIT) Running = false;
	
	//SDL_Delay(5);
}
int main (int argc, char *argv[]) {
	ClassSDL 		*WINDOW = new ClassSDL ("TETRIS",
											SDL_WINDOWPOS_CENTERED,
											SDL_WINDOWPOS_UNDEFINED,
											BLOCK_SIZE * CANVAS_WIDTH,
											BLOCK_SIZE * CANVAS_HEIGHT,
											SDL_WINDOW_SHOWN);
	ClassGame 		*GAME = new ClassGame;
	
	WINDOW->GAME = GAME;
	
	WINDOW->test();
	while (WINDOW->running()) {
		WINDOW->handleEvents();
		WINDOW->update();
		WINDOW->render();
	}
	/*
	while ((i = WINDOW->Capturar_Opcao(GAME)) != 3) {
		if (i == 0) do {
			GAME->Events();
			WINDOW->Render(GAME);
		} while (!GAME->Game_Pause && GAME->Game_Play);
		
		if (i == 1) WINDOW->Mostrar_Score();
	}
	*/
	delete GAME;
	delete WINDOW;
	
	return 0;
}
