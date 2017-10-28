//RENATO RIBEIRO DA SILVA GRR20172113
#include "filtros.h"

void mix(int argc, char *argv[]){
	int16_t *amostraEntrada,*amostraSaida,*amostra,BitsPerSample;
	uint32_t tam,newTam,newchunkSize;
	tipoWav wav;
	FILE *saidaWav;

	FILE *entradaWav = fopen(argv[1],"r");
	if(!entradaWav) {
		perror("Erro ao abrir arquivo de entrada");
		exit(1);
	}

	if (!strcmp(argv[argc-2],"-o")) //se o penultimo argumento for -o ele abre um arquivo com o nome do ultimo
	{
		saidaWav = fopen(argv[argc-1],"w+");
		if(!saidaWav) {
			perror("Erro ao abrir arquivo de saida");
			exit(1);
		}
	} else{
		puts("Utilize o formato de comando: wavmix arq1.wav arq2.wav arq3.wav ... -o output");
		exit(1);
	} 

	fseek(entradaWav,34,SEEK_SET); //coloca o ponteiro no bit 34 da saida
	fread(&BitsPerSample,2,1,entradaWav); //le o BitsPerSample

	fseek(entradaWav,40,SEEK_SET); //coloca o ponteiro no bit 40 da saida
	fread(&newTam,4,1,entradaWav); //le o subChunk2Size
	
	rewind(entradaWav); //recoloca o ponteiro no inicio

	lerWav(entradaWav,&wav); //passa para a struct o cabeçalho

	fwrite(&wav,44,1,saidaWav);	// escreve no arquivo de saida o cabeçalho
	amostra = malloc (BitsPerSample/2); //aloca espaço no tamanho de uma amostra
	amostraEntrada = malloc (BitsPerSample/2); //aloca espaço no tamanho de uma amostra
	amostraSaida = malloc (BitsPerSample/2); //aloca espaço no tamanho de uma amostra
	fread(amostraEntrada,BitsPerSample/2,1,entradaWav); //coleta amostra de audio

	while(!feof(entradaWav)){
		fwrite(amostra,BitsPerSample/2,1,saidaWav); //escreve amostra de audio no arquivo de saida
		fread(amostra,BitsPerSample/2,1,entradaWav); //coleta amostra de audio
	}


	for (int i = 2; i < argc -2; ++i)
	{
		entradaWav = fopen(argv[i],"r");
		if(!entradaWav) {
			perror("Erro ao abrir arquivo de entrada");
			printf("Arquivo: %s\n",argv[i] );
			exit(1);
		} 
		else {
			fseek(saidaWav,44,SEEK_SET); //coloca o ponteiro no bit 44 da saida para mixar amostras
			fseek(entradaWav,40,SEEK_SET);
			fread(&tam,4,1,entradaWav); //le o subChunk2Size
			if (tam > newTam)
			{
				newTam =  tam; //ve o maior arquivo 
			}

			fread(amostraEntrada,BitsPerSample/2,1,entradaWav); //coleta amostra de audio
			while(!feof(entradaWav)){
				fread(amostraSaida,BitsPerSample/2,1,saidaWav); //coleta amostra de audio
				if (!feof(saidaWav))
				{
					*amostra = *amostraSaida + *amostraEntrada;
					fseek(saidaWav,-BitsPerSample/2,SEEK_CUR);
					fwrite(amostra,BitsPerSample/2,1,saidaWav); //escreve amostra de audio no arquivo de saida
				} else fwrite(amostraEntrada,BitsPerSample/2,1,saidaWav);



				fread(amostra,BitsPerSample/2,1,entradaWav); //coleta amostra de audio
			}
		}
	}
	fseek(saidaWav,4,SEEK_SET);
	newchunkSize = newTam + 44 - 8;
	fwrite(&newchunkSize,4,1,saidaWav);

	fseek(saidaWav,40,SEEK_SET);
	fwrite(&newTam,4,1,saidaWav);
}


int main(int argc, char *argv[]){
	
	mix(argc,argv);
	
	return 0;
}