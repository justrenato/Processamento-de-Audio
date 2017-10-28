//RENATO RIBEIRO DA SILVA GRR20172113
#include "filtros.h"

void lerWav(FILE *entradaWav, tipoWav* wav){
	/*Le o cabeçalho e informações sobreo formato do audio*/

	fread(wav, 44, 1, entradaWav);

  	/*Aloca espaço em wav->Data do tamanho do espaço ocupado pelas amostras de audio (indicado em wav->Subchuk2Size)*/
	wav->Data = malloc(wav->Subchunk2Size);

	/*Começa ler as amostras de audio*/
	fread(wav->Data, wav->Subchunk2Size,1, entradaWav);
	rewind(entradaWav);
}

// void controleComandos(int argc, char *argv[]){
// 	int opt,prosseguir=0;
// 	float volume;
// 	FILE *entradaWav,*saidaWav;
// 	tipoWav wav;
// 	while( (opt = getopt(argc, argv, "i:o:l:")) > 0 ) {
// 		switch ( opt ) {
// 	        case 'l': /* opção -n */
// 				volume = atoi(optarg) ;
// 				if ((volume<0)||(volume>10)){
// 					puts("Digite um volume de 0.0 até 10.0.");
// 					exit(1);
// 				}
// 	            break ; 
//      	    case 'i': /* help */
// 				entradaWav = fopen(optarg, "r");
// 				if(!entradaWav) {
// 					perror("Erro ao abrir arquivo de entrada");
// 					exit(1);
// 				} else prosseguir=1;
// 				lerWav(entradaWav, &wav);
//                break ;
// 	           case 'o': /* opção -n */
// 				saidaWav = fopen(optarg, "w+");
// 	            break ;
//            default:
//                fprintf(stderr, "Opcao invalida ou faltando argumento: `%c'\n", optopt) ;
//                opt = -1 ;
// 		}
// 	}

// 	if(prosseguir){
// 		// infoWav(&wav);
// 	} else {
// 		puts("opção invalida ou faltando argumento.");
// 	}
// }