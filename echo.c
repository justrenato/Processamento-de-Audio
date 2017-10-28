//RENATO RIBEIRO DA SILVA GRR20172113
#include "filtros.h"
#define TOTALAMOSTRAS 8*wav->Subchunk2Size/wav->BitsPerSample
void echo(tipoWav* wav, FILE *entradaWav,FILE *saidaWav,int delay, float aten){
	tipoWav wavAux;
	lerWav(entradaWav, &wavAux);

	/*escreve o cabeçalho no arquivo de saida*/
	fwrite(wav, 1, 44, saidaWav);
	fseek(entradaWav,44,SEEK_SET);
	
	for (int i = delay; i < TOTALAMOSTRAS; ++i)
	{
		wav->Data[i] = wavAux.Data[i] + (wavAux.Data[i-delay] * aten);
	}

	fwrite(wav->Data,wav->Subchunk2Size,1,saidaWav);
}


int main(int argc, char *argv[]){
	int opt,prosseguir=0;
	int delay=1000;
	float aten=0.5;
	FILE *entradaWav,*saidaWav;
	tipoWav wav;
	while( (opt = getopt(argc, argv, "t:l:i:o:")) > 0 ) {
		switch ( opt ) {
	        case 't': /* opção -n */
				delay = atoi(optarg) ;
				if ((delay<0)){
					puts("Digite um delay maior ou igual a 0.0");
					exit(1);
				}
	            break ;
	        case 'l': /* opção -n */
				aten = atof(optarg) ;
				if ((aten<0)||(aten>1)){
					puts("Digite uma atenuação entre 0.0 e 1.0");
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
		echo( &wav, entradaWav,saidaWav,delay, aten);
	} 
	else { 
		puts("opção invalida ou faltando argumento.");
	}
}