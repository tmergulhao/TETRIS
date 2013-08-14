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

class ClassTabuleiro {
		LINHA *ENTER;
	public:
		ClassTabuleiro ();
		~ClassTabuleiro ();
		
		bool Acessar_Bloco (int y, int x, bool mode);
		bool Reciclar_Linha (int y);
};

#endif
