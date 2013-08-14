#include "peca.h"
#include "main.h"

ClassPeca ClassPeca::operator= (ClassPeca param) {
	ClassPeca temp;
	temp.X = X;
	temp.Y = Y;
	for (int i = 0; i < 4; i++) {
		temp.BLOCO[i].X = BLOCO[i].X;
		temp.BLOCO[i].Y = BLOCO[i].Y;
	}
	
	return (temp);
}
void ClassPeca::Iniciar_Peca (int i) {
	Y = -1;
	X = (CANVAS_WIDTH)/2;
	
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
void ClassPeca::Rotacionar_Peca () {
	int j, 
		x_max = -5,
		y_max = -5, 
		x_min = 5;
	
	// ROTATE AXIS
	for (int i = 0; i < 4; i++) {
		j = BLOCO[i].Y;
		BLOCO[i].Y = - BLOCO[i].X;
		BLOCO[i].X = j;
		
		if (y_max < BLOCO[i].Y) y_max = BLOCO[i].Y;
		
		if (x_max < BLOCO[i].X) x_max = BLOCO[i].X;
		if (x_min > BLOCO[i].X) x_min = BLOCO[i].X;
	}
	
	// SET ANY SHAPE TO FIT BASELINE
	for (int i = 0; i < 4; i++) BLOCO[i].Y -= y_max;
	
	// SET ANY OTHER SHAPE TO CENTER X AXIS
	j = ((x_max - x_min) == 3) ? 2 : 1;
	for (int i = 0; i < 4; i++) BLOCO[i].X -= (x_min + j);
}