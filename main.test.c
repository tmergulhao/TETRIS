#include "engine.h"
#include "tabuleiro.h"
#include "peca.h"

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include <time.h>
#include <stdlib.h>

void Testar_Rotacionar_T () {
	PECA* PECA_ATUAL = Chamar_Peca_Principal();
	BLOCO_TIPO* BLOCO = PECA_ATUAL->BLOCO;

	int i;
	bool ALERT_0, ALERT_1, ALERT_2, ALERT_3;

	Iniciar_Peca(5);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -2) ALERT_0 = (ALERT_0) ? false : true;
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -0) ALERT_2 = (ALERT_2) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -1) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -0) ALERT_0 = (ALERT_0) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -0) ALERT_2 = (ALERT_2) ? false : true;
		if (BLOCO[i].X == +1 && BLOCO[i].Y == -0) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -2) ALERT_0 = (ALERT_0) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -0) ALERT_2 = (ALERT_2) ? false : true;
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -1) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -1) ALERT_0 = (ALERT_0) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -0) ALERT_2 = (ALERT_2) ? false : true;
		if (BLOCO[i].X == +1 && BLOCO[i].Y == -1) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);
}

void Testar_Rotacionar_J () {
	PECA* PECA_ATUAL = Chamar_Peca_Principal();
	BLOCO_TIPO* BLOCO = PECA_ATUAL->BLOCO;

	int i;
	bool ALERT_0, ALERT_1, ALERT_2, ALERT_3;

	Iniciar_Peca(2);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (BLOCO[i].X == +1 && BLOCO[i].Y == -0) ALERT_0 = (ALERT_0) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -0) ALERT_1 = (ALERT_1) ? false : true;
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -0) ALERT_2 = (ALERT_2) ? false : true;
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -1) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -0) ALERT_0 = (ALERT_0) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -0) ALERT_1 = (ALERT_1) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -1) ALERT_2 = (ALERT_2) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -2) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -1) ALERT_0 = (ALERT_0) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (BLOCO[i].X == +1 && BLOCO[i].Y == -1) ALERT_2 = (ALERT_2) ? false : true;
		if (BLOCO[i].X == +1 && BLOCO[i].Y == -0) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -0) ALERT_0 = (ALERT_0) ? false : true;
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -2) ALERT_2 = (ALERT_2) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -2) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);
}

void Testar_Rotacionar_L () {
	PECA* PECA_ATUAL = Chamar_Peca_Principal();
	BLOCO_TIPO* BLOCO = PECA_ATUAL->BLOCO;

	int i;
	bool ALERT_0, ALERT_1, ALERT_2, ALERT_3;

	Iniciar_Peca(3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -0) ALERT_0 = (ALERT_0) ? false : true;
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -1) ALERT_2 = (ALERT_2) ? false : true;
		if (BLOCO[i].X == +1 && BLOCO[i].Y == -1) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -0) ALERT_0 = (ALERT_0) ? false : true;
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -2) ALERT_2 = (ALERT_2) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -0) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -0) ALERT_0 = (ALERT_0) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -0) ALERT_1 = (ALERT_1) ? false : true;
		if (BLOCO[i].X == +1 && BLOCO[i].Y == -0) ALERT_2 = (ALERT_2) ? false : true;
		if (BLOCO[i].X == +1 && BLOCO[i].Y == -1) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -2) ALERT_0 = (ALERT_0) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -2) ALERT_1 = (ALERT_1) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -1) ALERT_2 = (ALERT_2) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -0) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);
}

void Testar_Rotacionar_Z () {
	PECA* PECA_ATUAL = Chamar_Peca_Principal();
	BLOCO_TIPO* BLOCO = PECA_ATUAL->BLOCO;

	int i;
	bool ALERT_0, ALERT_1, ALERT_2, ALERT_3;

	Iniciar_Peca(1);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -1) ALERT_0 = (ALERT_0) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -0) ALERT_2 = (ALERT_2) ? false : true;
		if (BLOCO[i].X == +1 && BLOCO[i].Y == -0) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -2) ALERT_0 = (ALERT_0) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -1) ALERT_2 = (ALERT_2) ? false : true;
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -0) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);
}

void Testar_Rotacionar_S () {
	PECA* PECA_ATUAL = Chamar_Peca_Principal();
	BLOCO_TIPO* BLOCO = PECA_ATUAL->BLOCO;

	int i;
	bool ALERT_0, ALERT_1, ALERT_2, ALERT_3;

	Iniciar_Peca(0);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (BLOCO[i].X == -1 && BLOCO[i].Y == 0) ALERT_0 = (ALERT_0) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == 0) ALERT_1 = (ALERT_1) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -1) ALERT_2 = (ALERT_2) ? false : true;
		if (BLOCO[i].X == +1 && BLOCO[i].Y == -1) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -0) ALERT_0 = (ALERT_0) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -1) ALERT_2 = (ALERT_2) ? false : true;
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -2) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);
}

