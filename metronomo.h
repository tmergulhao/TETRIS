#ifndef MOD_METRONOMO
#define MOD_METRONOMO

#ifdef SERVIDOR_METRONOMO
#define EXT_MOD_METRONOMO
#else
#define EXT_MOD_METRONOMO extern
#endif

#define ESPERA_INPUT 		3 // seconds

#define Desligar_Espera() 	metronomy(0,0)

#define Tempo_Espera() 		metronomy(-1,0)

#define Tempo_Jogo() 		metronomy(-1,1)
#define Ver_T_Jogo()		metronomy(-2,1)
#define Mudar_Tempo_Jogo(X) if((Ver_T_Jogo()+X) > 0) metronomy(Ver_T_Jogo() + X,1)

// Interface para ENGINE.C
EXT_MOD_METRONOMO float metronomy (float mode, int which);

#endif