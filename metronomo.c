#include <time.h>
#include <stdlib.h>

#include "metronomo.h"

struct TIPO_TEMPORIZADOR {
	clock_t timer;
	float espera;
	struct TIPO_TEMPORIZADOR *NEXT;
};
typedef struct TIPO_TEMPORIZADOR TEMPORIZADOR;

float metronomy (float mode, int which) {
	static TEMPORIZADOR* timer;
	TEMPORIZADOR* timer_use = timer;
	
	while (which && timer_use && timer_use->NEXT) {
		timer_use = timer_use->NEXT;
		which--;
	}
	if (!(timer_use)) {
		if (timer_use) 	timer_use->NEXT = (TEMPORIZADOR*)malloc(sizeof(TEMPORIZADOR));
		else 			timer = timer_use = (TEMPORIZADOR*)malloc(sizeof(TEMPORIZADOR));
		
		timer_use->espera = ESPERA_INPUT;
		timer_use->timer = clock() +  CLOCKS_PER_SEC * timer_use->espera;
		
		return 0;
	}
	if(mode == -1 && timer_use->timer < clock()) {
		if (timer_use->espera <= 0) timer_use->espera = ESPERA_INPUT;
		
		timer_use->timer = clock() +  CLOCKS_PER_SEC * timer_use->espera;
		
		return 1;
	}
	else 	if (mode == -3) 	timer_use->timer = clock() +  CLOCKS_PER_SEC * timer_use->espera; // FALSEFIRE
	else 	if (mode == -2) 	return timer_use->espera; // VIEW
	else 	if (mode > 0) 		return timer_use->espera = mode; // SET
	
	if (!mode) while (timer) {
		timer_use = timer;
		timer = (timer->NEXT) ? timer->NEXT : NULL;
		free(timer_use);
	}
	
	return 0;
}