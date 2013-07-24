#include "engine.h"

#include "assert.h"
#ifndef ASSERT
	#define assert(ignore)((void) 0)
#endif

int main (int argc, char *argv[]) {
	int i;
	
	assert(i == 10);

	Iniciar_Modulos();
	
	if ((i = Testar_Interface())) {
		while ((i = Capturar_Opcao()) != 3) {
			if (i == 0) Jogar();
			if (i == 1) Mostrar_Score();
		}
	}
	
	Finalizar_Modulos();

	return 0;
}
