#include "filtros.h"

void reverteWav(tipoWav* wav, FILE *entradaWav,FILE *saidaWav){
	int16_t* amostra;
	amostra = malloc (wav->BitsPerSample); //aloca espaço no tamanho de uma amostra

	/*escreve o cabeçalho no arquivo de saida*/
	fwrite(wav, 1, 44, saidaWav);

	fseek (entradaWav, -1*(wav->BitsPerSample), SEEK_END) ; // aponta o equivalente ao tamanho de uma amostra antes do final do arquivo do arquivo de entrada 

	while(ftell(entradaWav)>43){ //enquanto não chega ao cabeçalho (no bit 43) do arquivo de entrada, coleta amostras
		fseek (entradaWav, -2*(wav->BitsPerSample), SEEK_CUR) ; // seta o apontador para duas amostras atras
		fread(amostra,wav->BitsPerSample,1,entradaWav); //coleta amostra de audio
		fwrite(amostra,wav->BitsPerSample,1,saidaWav); //escreve amostra de audio no arquivo de saida
	}
}