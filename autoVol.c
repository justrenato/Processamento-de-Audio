#include "filtros.h"


void ajustVolume(tipoWav* wav, FILE *entradaWav,FILE *saidaWav){
	int16_t *amostra,maior;
	float taxa;
	amostra = malloc (wav->BitsPerSample); //aloca espaço no tamanho de uma amostra
	
	/*escreve o cabeçalho no arquivo de saida*/
	fwrite(wav, 1, 44, saidaWav);


	fread(amostra,wav->BitsPerSample,1,entradaWav); //coleta amostra de audio
	maior=*amostra;

	while(!feof(entradaWav)){
		fread(amostra,wav->BitsPerSample,1,entradaWav); //coleta amostra de audio
		if (*amostra<0)
		{
			*amostra*=-1;
		}

		if (*amostra>maior)
		{
			maior=*amostra;
		}
	}
	taxa=0; /*so inicializando pra nao xiar no -Wall*/
	taxa = PICO/(float)maior;
	fseek(entradaWav,44,SEEK_SET);
	fread(amostra,wav->BitsPerSample,1,entradaWav); //coleta amostra de audio
	while(!feof(entradaWav)){
		fwrite(amostra,wav->BitsPerSample,1,saidaWav); //escreve amostra de audio no arquivo de saida
		*amostra=*amostra*taxa;
		fread(amostra,wav->BitsPerSample,1,entradaWav); //coleta amostra de audio
	}
}


int main(int argc, char *argv[]){
	int opt,prosseguir=0;
	FILE *entradaWav,*saidaWav;
	tipoWav wav;
	while( (opt = getopt(argc, argv, "i:o:")) > 0 ) {
		switch ( opt ) {    	    
     	    case 'i': /* help */
				entradaWav = fopen(optarg, "r");
				if(!entradaWav) {
					perror("Erro ao abrir arquivo de entrada");
					exit(1);
				} else prosseguir =1;
				lerWav(entradaWav, &wav);
               break ;
	           case 'o': /* opção -n */
				saidaWav = fopen(optarg, "w+");
	            break ;
           default:
            	fprintf(stderr, "Opcao invalida ou faltando argumento: `%c'\n", optopt) ;
              	return -1 ;
		}        
	}
	if(prosseguir){
		ajustVolume( &wav, entradaWav,saidaWav);
	} else {puts("opção invalida ou faltando argumento.");}
}