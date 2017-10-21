#include "filtros.h"

void setVolume(tipoWav* wav, FILE *entradaWav,FILE *saidaWav,float vol){
	int16_t* amostra;
	amostra = malloc (2); //aloca espaço no tamanho de uma amostra

	/*escreve o cabeçalho no arquivo de saida*/
	fwrite(wav, 1, 44, saidaWav);
	fseek(entradaWav,44,SEEK_SET);

	while(!feof(entradaWav)){
		// printf(" no while com ponteiro em: %ld\n",ftell(entradaWav) );
		fread(amostra,2,1,entradaWav); //coleta amostra de audio
		*amostra=*amostra*vol;
		fwrite(amostra,2,1,saidaWav); //escreve amostra de audio no arquivo de saida
	}
}

int main(int argc, char *argv[]){
	int opt,prosseguir=0;
	float volume;
	FILE *entradaWav,*saidaWav;
	tipoWav wav;
	while( (opt = getopt(argc, argv, "l:i:o:")) > 0 ) {
		switch ( opt ) {
	        case 'l': /* opção -n */
				volume = atoi(optarg) ;
				if ((volume<0)||(volume>10)){
					puts("Digite um volume de 0.0 até 10.0.");
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
		setVolume( &wav, entradaWav,saidaWav,volume);
	} else {puts("opção invalida ou faltando argumento.");}
}