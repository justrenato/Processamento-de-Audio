#include <stdio.h>
#include <stdlib.h>

typedef struct tipoWav{
	char ChunkID[4];
	int ChunkSize;
	char Format[4];
	char Subchunk1ID[4];
	int Subchunk1Size;
	short AudioFormat;
	short NumChannels;
	int SampleRate;
	int ByteRate;
	short BlockAlign;
	short BitsPerSample;
	char Subchunk2ID[4];
	int Subchunk2Size;
	short *Data;
}tipoWav;

void lerWav(FILE *entradaWav, tipoWav* wav){
	/*Le o cabeçalho e informações sobreo formato do audio*/
	fread(wav->ChunkID, 4, 1, entradaWav);
	fread(&wav->ChunkSize, 4, 1, entradaWav);
	fread(wav->Format, 4, 1, entradaWav);
	fread(wav->Subchunk1ID, 4, 1, entradaWav);
	fread(&wav->Subchunk1Size, 4, 1, entradaWav);
	fread(&wav->AudioFormat, 2, 1, entradaWav);
	fread(&wav->NumChannels, 2, 1, entradaWav);
	fread(&wav->SampleRate, 4, 1, entradaWav);
	fread(&wav->ByteRate, 4, 1, entradaWav);
	fread(&wav->BlockAlign, 2, 1, entradaWav);
	fread(&wav->BitsPerSample, 2, 1, entradaWav);
	fread(wav->Subchunk2ID, 4, 1, entradaWav);
	fread(&wav->Subchunk2Size, 4, 1, entradaWav);

  	/*Aloca espaço em wav->Data do tamanho do espaço ocupado pelas amostras de audio (indicado em wav->Subchuk2Size)*/
	wav->Data = (short*) malloc(sizeof(short)*(wav->Subchunk2Size)*(wav->BitsPerSample/8));

	/*Começa ler as amostras de audio*/
	fread(wav->Data, wav->BitsPerSample/8, wav->Subchunk2Size/(wav->BitsPerSample/8), entradaWav);
	rewind(entradaWav);
}

void escreverWav(tipoWav* wav, FILE *saidaWav ){
	/*Escreve o cabeçalho e informações sobreo formato do audio*/
	fwrite(wav->ChunkID, 1, 4, saidaWav);
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

	/*Começa escrever as amostras de audio*/
	fwrite(wav->Data, wav->BitsPerSample/8, wav->Subchunk2Size/(wav->BitsPerSample/8), saidaWav);
	rewind(saidaWav);
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
	int* amostra;
	amostra = malloc (wav->BitsPerSample); //aloca espaço no tamanho de uma amostra

	/*escreve o cabeçalho no arquivo de saida*/
	fwrite(wav->ChunkID, 1, 4, saidaWav);
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

	fseek (entradaWav, -1*(wav->BitsPerSample), SEEK_END) ; // aponta o equivalente ao tamanho de uma amostra antes do final do arquivo do arquivo de entrada 

	while(ftell(entradaWav)>43){ //enquanto não chega ao cabeçalho (no bit 43) do arquivo de entrada, coleta amostras
		fseek (entradaWav, -2*(wav->BitsPerSample), SEEK_CUR) ; // seta o apontador para duas amostras atras
		fread(amostra,wav->BitsPerSample,1,entradaWav); //coleta amostra de audio
		fwrite(amostra,wav->BitsPerSample,1,saidaWav); //escreve amostra de audio no arquivo de saida
	}
	rewind(entradaWav);
	rewind(saidaWav);
}

void volume(tipoWav* wav, FILE *entradaWav,FILE *saidaWav){
	float volume=1;
	int* amostra;
	amostra = malloc (wav->BitsPerSample); //aloca espaço no tamanho de uma amostra
	printf("ponteiro entrada: %ld\n",ftell(entradaWav) );
	printf("ponteiro saida: %ld\n",ftell(saidaWav) );
	printf("Digite o volume(min: 0 max: 10): \n");
	scanf("%f",&volume);
	while((volume<0)||(volume>10)){
		printf("Valor não aceito.\n");
		printf("Digite o volume(min: 0 max: 10): \n");
		scanf("%f",&volume);
	}
	/*escreve o cabeçalho no arquivo de saida*/
	fwrite(wav->ChunkID, 1, 4, saidaWav);
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

	while(!feof(entradaWav)){
		fread(amostra,wav->BitsPerSample,1,entradaWav); //coleta amostra de audio
		*amostra=*amostra*volume;
		fwrite(amostra,wav->BitsPerSample,1,saidaWav); //escreve amostra de audio no arquivo de saida
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
	volume( &wav, entradaWav,saidaWav);

	int fcloseall (void);
}
