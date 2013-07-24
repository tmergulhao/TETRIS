#include <stdlib.h>

#include "peca.h"
#include "engine.h"

PECA* Chamar_Peca_Principal () {
	static PECA* PECA_ATUAL;
	
	if (!PECA_ATUAL) PECA_ATUAL = (PECA*)malloc(sizeof(PECA));
	
	return PECA_ATUAL;
}

void Liberar_Peca () {
	free(Chamar_Peca_Principal());
}

void Iniciar_Peca (int i) {
	PECA* PECA_ATUAL = Chamar_Peca_Principal();
	BLOCO_TIPO* BLOCO = PECA_ATUAL->BLOCO;
	
	PECA_ATUAL->Y = -1;
	PECA_ATUAL->X = (CANVAS_WIDTH)/2;
	
	PECA_ATUAL = Chamar_Peca_Principal();
	
			BLOCO[0].X = 0;		BLOCO[0].Y = 0;
	
	switch (i) {
		case 0:
			BLOCO[1].X = 0;		BLOCO[1].Y = -1;
			BLOCO[2].X = -1;	BLOCO[2].Y = -1;
			BLOCO[3].X = -1;	BLOCO[3].Y = -2;
			break;
		case 1:
			BLOCO[0].X = -1;
			BLOCO[1].X = -1;	BLOCO[1].Y = -1;
			BLOCO[2].X = 0;		BLOCO[2].Y = -1;
			BLOCO[3].X = 0;		BLOCO[3].Y = -2;
			break;
		case 2:
			BLOCO[0].X = -1;
			BLOCO[1].X = -1;	BLOCO[1].Y = -1;
			BLOCO[2].X = -1;	BLOCO[2].Y = -2;
			BLOCO[3].X = 0;		BLOCO[3].Y = -2;
			break;
		case 3:
			BLOCO[1].X = 0;		BLOCO[1].Y = -1;
			BLOCO[2].X = 0;		BLOCO[2].Y = -2;
			BLOCO[3].X = -1;	BLOCO[3].Y = -2;
			break;
		case 4:
			BLOCO[1].X = 0;		BLOCO[1].Y = -1;
			BLOCO[2].X = -1;	BLOCO[2].Y = -1;
			BLOCO[3].X = -1;	BLOCO[3].Y = 0;
			break;
		case 5:
			BLOCO[1].X = 0;		BLOCO[1].Y = -1;
			BLOCO[2].X = -1;	BLOCO[2].Y = -1;
			BLOCO[3].X = 1;		BLOCO[3].Y = -1;
			break;
		default:
			BLOCO[0].X = -1;
			BLOCO[1].X = -1;	BLOCO[1].Y = -1;
			BLOCO[2].X = -1;	BLOCO[2].Y = -2;
			BLOCO[3].X = -1;	BLOCO[3].Y = -3;
			break;
	}
}

void Rotacionar_Peca () {
	PECA* PECA_ATUAL = Chamar_Peca_Principal();
	BLOCO_TIPO* BLOCO = PECA_ATUAL->BLOCO;
	
	int i, j, 
		x_max = -5,
		y_max = -5, 
		x_min = 5;
	
	// ROTATE AXIS
	for (i = 0; i < 4; i++) {
		j = BLOCO[i].Y;
		BLOCO[i].Y = - BLOCO[i].X;
		BLOCO[i].X = j;
		
		if (y_max < BLOCO[i].Y) y_max = BLOCO[i].Y;
		
		if (x_max < BLOCO[i].X) x_max = BLOCO[i].X;
		if (x_min > BLOCO[i].X) x_min = BLOCO[i].X;
	}
	
	// SET ANY SHAPE TO FIT BASELINE
	for (i = 0; i < 4; i++) BLOCO[i].Y -= y_max;
	
	// SET ANY OTHER SHAPE TO CENTER X AXIS
	j = ((x_max - x_min) == 3) ? 2 : 1;
	for (i = 0; i < 4; i++) BLOCO[i].X -= (x_min + j);
}
