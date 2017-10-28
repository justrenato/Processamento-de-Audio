//RENATO RIBEIRO DA SILVA GRR20172113
#include "filtros.h"

void estAmp(tipoWav* wav, FILE *entradaWav,FILE *saidaWav,float k){
	if(wav->NumChannels ==2){
		int16_t *amostradir,*amostraesq, diff;
		amostradir = malloc (2); //aloca espaço no tamanho de uma amostra
		amostraesq = malloc (2); //aloca espaço no tamanho de uma amostra

		/*escreve o cabeçalho no arquivo de saida*/
		fwrite(wav, 1, 44, saidaWav);
		fseek(entradaWav,44,SEEK_SET);

		while(!feof(entradaWav)){
			// printf(" no while com ponteiro em: %ld\n",ftell(entradaWav) );
			fread(amostraesq,2,1,entradaWav); //coleta amostra de audio
			fread(amostradir,2,1,entradaWav); //coleta amostra de audio
			diff = *amostradir - *amostraesq;
			*amostradir = *amostradir + k * diff;
			*amostraesq = *amostradir - k * diff;
			fwrite(amostraesq,2,1,saidaWav); //escreve amostra de audio no arquivo de saida
			fwrite(amostradir,2,1,saidaWav); //escreve amostra de audio no arquivo de saida
		}
	}
}

int main(int argc, char *argv[]){
	int opt,prosseguir=0;
	float k;
	FILE *entradaWav,*saidaWav;
	tipoWav wav;
	while( (opt = getopt(argc, argv, "l:i:o:")) > 0 ) {
		switch ( opt ) {
	        case 'l': /* opção -n */
				k = atoi(optarg) ;
				if ((k<0)||(k>10)){
					puts("Digite um k de 0.0 até 10.0.");
					exit(1);
				}
	            break ;     	    
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
		estAmp( &wav, entradaWav,saidaWav,k);
	} else {puts("opção invalida ou faltando argumento.");}
}