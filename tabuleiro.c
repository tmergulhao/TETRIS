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
	
	/*
	int i, j = 0;
	
	y = CANVAS_HEIGHT - y - 1;
	
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
	
	*/
}
bool Acessar_Bloco (int y, int x, bool mode) {
	TABULEIRO *TABULEIRO_PRINCIPAL = Chamar_Tabuleiro();
	LINHA *LINHA_ATUAL = TABULEIRO_PRINCIPAL->ENTER;
	
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