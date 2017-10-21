#ifndef __FILTROS__
#define __FILTROS__
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#define PICO 32767

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

void lerWav(FILE *entradaWav, tipoWav* wav);

void escreverWav(tipoWav* wav, FILE *saidaWav );

void infoWav(tipoWav* wav);

void reverteWav(tipoWav* wav, FILE *entradaWav,FILE *saidaWav);

void setVolume(tipoWav* wav, FILE *entradaWav,FILE *saidaWav,float vol);

void ajustVolume(tipoWav* wav, FILE *entradaWav,FILE *saidaWav);

// void controleComandos(int argc, char *argv[]);

void estAmp(tipoWav* wav, FILE *entradaWav,FILE *saidaWav,float vol);

void eco(tipoWav* wav, FILE *entradaWav,FILE *saidaWav,float delay, float aten);

#endif