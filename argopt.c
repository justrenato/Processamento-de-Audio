#include <stdio.h>
#include <stdlib.h>
/* para getopt() */
#include <unistd.h>

/* Mostra a ajuda */
void show_help(char *name) {
    fprintf(stderr, "\
            [uso] %s <opcoes>\n\
            -h         mostra essa tela e sai.\n\
            -n NOME    seta o seu nome.\n\
            -i IDADE   seta sua idade.\n\
            -e ESTADO  seta seu estado.\n\
            -c         cadastra no banco de dados.\n", name) ;
    exit(-1) ;
}

int main(int argc, char **argv) {
    int opt ;

    /* Variáveis que receberão os argumentos
     * das opções. */
    char *nome=NULL, *idade=NULL, *estado=NULL ;
    char flag_cadastrar = 0 ;

    /* Chama ajuda. */
    if ( argc < 2 ) show_help(argv[0]) ;

    /* getopt() retorna o caractere de uma opção a cada
     * iteração e -1 para marcar o fim do processo. */
    while( (opt = getopt(argc, argv, "hn:i:e:c")) > 0 ) {
        switch ( opt ) {
            case 'h': /* help */
                show_help(argv[0]) ;
                break ;
            case 'n': /* opção -n */
                nome = optarg ;
                break ;
            case 'i': /* opção -i */
                idade = optarg ;
                break ;
            case 'e': /* opção -e */
                estado = optarg ;
                break ;
            case 'c': /* opção -c */
                flag_cadastrar = 1 ;
                break ;
            default:
                fprintf(stderr, "Opcao invalida ou faltando argumento: `%c'\n", optopt) ;
                return -1 ;
        }
    }

    /* Mostra os dados na tela. */
    printf("Seus dados: \n\
            Nome   : %s\n\
            Idade  : %s\n\
            Estado : %s\n", nome, idade, estado) ;

    printf("Dados gravados no banco de dados: ") ;
    if ( flag_cadastrar == 0 ) printf("NAO.\n") ;
    else printf("SIM.\n") ;

    /* Mostra os argumentos em excesso */
    if ( argv[optind] != NULL ) {
        int i ;

        puts("** Argumentos em excesso **") ;
        for(i=optind; argv[i] != NULL; i++) {
            printf("-- %s\n", argv[i]) ;
        }
    }

    return 0 ;
}
/* EOF */