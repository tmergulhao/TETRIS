#ifndef MOD_MAIN
	#define MOD_MAIN
	
	#include <stdlib.h>
	#include <time.h>
	
	#ifdef NCURSES
		#define KEY_SPACE			32
	#endif
	
	// STRUCTURE DEFS
	#define BETWEEN(X,DOWN,UP)	((X) >= (DOWN) && (X) <= (UP))
	
	// CANVAS DEFS
	#define CANVAS_WIDTH		10
	#define CANVAS_HEIGHT		20
#endif
