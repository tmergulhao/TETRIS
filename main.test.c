#include "metronomo.h"
#include "tabuleiro.h"
#include "peca.h"

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include <stdlib.h>
#include <time.h>

void Testar_Metronomo_Set () {
	float i = Espera_Jogo();

	Mudar_Tempo_Jogo(1);
	CU_ASSERT_TRUE(Espera_Jogo() == 1);
	Mudar_Tempo_Jogo(0.1);
	CU_ASSERT_FALSE(Espera_Jogo() == 0.1);
}

void Testar_Metronomo (void) {
	CU_pSuite suite;
	
	suite = CU_add_suite("METRONOMO",NULL,NULL);

	CU_ADD_TEST(suite, Testar_Metronomo_Set);

	Desligar_Espera();
}

ClassPeca PECA_ATUAL, PECA_SEC;

void Testar_Rotacionar_T () {
	int i;
	bool ALERT_0, ALERT_1, ALERT_2, ALERT_3;
	
	PECA_SEC.Iniciar_Peca(5);
	
	PECA_ATUAL = PECA_SEC;
	
	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	PECA_ATUAL.Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -2) ALERT_0 = (ALERT_0) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_2 = (ALERT_2) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	PECA_ATUAL.Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_0 = (ALERT_0) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_2 = (ALERT_2) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == +1 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	PECA_ATUAL.Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -2) ALERT_0 = (ALERT_0) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_2 = (ALERT_2) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	PECA_ATUAL.Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_0 = (ALERT_0) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_2 = (ALERT_2) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == +1 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);
}

void Testar_Rotacionar_J () {
	int i;
	bool ALERT_0, ALERT_1, ALERT_2, ALERT_3;

	PECA_SEC.Iniciar_Peca(2);
	
	PECA_ATUAL = PECA_SEC;

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	PECA_ATUAL.Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (PECA_ATUAL.BLOCO[i].X == +1 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_0 = (ALERT_0) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_1 = (ALERT_1) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_2 = (ALERT_2) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	PECA_ATUAL.Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_0 = (ALERT_0) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_1 = (ALERT_1) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_2 = (ALERT_2) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -2) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	PECA_ATUAL.Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_0 = (ALERT_0) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == +1 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_2 = (ALERT_2) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == +1 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	PECA_ATUAL.Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_0 = (ALERT_0) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -2) ALERT_2 = (ALERT_2) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -2) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);
}

void Testar_Rotacionar_L () {
	int i;
	bool ALERT_0, ALERT_1, ALERT_2, ALERT_3;

	PECA_SEC.Iniciar_Peca(3);
	
	PECA_ATUAL = PECA_SEC;

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	PECA_ATUAL.Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_0 = (ALERT_0) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_2 = (ALERT_2) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == +1 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	PECA_ATUAL.Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_0 = (ALERT_0) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -2) ALERT_2 = (ALERT_2) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	PECA_ATUAL.Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_0 = (ALERT_0) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_1 = (ALERT_1) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == +1 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_2 = (ALERT_2) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == +1 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	PECA_ATUAL.Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -2) ALERT_0 = (ALERT_0) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -2) ALERT_1 = (ALERT_1) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_2 = (ALERT_2) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);
}

void Testar_Rotacionar_Z () {
	int i;
	bool ALERT_0, ALERT_1, ALERT_2, ALERT_3;

	PECA_SEC.Iniciar_Peca(1);
	
	PECA_ATUAL = PECA_SEC;

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	PECA_ATUAL.Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_0 = (ALERT_0) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_2 = (ALERT_2) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == +1 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	PECA_ATUAL.Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -2) ALERT_0 = (ALERT_0) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_2 = (ALERT_2) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);
}

void Testar_Rotacionar_S () {
	int i;
	bool ALERT_0, ALERT_1, ALERT_2, ALERT_3;

	PECA_SEC.Iniciar_Peca(0);
	
	PECA_ATUAL = PECA_SEC;

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	PECA_ATUAL.Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == 0) ALERT_0 = (ALERT_0) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == 0) ALERT_1 = (ALERT_1) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_2 = (ALERT_2) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == +1 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	PECA_ATUAL.Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_0 = (ALERT_0) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_2 = (ALERT_2) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -2) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);
}

void Testar_Rotacionar_I () {
	int i;
	bool ALERT_0, ALERT_1, ALERT_2, ALERT_3;

	PECA_SEC.Iniciar_Peca(6);
	
	PECA_ATUAL = PECA_SEC;

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	PECA_ATUAL.Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (PECA_ATUAL.BLOCO[i].X == -2 && PECA_ATUAL.BLOCO[i].Y == 0) ALERT_0 = (ALERT_0) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == 0) ALERT_1 = (ALERT_1) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -0 && PECA_ATUAL.BLOCO[i].Y == 0) ALERT_2 = (ALERT_2) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == +1 && PECA_ATUAL.BLOCO[i].Y == 0) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	PECA_ATUAL.Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -0) ALERT_0 = (ALERT_0) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -2) ALERT_2 = (ALERT_2) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -3) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);
}

