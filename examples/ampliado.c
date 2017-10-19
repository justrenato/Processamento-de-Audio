#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "dados.h"
#include "header.h"

void e_ampliado(FILE *music_in, header* wave, FILE *music_out){
	int16_t *aux;
	int16_t *aux1;
	int16_t *aux2;
	int16_t *aux11;
	int16_t *aux22;

	int diff;

	read_wav(music_in, wave);
	fwrite(wave, 44, 1, music_out);	
	aux1 = malloc(wave->bits_sample/2*wave->subchunk2_size/wave->bits_sample);
	aux2 = malloc(wave->bits_sample/2*wave->subchunk2_size/wave->bits_sample);

	int k = 6;
	while(!feof(music_in)){
		if (k % 2 == 0){
			fread(aux,wave-> bits_sample/2,1,music_in);	
			aux1= (int16_t)*aux;
		}
		else{
			fread(aux,wave->bits_sample/2,1,music_in);	
			aux2= (int16_t)*aux;

		}
	}

	fseek(music_in, 44, SEEK_SET);
	int i= 0;
	while(!feof(music_in)){
		diff = aux1[i] - aux2[i];
		aux11 = aux1[i] + 5*diff;
		aux22 = aux2[i] - 5*diff;
		fwrite(aux11, wave->bits_sample/2,1, music_out);
		fwrite(aux22, wave->bits_sample/2,1, music_out);
		i++;
	}
}