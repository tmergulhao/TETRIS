#ifndef MOD_ENGINE
#define MOD_ENGINE

#ifdef SERVIDOR_ENGINE
#define EXT_MOD_ENGINE
#else
#define EXT_MOD_ENGINE extern
#endif

// STRUCTURE DEFS
#define BETWEEN(X,DOWN,UP)	((X) >= (DOWN) && (X) <= (UP))

// MAIN DEFS
#define CANVAS_WIDTH		10
#define CANVAS_HEIGHT		20

// Interface para MAIN.C
EXT_MOD_ENGINE void Iniciar_Modulos();
EXT_MOD_ENGINE void Mostrar_Score();
EXT_MOD_ENGINE void Finalizar_Modulos();
EXT_MOD_ENGINE void Jogar();

EXT_MOD_ENGINE int Testar_Interface();
EXT_MOD_ENGINE int Capturar_Opcao();

#endif