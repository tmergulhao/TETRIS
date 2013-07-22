#include "tabuleiro.h"

#include <stdlib.h>

#include <ncurses.h>

LINHA* Chamar_Tabuleiro () {
	static LINHA* LINHA_PRINCIPAL;
	LINHA* LINHA_ATUAL;
	LINHA* ANDAR;
	int i;
	
	if (!LINHA_PRINCIPAL) {
		LINHA_ATUAL = LINHA_PRINCIPAL = (LINHA*)malloc(sizeof(LINHA));
		
		for (i = 1; i < CANVAS_HEIGHT; i++) {
			LINHA_ATUAL->NEXT = (LINHA*)malloc(sizeof(LINHA));
			LINHA_ATUAL = LINHA_ATUAL->NEXT;
		}
	}

	return LINHA_PRINCIPAL;
}
void Liberar_Tabuleiro () {
	LINHA *LINHA_LIBERAR, *LINHA_ATUAL = Chamar_Tabuleiro();
	
	while (LINHA_ATUAL) {
		LINHA_LIBERAR = LINHA_ATUAL;
		LINHA_ATUAL = LINHA_ATUAL->NEXT;
		free(LINHA_LIBERAR);
	}
}
bool Reciclar_Linha (int y) {
	LINHA *LINHA_RECICLAR, *LINHA_ATUAL = Chamar_Tabuleiro();
	
	int i, j = 0;
	
	if (y > 0) { // FOR LINES, NOT THE FIRST
		for (i = 0; i < y-1; i++) LINHA_ATUAL = LINHA_ATUAL->NEXT;
		
		for (i = 0; i < CANVAS_WIDTH; i++) if (LINHA_ATUAL->NEXT->VALOR[i]) j++;
		
		if (j == CANVAS_WIDTH) {
			LINHA_RECICLAR = LINHA_ATUAL->NEXT;
			LINHA_ATUAL->NEXT = LINHA_ATUAL->NEXT->NEXT;
			
			LINHA_RECICLAR->NEXT = NULL;
			for (i = 0; i < CANVAS_WIDTH; i++) LINHA_RECICLAR->VALOR[i] = false;
			
			while (LINHA_ATUAL->NEXT) LINHA_ATUAL = LINHA_ATUAL->NEXT;
			
			LINHA_ATUAL->NEXT = LINHA_RECICLAR;
			
			return true;
		}
		
		return 0;
		
	} else if (y == 0) { // FOR FIRST LINE
		for (i = 0; i < CANVAS_WIDTH; i++) if (LINHA_ATUAL->VALOR[i]) j++;
		
		if (j == CANVAS_WIDTH) {
			for (i = 0; i < CANVAS_WIDTH; i++) {
				LINHA_ATUAL->VALOR[i] = LINHA_ATUAL->NEXT->VALOR[i];
				LINHA_ATUAL->NEXT->VALOR[i] = true;
			}
		}
		
		return Reciclar_Linha(1);
	} else { // FOR ALL LINES
		while (LINHA_ATUAL) {
			for (i = 0; i < CANVAS_WIDTH; i++) LINHA_ATUAL->VALOR[i] = false;
			LINHA_ATUAL = LINHA_ATUAL->NEXT;
		}
		
		return NULL;
	}
	
	
}
bool Acessar_Bloco (int y, int x, bool mode) {
	LINHA *LINHA_ATUAL = Chamar_Tabuleiro();
	
	int i, j;
	
	for (i = 0; i < y; i++) LINHA_ATUAL = LINHA_ATUAL->NEXT;
	
	if (mode) LINHA_ATUAL->VALOR[x] = !LINHA_ATUAL->VALOR[x];
	
	return LINHA_ATUAL->VALOR[x];
}

/*
bool Reciclar_Linha (LINHA* LINHA_EXCLUIR) {
	LINHA *LINHA_ATUAL = Chamar_Tabuleiro();
	
	int i;
	
	for (i = 0; i < CANVAS_WIDTH; i++) {}
	
	for (i = TELA_LARGURA; i; i--) LINHA_EXCLUIR->VALOR[i-1] = false;

	if (LINHA_FINAL != LINHA_EXCLUIR) LINHA_FINAL->NEXT = LINHA_EXCLUIR;
	else if (TELA_ATUAL->ENTER = LINHA_EXCLUIR) {
		TELA_ATUAL->ENTER = TELA_ATUAL->ENTER->NEXT;
		LINHA_FINAL->NEXT = LINHA_EXCLUIR;
	} else {
		while (LINHA_ATUAL->NEXT != LINHA_EXCLUIR) LINHA_ATUAL = LINHA_ATUAL->NEXT;
		LINHA_ATUAL->NEXT = LINHA_ATUAL->NEXT->NEXT;
		LINHA_FINAL = LINHA_EXCLUIR;
	}
	LINHA_EXCLUIR->NEXT = NULL;
}
*/