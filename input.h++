#ifndef MOD_INPUT
	#define MOD_INPUT
	
	#include <SDL2/SDL.h>
	
	#include <iostream>
	#include <vector>
	
	#include "metronomo.h++"
	
	class ClassInput {
			ClassInput();
			static ClassInput *p_instance;
			const Uint8* keystate;
			ClassMetronomy TEMPO;
		public:
			static ClassInput* instance () {
				if (p_instance) return p_instance;
				return (p_instance = new ClassInput());
			}
			bool isKeyDown(SDL_Scancode);
	};
	typedef ClassInput INPUT;
#endif
