#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "dados.h"
#include "header.h"

void volume_automatico(FILE *music_in, header* wave, FILE *	music_out){
	read_wav(music_in, wave);

	int16_t *aux;
	int16_t maior;
	float fator;
	aux = malloc(wave -> bits_sample/2);
	*aux = 0;
	fseek(music_in, 44, SEEK_SET);
	maior = *aux;
	while(!feof(music_in)){
		fread(aux, wave->bits_sample/2,1,music_in);
		if (*aux< 0)
			*aux = *aux*-1;	

		if (*aux > maior)
			maior = *aux;
		printf("%d\n",maior );

	}
	// printf("%d\n",maior );
	fator = 32767/maior;
	
	fwrite(wave, 44, 1, music_out);
	
	fseek(music_in, 44, SEEK_SET);

	while(!feof(music_in)){
		fread(aux, wave->bits_sample, 1, music_in);
		*aux = *aux*fator;
		fwrite(aux, wave->bits_sample,1, music_out);
	}

}