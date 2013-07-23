#include "tabuleiro.h"

#include <stdlib.h>

TABULEIRO* Chamar_Tabuleiro () {
	static TABULEIRO *TABULEIRO_PRINCIPAL;
	LINHA *LINHA_ATUAL;
	
	int i;
	
	if (!TABULEIRO_PRINCIPAL) {
		TABULEIRO_PRINCIPAL = (TABULEIRO*)malloc(sizeof(TABULEIRO));
		TABULEIRO_PRINCIPAL->ENTER = LINHA_ATUAL = (LINHA*)malloc(sizeof(LINHA));
		
		for (i = 1; i < CANVAS_HEIGHT; i++) LINHA_ATUAL = LINHA_ATUAL->NEXT = (LINHA*)malloc(sizeof(LINHA));
		
		LINHA_ATUAL->NEXT = NULL;
	}
	if (!TABULEIRO_PRINCIPAL->ENTER) {
		free(TABULEIRO_PRINCIPAL);
		TABULEIRO_PRINCIPAL = NULL;
	}
	
	return TABULEIRO_PRINCIPAL;
}
void Liberar_Tabuleiro () {
	TABULEIRO *TABULEIRO_PRINCIPAL = Chamar_Tabuleiro();
	LINHA *LINHA_LIBERAR;
	
	while (TABULEIRO_PRINCIPAL->ENTER) {
		LINHA_LIBERAR = TABULEIRO_PRINCIPAL->ENTER;
		
		TABULEIRO_PRINCIPAL->ENTER = TABULEIRO_PRINCIPAL->ENTER->NEXT;
		
		free(LINHA_LIBERAR);
	}
	TABULEIRO_PRINCIPAL->ENTER = NULL;
	Chamar_Tabuleiro();
}
bool Reciclar_Linha (int y) {
	TABULEIRO *TABULEIRO_PRINCIPAL = Chamar_Tabuleiro();
	LINHA *LINHA_RECICLA, *LINHA_ATUAL = TABULEIRO_PRINCIPAL->ENTER;
	
	int i, j = 0;
	
	if (y == 0) {
		for (i = 0; i < CANVAS_WIDTH; i++) if (TABULEIRO_PRINCIPAL->ENTER->VALOR[i]) j++;
		if (j == CANVAS_WIDTH) 
			for (i = 0; i < CANVAS_WIDTH; i++) LINHA_ATUAL->VALOR[i] = false;
	} else  if (y > 0) {
		for (y = y-1; y; y--) LINHA_ATUAL = LINHA_ATUAL->NEXT;

		LINHA_RECICLA = LINHA_ATUAL->NEXT;
		
		for (i = 0; i < CANVAS_WIDTH; i++) if (LINHA_RECICLA->VALOR[i]) j++;
		if (j == CANVAS_WIDTH) 
			for (i = 0; i < CANVAS_WIDTH; i++) LINHA_RECICLA->VALOR[i] = false;
		else return 0;
		
		LINHA_ATUAL->NEXT = LINHA_ATUAL->NEXT->NEXT;
		LINHA_RECICLA->NEXT = TABULEIRO_PRINCIPAL->ENTER;
		TABULEIRO_PRINCIPAL->ENTER = LINHA_RECICLA;
	} else {
		for (j = 0; j < CANVAS_HEIGHT; j++) {
			for (i = 0; i < CANVAS_WIDTH; i++) LINHA_ATUAL->VALOR[i] = false;
			LINHA_ATUAL = LINHA_ATUAL->NEXT;
		}
	}
	
	return 1;
}
bool Acessar_Bloco (int y, int x, bool mode) {
	TABULEIRO *TABULEIRO_PRINCIPAL = Chamar_Tabuleiro();
	LINHA *LINHA_ATUAL = TABULEIRO_PRINCIPAL->ENTER;
	
	while (y > 0) {
		LINHA_ATUAL = LINHA_ATUAL->NEXT;
		y--;
	}

	if (mode) LINHA_ATUAL->VALOR[x] = !LINHA_ATUAL->VALOR[x];
	
	return LINHA_ATUAL->VALOR[x];
}
