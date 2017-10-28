//RENATO RIBEIRO DA SILVA GRR20172113
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
		reverteWav( &wav, entradaWav,saidaWav);
	} else {puts("opção invalida ou faltando argumento.");}
}