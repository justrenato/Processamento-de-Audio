#include "filtros.h"

void setVolume(tipoWav* wav, FILE *entradaWav,FILE *saidaWav){
	float volume=1;
	int16_t* amostra;
	amostra = malloc (2); //aloca espaço no tamanho de uma amostra
	printf("Digite o volume(min: 0 max: 10): \n");
	scanf("%f",&volume);
	while((volume<0)||(volume>10)){
		printf("Valor não aceito.\n");
		printf("Digite o volume(min: 0 max: 10): \n");
		scanf("%f",&volume);
	}

	/*escreve o cabeçalho no arquivo de saida*/
	fwrite(wav, 1, 44, saidaWav);
	fseek(entradaWav,44,SEEK_SET);
	/*aqui ta somando "volume" vezes, ao invéz de multiplicar pelo volume*/
	while(!feof(entradaWav)){
		// printf(" no while com ponteiro em: %ld\n",ftell(entradaWav) );
		fread(amostra,2,1,entradaWav); //coleta amostra de audio
		*amostra=*amostra*volume;
		fwrite(amostra,2,1,saidaWav); //escreve amostra de audio no arquivo de saida
	}
}