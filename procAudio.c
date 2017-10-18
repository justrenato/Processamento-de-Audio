#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#define PICOMAX 32767
#define PICOMIN -32767

typedef struct tipoWav{
	char ChunkID[4];
	uint32_t ChunkSize;
	char Format[4];
	char Subchunk1ID[4];
	uint32_t Subchunk1Size;
	uint16_t AudioFormat;
	uint16_t NumChannels;
	uint32_t SampleRate;
	uint32_t ByteRate;
	uint16_t BlockAlign;
	uint16_t BitsPerSample;
	char Subchunk2ID[4];
	uint32_t Subchunk2Size;
	int16_t *Data;
}tipoWav;

void lerWav(FILE *entradaWav, tipoWav* wav){
	/*Le o cabeçalho e informações sobreo formato do audio*/

	fread(wav, 44, 1, entradaWav);

  	/*Aloca espaço em wav->Data do tamanho do espaço ocupado pelas amostras de audio (indicado em wav->Subchuk2Size)*/
	wav->Data = malloc(wav->Subchunk2Size);

	/*Começa ler as amostras de audio*/
	fread(wav->Data, wav->Subchunk2Size,1, entradaWav);
	rewind(entradaWav);
}

void escreverWav(tipoWav* wav, FILE *saidaWav ){
	/*Escreve o cabeçalho e informações sobreo formato do audio*/
	fwrite(wav, 1, 44, saidaWav);
	
	/*Começa escrever as amostras de audio*/
	fwrite(wav->Data, wav->BitsPerSample/8, wav->Subchunk2Size/(wav->BitsPerSample/8), saidaWav);
}

void infoWav(tipoWav* wav){
	printf("Riff tag        : \"");
	for (int i = 0; i < 4; ++i)
	{
		printf("%c",wav->ChunkID[i] );
	}
	printf("\"\n");

	printf("Riff size       : %d\n",wav->ChunkSize);

	printf("Wave tag        : \"");
	for (int i = 0; i < 4; ++i)
	{
		printf("%c",wav->Format[i] );
	}
	printf("\"\n");

	printf("Form tag        : \"");
	for (int i = 0; i < 4; ++i)
	{
		printf("%c",wav->Subchunk1ID[i] );
	}
	printf("\"\n");

	printf("Fmt_size        : %d\n",wav->Subchunk1Size );
	printf("Audio_format    : %d\n",wav->AudioFormat );
	printf("Num_channels    : %d\n",wav->NumChannels );
	printf("Sample_rate     : %d\n",wav->SampleRate );
	printf("Byte_rate       : %d\n",wav->ByteRate );
	printf("Block_align     : %d\n",wav->BlockAlign );
	printf("Bits_per_sample : %d\n",wav->BitsPerSample );

	printf("Data tag        : \"");
	for (int i = 0; i < 4; ++i)
	{
		printf("%c",wav->Subchunk2ID[i] );
	}
	printf("\"\n");

	printf("Data size       : %d\n",wav->Subchunk2Size );
	printf("Samples/Channel : %d\n",(wav->Subchunk2Size*8)/ (wav->BitsPerSample * wav->NumChannels));
}

void inverteWav(tipoWav* wav, FILE *entradaWav,FILE *saidaWav){
	int16_t* amostra;
	amostra = malloc (wav->BitsPerSample); //aloca espaço no tamanho de uma amostra

	/*escreve o cabeçalho no arquivo de saida*/
	fwrite(wav, 1, 44, saidaWav);

	fseek (entradaWav, -1*(wav->BitsPerSample), SEEK_END) ; // aponta o equivalente ao tamanho de uma amostra antes do final do arquivo do arquivo de entrada 

	while(ftell(entradaWav)>43){ //enquanto não chega ao cabeçalho (no bit 43) do arquivo de entrada, coleta amostras
		fseek (entradaWav, -2*(wav->BitsPerSample), SEEK_CUR) ; // seta o apontador para duas amostras atras
		fread(amostra,wav->BitsPerSample,1,entradaWav); //coleta amostra de audio
		fwrite(amostra,wav->BitsPerSample,1,saidaWav); //escreve amostra de audio no arquivo de saida
	}
}