void Testar_Rotacionar_I () {
	PECA* PECA_ATUAL = Chamar_Peca_Principal();
	BLOCO_TIPO* BLOCO = PECA_ATUAL->BLOCO;

	int i;
	bool ALERT_0, ALERT_1, ALERT_2, ALERT_3;

	Iniciar_Peca(6);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (BLOCO[i].X == -2 && BLOCO[i].Y == 0) ALERT_0 = (ALERT_0) ? false : true;
		if (BLOCO[i].X == -1 && BLOCO[i].Y == 0) ALERT_1 = (ALERT_1) ? false : true;
		if (BLOCO[i].X == -0 && BLOCO[i].Y == 0) ALERT_2 = (ALERT_2) ? false : true;
		if (BLOCO[i].X == +1 && BLOCO[i].Y == 0) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -0) ALERT_0 = (ALERT_0) ? false : true;
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -2) ALERT_2 = (ALERT_2) ? false : true;
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -3) ALERT_3 = (ALERT_3) ? false : true;
	}
	CU_ASSERT_TRUE(ALERT_0 && ALERT_1 && ALERT_2 && ALERT_3);
}

void Testar_Rotacionar_O () {
	PECA* PECA_ATUAL = Chamar_Peca_Principal();
	BLOCO_TIPO* BLOCO = PECA_ATUAL->BLOCO;

	int i;
	bool ALERT_0, ALERT_1, ALERT_2, ALERT_3;

	Iniciar_Peca(4);

	ALERT_0 = ALERT_1 = ALERT_2 = ALERT_3 = false;
	Rotacionar_Peca();
	for (i = 0; i < 4; i++) {
		if (BLOCO[i].X == 0 && BLOCO[i].Y == 0) ALERT_0 = (ALERT_0) ? false : true;
		if (BLOCO[i].X == 0 && BLOCO[i].Y == -1) ALERT_1 = (ALERT_1) ? false : true;
		if (BLOCO[i].X == -1 && BLOCO[i].Y == 0) ALERT_2 = (ALERT_2) ? false : true;
		if (BLOCO[i].X == -1 && BLOCO[i].Y == -1) ALERT_3 = (ALERT_3) ? false : true;
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

#define Inver_Bloco(Y,X)	Acessar_Bloco(Y,X,1)
#define Valor_Bloco(Y,X)	Acessar_Bloco(Y,X,0)
#define Reciclar_Tabul()	Reciclar_Linha(-1)

void Testar_Limpar_ALL_L () {
	int i, j;
	for (j = 0; j < CANVAS_HEIGHT; j++) for (i = 0; i < CANVAS_WIDTH; i++) Inver_Bloco(j,i);
	Reciclar_Linha(-1);
	for (j = 0; j < CANVAS_HEIGHT; j++) for (i = 0; i < CANVAS_WIDTH; i++) if (Valor_Bloco(j,i)) CU_ASSERT_TRUE(false);
}

void Testar_Limpar_NUM_L () {
	int i, j = rand()%CANVAS_WIDTH;
	for (i = 0; i < CANVAS_WIDTH; i++) Inver_Bloco(j,i);
	Reciclar_Linha(j);
	for (i = 0; i < CANVAS_WIDTH; i++) if (Valor_Bloco(j,i)) CU_ASSERT_TRUE(false);
}

void Testar_Limpar_LAS_L () {
	int i;
	for (i = 0; i < CANVAS_WIDTH; i++) Inver_Bloco(CANVAS_HEIGHT-1,i);
	Reciclar_Linha(CANVAS_HEIGHT-1);
	for (i = 0; i < CANVAS_WIDTH; i++) if (Valor_Bloco(CANVAS_HEIGHT-1,i)) CU_ASSERT_TRUE(false);
}

void Testar_Limpar_FIR_L () {
	int i;
	for (i = 0; i < CANVAS_WIDTH; i++) Inver_Bloco(0,i);
	Reciclar_Linha(0);
	for (i = 0; i < CANVAS_WIDTH; i++) if (Valor_Bloco(0,i)) CU_ASSERT_TRUE(false);
}

void Testar_Trocar_Captar_Valor () {
	int i, j;
	i = rand()%(CANVAS_WIDTH);
	j = rand()%(CANVAS_HEIGHT);

	Inver_Bloco(j,i);
	CU_ASSERT_TRUE(Valor_Bloco(j,i));
	Inver_Bloco(j,i);
}

void Testar_Tabuleiro (void) {
	CU_pSuite suite;
	
	suite = CU_add_suite("TABULEIRO",NULL,NULL);
	
	CU_ADD_TEST(suite, Testar_Trocar_Captar_Valor);
	CU_ADD_TEST(suite, Testar_Limpar_FIR_L);
	CU_ADD_TEST(suite, Testar_Limpar_LAS_L);
	CU_ADD_TEST(suite, Testar_Limpar_NUM_L);
	CU_ADD_TEST(suite, Testar_Limpar_ALL_L);
}

int main (int argc, char *argv[]) {
	if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

	srand (time(NULL));
	
	Testar_Tabuleiro();
	Testar_Peca();

	Liberar_Tabuleiro();
	Liberar_Peca();
	
	CU_basic_set_mode(CU_BRM_VERBOSE);
	
	CU_basic_run_tests();
	
	CU_cleanup_registry();
	
	return CU_get_error();
}