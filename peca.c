#include <ncurses.h>

typedef struct {
	int X, Y;
} BLOCO_TIPO;
typedef struct {
	int X, Y;
	BLOCO_TIPO BLOCO[4];
} PECA;

void Mostrar_Peca () {
	PECA* PECA_ATUAL = Chamar_Peca();

	int i;

	for (i = 0; i < 4; i++) mvaddstr(PECA_ATUAL->Y + PECA_ATUAL->BLOCO[i].Y, (PECA_ATUAL->X + PECA_ATUAL->BLOCO[i].X)*2, "[]");
}
void Rotacionar_Peca () {
	PECA* PECA_ATUAL = Chamar_Peca();
	int i, j, 
		x_max = PECA_ATUAL->BLOCO[0].X, 
		x_min = PECA_ATUAL->BLOCO[0].X,
		y_max = PECA_ATUAL->BLOCO[0].Y;
	
	for(i = 3; i; i--) {
		j = PECA_ATUAL->BLOCO[i].Y;
		PECA_ATUAL->BLOCO[i].Y = - PECA_ATUAL->BLOCO[i].X;
		(PECA_ATUAL->BLOCO[i].X = - j;
		
		if (x_max < PECA_ATUAL->BLOCO[i].X) x_max = PECA_ATUAL->BLOCO[i].X;
		if (y_max < PECA_ATUAL->BLOCO[i].Y) y_max = PECA_ATUAL->BLOCO[i].Y;
		
		if (x_min > PECA_ATUAL->BLOCO[i].X) x_min = PECA_ATUAL->BLOCO[i].X;
	}
	if (y_max) for (i = 4; i; i--) PECA_ATUAL->BLOCO[i-1].Y -= y_max;
	
	if ((x_max - x_min) == 4 && x_min != -1) {
		for (i = 4; i; i--) PECA_ATUAL->BLOCO[i-1].X -= (x_min+1);
	} else {
		if ((x_min + x_max) != 0 && x_min != -1) for (i = 4; i; i--) PECA_ATUAL->BLOCO[i-1].X -= (x_min+1);
	}
}
void Centralizar_Peca () {
	PECA* PECA_ATUAL = Chamar_Peca();
	PECA_ATUAL->Y = SCR_HEIGHT_ADD + 11;
	PECA_ATUAL->X = SCR_WIDTH_ADD + 20/2;
}

void Iniciar_Peca (unsigned i) {
	PECA* PECA_ATUAL = Chamar_Peca();

	PECA_ATUAL->Y = -1;
	PECA_ATUAL->X = 11;
	
	PECA_ATUAL->BLOCO[0].X = 0;
	PECA_ATUAL->BLOCO[0].Y = 0;
	
	switch (i) {
		case 0:
			PECA_ATUAL->BLOCO[1].X = 0;
			PECA_ATUAL->BLOCO[1].Y = -1;
			PECA_ATUAL->BLOCO[2].X = -1;
			PECA_ATUAL->BLOCO[2].Y = -1;
			PECA_ATUAL->BLOCO[3].X = -1;
			PECA_ATUAL->BLOCO[3].Y = -2;
			break;
		case 1:
			PECA_ATUAL->BLOCO[1].X = 0;
			PECA_ATUAL->BLOCO[1].Y = -1;
			PECA_ATUAL->BLOCO[2].X = 1;
			PECA_ATUAL->BLOCO[2].Y = -1;
			PECA_ATUAL->BLOCO[3].X = 1;
			PECA_ATUAL->BLOCO[3].Y = -2;
			break;
		case 2:
			PECA_ATUAL->BLOCO[1].X = 0;
			PECA_ATUAL->BLOCO[1].Y = -1;
			PECA_ATUAL->BLOCO[2].X = 0;
			PECA_ATUAL->BLOCO[2].Y = -2;
			PECA_ATUAL->BLOCO[3].X = 1;
			PECA_ATUAL->BLOCO[3].Y = -2;
			break;
		case 3:
			PECA_ATUAL->BLOCO[1].X = 0;
			PECA_ATUAL->BLOCO[1].Y = -1;
			PECA_ATUAL->BLOCO[2].X = 0;
			PECA_ATUAL->BLOCO[2].Y = -2;
			PECA_ATUAL->BLOCO[3].X = -1;
			PECA_ATUAL->BLOCO[3].Y = -2;
			break;
		case 4:
			PECA_ATUAL->BLOCO[1].X = 0;
			PECA_ATUAL->BLOCO[1].Y = -1;
			PECA_ATUAL->BLOCO[2].X = -1;
			PECA_ATUAL->BLOCO[2].Y = -1;
			PECA_ATUAL->BLOCO[3].X = -1;
			PECA_ATUAL->BLOCO[3].Y = 0;
			break;
		case 5:
			PECA_ATUAL->BLOCO[1].X = 0;
			PECA_ATUAL->BLOCO[1].Y = -1;
			PECA_ATUAL->BLOCO[2].X = -1;
			PECA_ATUAL->BLOCO[2].Y = -1;
			PECA_ATUAL->BLOCO[3].X = 1;
			PECA_ATUAL->BLOCO[3].Y = -1;
			break;
		default:
			PECA_ATUAL->BLOCO[1].X = 0;
			PECA_ATUAL->BLOCO[1].Y = -1;
			PECA_ATUAL->BLOCO[2].X = 0;
			PECA_ATUAL->BLOCO[2].Y = -2;
			PECA_ATUAL->BLOCO[3].X = 0;
			PECA_ATUAL->BLOCO[3].Y = -3;
			break;
	}
}
PECA* Chamar_Peca () {
	static PECA* PECA_ATUAL;

	if (!PECA_ATUAL) {
		PECA_ATUAL = (PECA*)malloc(sizeof(PECA));
		Iniciar_Peca();
	}

	return PECA_ATUAL;
}
