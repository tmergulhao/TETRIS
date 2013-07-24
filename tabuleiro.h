#ifndef MOD_TABULEIRO
#define MOD_TABULEIRO

#ifdef SERVIDOR_TABULEIRO
#define EXT_MOD_TABULEIRO
#else
#define EXT_MOD_TABULEIRO extern
#endif

#include <stdbool.h>

#include "main.h"

struct TIPO_LINHA {
	struct TIPO_LINHA* NEXT;
	bool VALOR[CANVAS_WIDTH];
};
typedef struct TIPO_LINHA LINHA;

struct TIPO_TABULEIRO {
	struct TIPO_LINHA* ENTER;
};
typedef struct TIPO_TABULEIRO TABULEIRO;

EXT_MOD_TABULEIRO void Liberar_Tabuleiro ();
EXT_MOD_TABULEIRO TABULEIRO* Chamar_Tabuleiro ();

EXT_MOD_TABULEIRO bool Acessar_Bloco (int y, int x, bool mode);
EXT_MOD_TABULEIRO bool Reciclar_Linha (int y);

#endif