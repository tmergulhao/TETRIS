#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>

#include "main.h++"
#include "peca.h++"
#include "metronomo.h++"
#include "tabuleiro.h++"
#include "game.h++"
#include "textures.h++"
#include "input.h++"

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
		bool handleEvents();
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
	
	delete TEXTURES::instance();
	delete INPUT::instance();
	
	SDL_DestroyWindow(Window);
	SDL_DestroyRenderer(Renderer);
	SDL_Quit();
}

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
	SDL_Event event;
	
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
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) Running = false;
		}
	}
	TEMPO.SetTempo(5);
	
	SDL_RenderClear(Renderer);
	GAME->PECA_PRI.Iniciar_Peca();
	GAME->PECA_PRI.Y = CANVAS_HEIGHT*0.6;
	GAME->PECA_PRI.X = CANVAS_WIDTH/2;
	Mostrar_Peca();
	SDL_RenderPresent(Renderer);
	
	GAME->Game_Play = true;
}
void ClassSDL::render () {
	SDL_RenderClear(Renderer);
	
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255); // RGBA
	
	Mostrar_Tabuleiro();
	Mostrar_Peca();
	
	SDL_RenderPresent(Renderer);
}
bool ClassSDL::handleEvents() {
	SDL_Event event;
	
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) Running = false;
	}
	
	if(INPUT::instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
		GAME->Mover_Peca(-1);
		return 1;
	}
	else if(INPUT::instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
		GAME->Mover_Peca(+1);
		return 1;
	}
	else if(INPUT::instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
		GAME->Descer_Peca();
		TEMPO.FalseFire();
		Running = GAME->Game_Play;
		return 1;
	}
	else if(INPUT::instance()->isKeyDown(SDL_SCANCODE_UP)) {
		GAME->Rotacionar_Peca_Check();
		return 1;
	}
	else if(TEMPO.Tempo()) {
		GAME->Descer_Peca();
		Running = GAME->Game_Play;
		return 1;
	}
	
	return 0;
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
		if (WINDOW->handleEvents())
			WINDOW->render();
	}
	
	delete GAME;
	delete WINDOW;
	
	return 0;
}
