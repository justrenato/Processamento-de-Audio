#include "filtros.h"

void cat(int argc, char *argv[],FILE *saidaWav){
	saidaWav = fopen(argv[argc-1],"w+");
	FILE *entrada;
	for (int i = 0; i < argc -2; ++i)
	{
		entrada = fopen(argv[i],"r");
	}
}


int main(int argc, char *argv[]){
	

	FILE *saidaWav;
	cat(argc,argv,saidaWav);
	
	return 0;
}