#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	FILE *arq ;
	arq = fopen ("./adele.wav", "r") ;

  if (!arq)
  {
    perror ("Erro encontrado ao tentar abrir arquivo") ;
    exit (1) ;
  } puts("arquivo aberto");
  long int vetor[400];





  // fread (vetor, 4, 100, arq);
  //fwrite (vetor, 4, 100, arq);
return 0;
}