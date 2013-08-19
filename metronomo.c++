#include <time.h>

#include "metronomo.h++"

ClassMetronomy::ClassMetronomy () {
	SetTempo();
	limit = clock() +  CLOCKS_PER_SEC * tempo;
}
void ClassMetronomy::SetTempo (double t) {
	tempo = t;
	limit = clock() +  CLOCKS_PER_SEC * tempo;
}
bool ClassMetronomy::Tempo () {
	if (limit > clock()) return 0;
	
	limit = clock() +  CLOCKS_PER_SEC * tempo;
	return 1;
}
