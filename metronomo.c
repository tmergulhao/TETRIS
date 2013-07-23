#include <time.h>
#include <stdlib.h>

#include "metronomo.h"

struct TIPO_TEMPORIZADOR {
	clock_t TEMPO;
	float espera;
	struct TIPO_TEMPORIZADOR *NEXT;
};
typedef struct TIPO_TEMPORIZADOR TEMPORIZADOR;

float metronomy (float mode, int which) {
	static TEMPORIZADOR* timer;
	TEMPORIZADOR* timer_use;
	
	if (!mode) {
		while (timer) {
			timer_use = timer;
			timer = timer->NEXT;
			free(timer_use);
		}
		return 0;
	}
	
	if (!timer) {
		timer = (TEMPORIZADOR*)malloc(sizeof(TEMPORIZADOR));
		timer->NEXT = NULL;
		timer->espera = ESPERA_INPUT;
	}
	timer_use = timer;
	
	for (; which; which--) {
		if (!timer->NEXT) {
			timer_use->NEXT = (TEMPORIZADOR*)malloc(sizeof(TEMPORIZADOR));
			timer_use->NEXT->NEXT = NULL;
			timer_use->NEXT->espera = ESPERA_INPUT;
			timer_use->NEXT->TEMPO = clock() +  CLOCKS_PER_SEC * timer_use->espera;
		}
		timer_use = timer_use->NEXT;
	}
	
	if(mode == -1 && timer_use->TEMPO < clock()) {
		if (timer_use->espera <= 0) timer_use->espera = ESPERA_INPUT;
		
		timer_use->TEMPO = clock() +  CLOCKS_PER_SEC * timer_use->espera;
		
		return 1;
	}
	else 	if (mode == -3) 	timer_use->TEMPO = clock() +  CLOCKS_PER_SEC * timer_use->espera; // FALSEFIRE
	else 	if (mode == -2) 	return timer_use->espera; // VIEW
	else 	if (mode > 0) 		return timer_use->espera = mode; // SET
	
	return 0;
}