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


// struct option longopts[] = {
//     {"wavinfo",    required_argument, 0, 'a'},
//     {"wavrev",     required_argument, 0, 'b'},
//     {"wavvol",     required_argument, 0, 'c'},
//     {"wavautovol", required_argument, 0, 'd'},
//     {"wavecho",    required_argument, 0, 'e'},
//     {"wavwide",    required_argument, 0, 'f'},
//     {"wavcat",     required_argument, 0, 'g'},
//     {"wavmix",     required_argument, 0, 'h'}
// };

void lerWav(FILE *entradaWav, tipoWav* wav);

void escreverWav(tipoWav* wav, FILE *saidaWav );

void infoWav(tipoWav* wav);

void reverteWav(tipoWav* wav, FILE *entradaWav,FILE *saidaWav);

void setVolume(tipoWav* wav, FILE *entradaWav,FILE *saidaWav,float vol);

void ajustVolume(tipoWav* wav, FILE *entradaWav,FILE *saidaWav);

#endif