#include "filtros.h"

int main(){

	FILE *entradaWav = fopen("adele.wav", "r");
	if(!entradaWav) {
		perror("Erro ao abrir arquivo de entrada");
		exit(1);
	}

	FILE *saidaWav = fopen("saida.wav", "w+");
	if(!saidaWav){
		perror("Erro ao criar arquivo de saída");
		exit(1);
	}

	tipoWav wav;
	lerWav(entradaWav, &wav);

	// infoWav(&wav);
	// escreverWav( &wav, saidaWav);
	// inverteWav( &wav, entradaWav,saidaWav);
	setVolume( &wav, entradaWav,saidaWav);
	// ajustVolume( &wav, entradaWav,saidaWav);

	int fcloseall (void);
}
