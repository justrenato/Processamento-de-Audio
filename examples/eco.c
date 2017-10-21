#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "dados.h"
#include "header.h"

void eco(FILE *music_in, header* wave, FILE *music_out){
	long int novoTam;
	read_wav(music_in, wave);

	int16_t *aux;
	aux = malloc(wave-> bits_sample);

	fwrite(wave, 44, 1, music_out);	
	novoTam = (wave->subchunk2_size * 2);//delay
	for (int i = 0; i < wave-> sample_rate - novoTam; i++){
		fread(aux, wave->bits_sample, 1, music_in);
		
		aux[i + novoTam] = aux[i+novoTam] + aux[i] * 0.3;

		fwrite(aux, wave->bits_sample, 2, music_out);
	}
}