#include "filtros.h"


void ajustVolume(tipoWav* wav, FILE *entradaWav,FILE *saidaWav){
	int16_t *amostra,maior,menor;
	amostra = malloc (wav->BitsPerSample); //aloca espaço no tamanho de uma amostra
	
	/*escreve o cabeçalho no arquivo de saida*/
	fwrite(wav, 1, 44, saidaWav);


	fread(amostra,wav->BitsPerSample,1,entradaWav); //coleta amostra de audio
	menor=*amostra;
	maior=*amostra;

	while(!feof(entradaWav)){
		fread(amostra,wav->BitsPerSample,1,entradaWav); //coleta amostra de audio
		if(*amostra>PICOMAX){
			printf("amostra: %d\n",*amostra );
		}
		if (*amostra>maior)
		{
			maior=*amostra;
		}
		if (*amostra<menor)
		{
			menor=*amostra;
		}
	}
	printf("amostra: %d\n",*amostra );
	printf("maior: %d\n",maior );
	printf("menor: %d\n",menor );
	// maior=(((float)maior / PICOMAX)*100);
	// menor=(((float)menor / PICOMIN)*100);
	// printf("maior: %d\n",maior );
	// printf("menor: %d\n",menor );

	fseek(entradaWav,44,SEEK_SET);
	fread(amostra,wav->BitsPerSample,1,entradaWav); //coleta amostra de audio
	while(!feof(entradaWav)){
		if ((*amostra>0)&&(maior>PICOMAX))
		{
			*amostra=*amostra * -1*((((float)maior/PICOMAX)*100)-100);
		}

		if ((*amostra<0)&&(menor<PICOMIN))
		{
			*amostra=*amostra * ((((float)maior/PICOMAX)*100)-100);
		}


		fwrite(amostra,wav->BitsPerSample,1,saidaWav); //escreve amostra de audio no arquivo de saida
		fread(amostra,wav->BitsPerSample,1,entradaWav); //coleta amostra de audio
	}
}