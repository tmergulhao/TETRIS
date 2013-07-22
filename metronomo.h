#ifndef MOD_METRONOMO
#define MOD_METRONOMO

#ifdef SERVIDOR_METRONOMO
#define EXT_MOD_METRONOMO
#else
#define EXT_MOD_METRONOMO extern
#endif

#define ESPERA_INPUT 		3 // seconds

// Interface para ENGINE.C
EXT_MOD_METRONOMO float metronomy (float mode, int which);

#endif