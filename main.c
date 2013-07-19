#include "engine.h"

int main (int argc, char *argv[]) {
	int i;
	
	Iniciar_Modulos();
	
	if ((i = Testar_Interface())) {
		while ((i = Capturar_Opcao()) != 2) {
			if (i == 0) Jogar();
			if (i == 1) Mostrar_Score();
		}
	}
	
	Finalizar_Modulos();

	return 0;
}
