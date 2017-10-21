#include "filtros.h"

// void eco(tipoWav* wav, FILE *entradaWav,FILE *saidaWav,int delay, float aten){
// 	int16_t* amostra;
// 	amostra = malloc (2); //aloca espaço no tamanho de uma amostra

// 	/*escreve o cabeçalho no arquivo de saida*/
// 	fwrite(wav, 1, 44, saidaWav);
// 	fseek(entradaWav,44,SEEK_SET);
// 	aqui ta somando "volume" vezes, ao invéz de multiplicar pelo volume
// 	while(!feof(entradaWav)){
// 		// printf(" no while com ponteiro em: %ld\n",ftell(entradaWav) );
// 		fread(amostra,2,1,entradaWav); //coleta amostra de audio
		


// 		fwrite(amostra,2,1,saidaWav); //escreve amostra de audio no arquivo de saida
// 	}
// }


int main(int argc, char *argv[]){
	printf("CODIGO EM DESENVOLVIMENTO xD\n");
	// int opt,prosseguir=0;
	// int delay;
	// FILE *entradaWav,*saidaWav;
	// tipoWav wav;
	// while( (opt = getopt(argc, argv, "t:l:i:o:")) > 0 ) {
	// 	switch ( opt ) {
	//         case 't': /* opção -n */
	// 			delay = atoi(optarg) ;
	// 			if ((delay<0)){
	// 				puts("Digite um delay maior ou igual a 0.0");
	// 				exit(1);
	// 			}
	//             break ;
	//         case 'l': /* opção -n */
	// 			aten = atoi(optarg) ;
	// 			if ((aten<0)||(aten>1)){
	// 				puts("Digite uma atenuação entre 0.0 e 1.0");
	// 				exit(1);
	// 			}
	//             break ;     	    
 //     	    case 'i': /* help */
	// 			entradaWav = fopen(optarg, "r");
	// 			if(!entradaWav) {
	// 				perror("Erro ao abrir arquivo de entrada");
	// 				exit(1);
	// 			} else prosseguir =1;
	// 			lerWav(entradaWav, &wav);
 //               break ;
	//            case 'o': /* opção -n */
	// 			saidaWav = fopen(optarg, "w+");
	//             break ;
 //           default:
 //            	fprintf(stderr, "Opcao invalida ou faltando argumento: `%c'\n", optopt) ;
 //              	return -1 ;
	// 	}        
	// }
	// if(prosseguir){
	// 	eco( &wav, entradaWav,saidaWav,delay, aten);
	// } else {puts("opção invalida ou faltando argumento.");}
}