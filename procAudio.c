#include "filtros.h"

int main(int argc, char *argv[]){
	int opt, indexptr = 0;
	char *entrada,*saida;
	FILE *entradaWav,*saidaWav;
	tipoWav wav;

	// while( (opt = getopt(argc, argv, "i:o:frva")) > 0 ) {
	//        switch ( opt ) {
	//      	    case 'i': /* help */
	// 			entradaWav = fopen(optarg, "r");
	// 			lerWav(entradaWav, &wav);
	//                break ;
	//            case 'o': /* opção -n */
	// 			saidaWav = fopen(optarg, "w+");
	//                break ;
	//            case 'f': /* opção -i */
	//                infoWav(&wav);
	//                break ;
	//            case 'r': /* opção -e */
	//                reverteWav( &wav, entradaWav,saidaWav);
	//                break ;
	//            case 'v': /* opção -c */
	//                setVolume( &wav, entradaWav,saidaWav);
	//                break ;
	//            case 'a': /* opção -c */
	//                ajustVolume( &wav, entradaWav,saidaWav);
	//                break ;
	//            default:
	//                fprintf(stderr, "Opcao invalida ou faltando argumento: `%c'\n", optopt) ;
	//                return -1 ;
	//        }
	//        printf("%s\n",optarg );        
	//     }

	// FILE *entradaWav = fopen("adele.wav","r");
	// if(!entradaWav) {
	// 	perror("Erro ao abrir arquivo de entrada");
	// 	exit(1);
	// }
	// FILE *saidaWav = fopen("saida.wav","w+");
	// if(!saidaWav) {
	// 	perror("Erro ao abrir arquivo de saida");
	// 	exit(1);
	// }

	lerWav(entradaWav, &wav);
	// infoWav(&wav);
	// escreverWav( &wav, saidaWav);
	// reverteWav( &wav, entradaWav,saidaWav);
	// setVolume( &wav, entradaWav,saidaWav);
	// ajustVolume( &wav, entradaWav,saidaWav);

	// int fcloseall (void);
}
