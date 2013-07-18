#ifndef MOD_PECA
#define MOD_PECA

#ifdef SERVIDOR_PECA
#define EXT_MOD_PECA
#else
#define EXT_MOD_PECA extern
#endif

typedef struct {
	int X, Y;
} BLOCO_TIPO;
typedef struct {
	int X, Y;
	BLOCO_TIPO BLOCO[4];
} PECA;

// Interface para MAIN.C
EXT_MOD_PECA PECA* Chamar_Peca();
EXT_MOD_PECA void Rotacionar_Peca();
EXT_MOD_PECA void Iniciar_Peca();

#endif