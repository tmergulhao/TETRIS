#include "engine.h"

int main (int argc, char *argv[]) {
	int i;
	
	Iniciar_Modulos();
	
	if ((i = Testar_Interface())) {
		while ((i = Capturar_Opcao()) != 2) {
			if (i == 0) Mostrar_Score();
			if (i == 1) Jogar();
		}
	}
	
	Finalizar_Modulos();

	return 0;
}