void setVolume(tipoWav* wav, FILE *entradaWav,FILE *saidaWav){
	float volume=1;
	int16_t* amostra;
	amostra = malloc (wav->BitsPerSample); //aloca espaço no tamanho de uma amostra
	printf("Digite o volume(min: 0 max: 10): \n");
	scanf("%f",&volume);
	while((volume<0)||(volume>10)){
		printf("Valor não aceito.\n");
		printf("Digite o volume(min: 0 max: 10): \n");
		scanf("%f",&volume);
	}

	/*escreve o cabeçalho no arquivo de saida*/
	fwrite(wav, 1, 44, saidaWav);


	/*aqui ta somando "volume" vezes, ao invéz de multiplicar pelo volume*/
	int i=0;
	int16_t* antigo;
	antigo = malloc (wav->BitsPerSample);
	while(!feof(entradaWav)){
		fread(amostra,wav->BitsPerSample,1,entradaWav); //coleta amostra de audio
		*antigo = *amostra;
		while(i < volume){
			*amostra = *amostra + *antigo;
			i++;
		}
		i=0;
		fwrite(amostra,wav->BitsPerSample,1,saidaWav); //escreve amostra de audio no arquivo de saida
	}



}

void ajustVolume(tipoWav* wav, FILE *entradaWav,FILE *saidaWav){
	int16_t *amostra,maior,menor;
	amostra = malloc (wav->BitsPerSample); //aloca espaço no tamanho de uma amostra
	
	/*escreve o cabeçalho no arquivo de saida*/
	fwrite(wav, 1, 44, saidaWav);
	fwrite(&wav->ChunkSize, 4, 1, saidaWav);
	fwrite(wav->Format, 4, 1, saidaWav);
	fwrite(wav->Subchunk1ID, 4, 1, saidaWav);
	fwrite(&wav->Subchunk1Size, 4, 1, saidaWav);
	fwrite(&wav->AudioFormat, 2, 1, saidaWav);
	fwrite(&wav->NumChannels, 2, 1, saidaWav);
	fwrite(&wav->SampleRate, 4, 1, saidaWav);
	fwrite(&wav->ByteRate, 4, 1, saidaWav);
	fwrite(&wav->BlockAlign, 2, 1, saidaWav);
	fwrite(&wav->BitsPerSample, 2, 1, saidaWav);
	fwrite(wav->Subchunk2ID, 4, 1, saidaWav);
	fwrite(&wav->Subchunk2Size, 4, 1, saidaWav);

	fread(amostra,wav->BitsPerSample,1,entradaWav); //coleta amostra de audio
	menor=*amostra;
	maior=*amostra;

	while(!feof(entradaWav)){
		fread(amostra,wav->BitsPerSample,1,entradaWav); //coleta amostra de audio
		if(*amostra>PICOMAX){
			printf("amostra: %d\n",*amostra );
		}
		if (*amostra>maior)
		{
			maior=*amostra;
		}
		if (*amostra<menor)
		{
			menor=*amostra;
		}
	}
	printf("amostra: %d\n",*amostra );
	printf("maior: %d\n",maior );
	printf("menor: %d\n",menor );
	// maior=(((float)maior / PICOMAX)*100);
	// menor=(((float)menor / PICOMIN)*100);
	// printf("maior: %d\n",maior );
	// printf("menor: %d\n",menor );

	fseek(entradaWav,44,SEEK_SET);
	fread(amostra,wav->BitsPerSample,1,entradaWav); //coleta amostra de audio
	while(!feof(entradaWav)){
		if ((*amostra>0)&&(maior>PICOMAX))
		{
			*amostra=*amostra * -1*((((float)maior/PICOMAX)*100)-100);
		}

		if ((*amostra<0)&&(menor<PICOMIN))
		{
			*amostra=*amostra * ((((float)maior/PICOMAX)*100)-100);
		}


		fwrite(amostra,wav->BitsPerSample,1,saidaWav); //escreve amostra de audio no arquivo de saida
		fread(amostra,wav->BitsPerSample,1,entradaWav); //coleta amostra de audio
	}
}

int main(){

	FILE *entradaWav = fopen("adele.wav", "r");
	if(!entradaWav) {
		perror("Erro ao abrir arquivo de entrada");
		exit(1);
	}

	FILE *saidaWav = fopen("saida.wav", "w+");
	if(!saidaWav){
		perror("Erro ao criar arquivo de saída");
		exit(1);
	}

	tipoWav wav;
	lerWav(entradaWav, &wav);

	// infoWav(&wav);
	// escreverWav( &wav, saidaWav);
	// inverteWav( &wav, entradaWav,saidaWav);
	setVolume( &wav, entradaWav,saidaWav);
	// ajustVolume( &wav, entradaWav,saidaWav);

	int fcloseall (void);
}
