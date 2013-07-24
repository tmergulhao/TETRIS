#ifndef MOD_MAIN
#define MOD_MAIN

#ifdef SERVIDOR_MAIN
#define EXT_MOD_MAIN
#else
#define EXT_MOD_MAIN extern
#endif

// STRUCTURE DEFS
#define BETWEEN(X,DOWN,UP)	((X) >= (DOWN) && (X) <= (UP))

// CANVAS DEFS
#define CANVAS_WIDTH		10
#define CANVAS_HEIGHT		20

// METRONOMO DEFS
#define Desligar_Espera() 	metronomy(0,0)
#define Tempo_Espera() 		metronomy(-1,0)
#define Tempo_Jogo() 		metronomy(-1,1)
#define Ver_T_Jogo()		metronomy(-2,1)
#define Passar_Ciclo()		metronomy(-3,1)
#define Mudar_Tempo_Jogo(X) if(BETWEEN((Ver_T_Jogo()+X),1,5)) metronomy(Ver_T_Jogo() + X,1)

// TABULEIRO DEFS
#define Inver_Bloco(Y,X)	Acessar_Bloco(Y,X,1)
#define Valor_Bloco(Y,X)	Acessar_Bloco(Y,X,0)
#define Reciclar_Tabul()	Reciclar_Linha(-1)

#endif