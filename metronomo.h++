#ifndef MOD_METRONOMO
#define MOD_METRONOMO

	#include <stdbool.h>
	#include <time.h>
	
	class ClassMetronomy {
			clock_t limit;
			double tempo;
		public:
			float espera;
			
			bool Tempo ();
			float ViewTempo () {return tempo;}
			void SetTempo (double t = 2);
			void FalseFire () {limit = clock() +  CLOCKS_PER_SEC * tempo;}
			
			ClassMetronomy ();
	};
#endif
