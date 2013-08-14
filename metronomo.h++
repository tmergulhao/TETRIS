#ifndef MOD_METRONOMO
#define MOD_METRONOMO

	#include <stdbool.h>
	#include <time.h>
	
	class ClassMetronomy {
			clock_t limit;
			float tempo;
		public:
			float espera;
			
			bool Tempo ();
			float ViewTempo () {return tempo;}
			void SetTempo (float t);
			void FalseFire () {limit = clock() +  CLOCKS_PER_SEC * tempo;}
			
			ClassMetronomy ();
	};
#endif
