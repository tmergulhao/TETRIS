#include <time.h>

#include "metronomo.h++"

ClassMetronomy::ClassMetronomy () {
	limit = clock();
	tempo = 2; // STANDART 2 SECOND
}
void ClassMetronomy::SetTempo (float t) {
	if (t <= 0)	tempo = 2; // STANDART 2 SECOND
	else tempo = t;
	
	limit = clock() +  CLOCKS_PER_SEC * tempo;
}
bool ClassMetronomy::Tempo () {
	if (limit > clock()) return 0;
	
	limit = clock() +  CLOCKS_PER_SEC * tempo;
	return 1;
}
