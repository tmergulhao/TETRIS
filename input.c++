#include "input.h++"

ClassInput* ClassInput::p_instance = 0;

ClassInput::ClassInput () {
	TEMPO.SetTempo(0.15);
}
bool ClassInput::isKeyDown(SDL_Scancode key) {
	keystate = SDL_GetKeyboardState(0); // CORRECT
	static SDL_Scancode lastkey;
	static bool trap;
	
	if (keystate[lastkey] == 1 && !trap && !TEMPO.Tempo()) return 0;
	else trap = true;
	
	if (keystate[key] == 1) {
		lastkey = key;
		trap = false;
		TEMPO.FalseFire();
		return true;
	}
	
	return false;
}
