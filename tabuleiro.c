#include "tabuleiro.h"

#include <assert.h>

#include <iostream>
using namespace std;

ClassTabuleiro::ClassTabuleiro () {
	LINHA *LINHA_ATUAL;
	
	ENTER = LINHA_ATUAL = new (nothrow) LINHA[CANVAS_HEIGHT];
	
	for (int i = 0; i < CANVAS_HEIGHT - 1; i++) {
		LINHA_ATUAL->NEXT = new (nothrow) LINHA[CANVAS_HEIGHT];
		LINHA_ATUAL = LINHA_ATUAL->NEXT;
	}
	
	LINHA_ATUAL->NEXT = NULL;
}
ClassTabuleiro::~ClassTabuleiro () {
	LINHA *LINHA_ATUAL = ENTER;
	
	for (int i = 0; i < CANVAS_HEIGHT; i++) {
		LINHA_ATUAL = ENTER;
		ENTER = ENTER->NEXT;
		delete LINHA_ATUAL;
	}
}
bool ClassTabuleiro::Reciclar_Linha (int y) {
	LINHA *LINHA_RECICLA, *LINHA_ATUAL = ENTER;
	
	int i, j = 0;

	assert(y < CANVAS_HEIGHT);
	
	if (y == 0) {
		for (i = 0; i < CANVAS_WIDTH; i++) if (ENTER->VALOR[i]) j++;
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
		LINHA_RECICLA->NEXT = ENTER;
		ENTER = LINHA_RECICLA;
	} else {
		for (j = 0; j < CANVAS_HEIGHT; j++) {
			for (i = 0; i < CANVAS_WIDTH; i++) LINHA_ATUAL->VALOR[i] = false;
			LINHA_ATUAL = LINHA_ATUAL->NEXT;
		}
	}
	
	return 1;
}
bool ClassTabuleiro::Acessar_Bloco (int y, int x, bool mode) {
	LINHA *LINHA_ATUAL = ENTER;

	assert(y < CANVAS_HEIGHT);
	assert(x < CANVAS_WIDTH);
	
	while (y > 0) {
		LINHA_ATUAL = LINHA_ATUAL->NEXT;
		y--;
	}

	if (mode) LINHA_ATUAL->VALOR[x] = !LINHA_ATUAL->VALOR[x];
	
	return LINHA_ATUAL->VALOR[x];
}
