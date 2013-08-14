#ifndef MOD_TABULEIRO
	#define MOD_TABULEIRO
	
	#include <stdbool.h>
	
	#include "main.h++"
	
	struct TIPO_LINHA {
		struct TIPO_LINHA* NEXT;
		bool VALOR[CANVAS_WIDTH];
	};
	typedef struct TIPO_LINHA LINHA;
	
	class ClassTabuleiro {
			LINHA *ENTER;
			LINHA *HEAD;
		public:
			ClassTabuleiro ();
			~ClassTabuleiro () {delete [] HEAD;}
			
			bool Valor_Bloco (int y, int x);
			bool Inver_Bloco (int y, int x);
			bool Reciclar_Linha (int y);
	};
#endif
