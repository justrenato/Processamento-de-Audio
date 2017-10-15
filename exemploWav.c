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

tipoWav lerWav(FILE *entradaWav, tipoWav wav){
	/*Le o cabeçalho e informações sobreo formato do audio*/
	fread(wav.ChunkID, 4, 1, entradaWav);
	fread(&wav.ChunkSize, 4, 1, entradaWav);
	fread(wav.Format, 4, 1, entradaWav);
	fread(wav.Subchunk1ID, 4, 1, entradaWav);
	fread(&wav.Subchunk1Size, 4, 1, entradaWav);
	fread(&wav.AudioFormat, 2, 1, entradaWav);
	fread(&wav.NumChannels, 2, 1, entradaWav);
	fread(&wav.SampleRate, 4, 1, entradaWav);
	fread(&wav.ByteRate, 4, 1, entradaWav);
	fread(&wav.BlockAlign, 2, 1, entradaWav);
	fread(&wav.BitsPerSample, 2, 1, entradaWav);
	fread(wav.Subchunk2ID, 4, 1, entradaWav);
	fread(&wav.Subchunk2Size, 4, 1, entradaWav);

  	/*Aloca espaço em wav.Data do tamanho do espaço ocupado pelas amostras de audio (indicado em wav.Subchuk2Size)*/
	wav.Data =  malloc(wav.Subchunk2Size);

	/*Começa ler as amostras de audio*/
	fread(wav.Data, wav.BitsPerSample, (wav.Subchunk2Size*8)/wav.BitsPerSample, entradaWav);
	fclose(entradaWav);
	return wav;
}

tipoWav escreverWav(FILE *saidaWav, tipoWav wav){
	/*Escreve o cabeçalho e informações sobreo formato do audio*/
	fwrite(wav.ChunkID, 4, 1, saidaWav);
	fwrite(&wav.ChunkSize, 4, 1, saidaWav);
	fwrite(wav.Format, 4, 1, saidaWav);
	fwrite(wav.Subchunk1ID, 4, 1, saidaWav);
	fwrite(&wav.Subchunk1Size, 4, 1, saidaWav);
	fwrite(&wav.AudioFormat, 2, 1, saidaWav);
	fwrite(&wav.NumChannels, 2, 1, saidaWav);
	fwrite(&wav.SampleRate, 4, 1, saidaWav);
	fwrite(&wav.ByteRate, 4, 1, saidaWav);
	fwrite(&wav.BlockAlign, 2, 1, saidaWav);
	fwrite(&wav.BitsPerSample, 2, 1, saidaWav);
	fwrite(wav.Subchunk2ID, 4, 1, saidaWav);
	fwrite(&wav.Subchunk2Size, 4, 1, saidaWav);

	/*Começa escrever as amostras de audio*/
	fwrite(wav.Data, wav.BitsPerSample, (wav.Subchunk2Size*8)/wav.BitsPerSample, saidaWav);
	fclose(saidaWav);
	return wav;
}

int main(){

	FILE *entradaWav = fopen("adele.wav", "r");
	if(!entradaWav) {
		perror("Erro ao abrir arquivo de entrada");
		exit(1);
	}

	FILE *saidaWav = fopen("saida.wav", "w");
	if(!saidaWav){
		perror("Erro ao criar arquivo de saída");
		exit(1);
	}

	tipoWav wav;
	wav = lerWav(entradaWav, wav);
	escreverWav(saidaWav, wav);

	printf("\n");
}