void Testar_Rotacionar_O () {
	int i;
	bool ALERT_0, ALERT_1, ALERT_2, ALERT_3;

	PECA_SEC.Iniciar_Peca(4);
	
	PECA_ATUAL = PECA_SEC;

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	PECA_SEC.Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (PECA_ATUAL.BLOCO[i].X == 0 && PECA_ATUAL.BLOCO[i].Y == 0) ALERT_0 = (ALERT_0) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == 0 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == 0) ALERT_2 = (ALERT_2) ? false : true;
		if (PECA_ATUAL.BLOCO[i].X == -1 && PECA_ATUAL.BLOCO[i].Y == -1) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);
}

void Testar_Peca (void) {
	CU_pSuite suite;
	
	suite = CU_add_suite("PECA",NULL,NULL);
	
	CU_ADD_TEST(suite, Testar_Rotacionar_O);

	CU_ADD_TEST(suite, Testar_Rotacionar_I);
	CU_ADD_TEST(suite, Testar_Rotacionar_S);
	CU_ADD_TEST(suite, Testar_Rotacionar_Z);

	CU_ADD_TEST(suite, Testar_Rotacionar_L);
	CU_ADD_TEST(suite, Testar_Rotacionar_J);
	CU_ADD_TEST(suite, Testar_Rotacionar_T);
}

ClassTabuleiro TABULEIRO_PRI;

void Testar_Limpar_CLR_L () {
	int i = rand()%(CANVAS_WIDTH - 1), k, j = rand()%CANVAS_HEIGHT;

	for (k = 0; k < i; k++) TABULEIRO_PRI.Inver_Bloco(j,k);
	TABULEIRO_PRI.Reciclar_Linha(j);
	for (k = 0; k < i; k++) CU_ASSERT_TRUE(TABULEIRO_PRI.Valor_Bloco(j,k));
	for (k = i; k < CANVAS_WIDTH; k++) CU_ASSERT_FALSE(TABULEIRO_PRI.Valor_Bloco(j,k));
}

void Testar_Limpar_ALL_L () {
	int i, j;
	for (j = 0; j < CANVAS_HEIGHT; j++) for (i = 0; i < CANVAS_WIDTH; i++) TABULEIRO_PRI.Inver_Bloco(j,i);
	TABULEIRO_PRI.Reciclar_Linha(-1);
	for (j = 0; j < CANVAS_HEIGHT; j++) for (i = 0; i < CANVAS_WIDTH; i++) CU_ASSERT_FALSE(TABULEIRO_PRI.Valor_Bloco(j,i));
}

void Testar_Limpar_NUM_L () {
	int i, j = rand()%CANVAS_HEIGHT;
	for (i = 0; i < CANVAS_WIDTH; i++) TABULEIRO_PRI.Inver_Bloco(j,i);
	TABULEIRO_PRI.Reciclar_Linha(j);
	for (i = 0; i < CANVAS_WIDTH; i++) CU_ASSERT_FALSE(TABULEIRO_PRI.Valor_Bloco(j,i));
}

void Testar_Limpar_LAS_L () {
	int i;
	for (i = 0; i < CANVAS_WIDTH; i++) TABULEIRO_PRI.Inver_Bloco(CANVAS_HEIGHT-1,i);
	TABULEIRO_PRI.Reciclar_Linha(CANVAS_HEIGHT-1);
	for (i = 0; i < CANVAS_WIDTH; i++) CU_ASSERT_FALSE(TABULEIRO_PRI.Valor_Bloco(CANVAS_HEIGHT-1,i));
}

void Testar_Limpar_FIR_L () {
	int i;
	for (i = 0; i < CANVAS_WIDTH; i++) TABULEIRO_PRI.Inver_Bloco(0,i);
	TABULEIRO_PRI.Reciclar_Linha(0);
	for (i = 0; i < CANVAS_WIDTH; i++) CU_ASSERT_FALSE(TABULEIRO_PRI.Valor_Bloco(0,i));
}

void Testar_Trocar_Captar_Valor () {
	int i = rand()%CANVAS_WIDTH, j = rand()%CANVAS_HEIGHT;
	
	TABULEIRO_PRI.Inver_Bloco(j,i);
	CU_ASSERT_TRUE(TABULEIRO_PRI.Valor_Bloco(j,i));
	TABULEIRO_PRI.Inver_Bloco(j,i);
}

void Testar_Tabuleiro (void) {
	CU_pSuite suite;
	
	suite = CU_add_suite("TABULEIRO",NULL,NULL);
	
	CU_ADD_TEST(suite, Testar_Trocar_Captar_Valor);
	CU_ADD_TEST(suite, Testar_Limpar_FIR_L);
	CU_ADD_TEST(suite, Testar_Limpar_LAS_L);
	CU_ADD_TEST(suite, Testar_Limpar_NUM_L);
	CU_ADD_TEST(suite, Testar_Limpar_ALL_L);
	CU_ADD_TEST(suite, Testar_Limpar_CLR_L);
}

int main (int argc, char *argv[]) {
	if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

	srand (time(NULL));
	
	Testar_Tabuleiro();
	Testar_Peca();
	Testar_Metronomo();
	
	CU_basic_set_mode(CU_BRM_VERBOSE);
	
	CU_basic_run_tests();
	
	CU_cleanup_registry();
	
	return CU_get_error();
}