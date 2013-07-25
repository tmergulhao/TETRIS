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

struct TIPO_PECA {
	int X, Y;
	BLOCO_TIPO BLOCO[4];
	struct TIPO_PECA *NEXT;
};
typedef struct TIPO_PECA PECA;

struct TIPO_GUIA_PECAS {
	struct TIPO_PECA *ENTER;
};
typedef struct TIPO_GUIA_PECAS GUIA_PECAS;

// Interface para ENGINE.C
#define Chamar_Peca_Principal()	 	Chamar_Peca(+0)
#define Chamar_Peca_Secundari()	 	Chamar_Peca(+1)
#define Liberar_Pecas()				Chamar_Peca(-1)

EXT_MOD_PECA PECA* Chamar_Peca(int mode);
EXT_MOD_PECA void Rotacionar_Peca(PECA* PECA_ATUAL);
EXT_MOD_PECA void Iniciar_Peca(int i,PECA* PECA_ATUAL);

#endif