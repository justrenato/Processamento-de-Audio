#include "filtros.h"

void lerWav(FILE *entradaWav, tipoWav* wav){
	/*Le o cabeçalho e informações sobreo formato do audio*/

	fread(wav, 44, 1, entradaWav);

  	/*Aloca espaço em wav->Data do tamanho do espaço ocupado pelas amostras de audio (indicado em wav->Subchuk2Size)*/
	wav->Data = malloc(wav->Subchunk2Size);

	/*Começa ler as amostras de audio*/
	fread(wav->Data, wav->Subchunk2Size,1, entradaWav);
	rewind(entradaWav);
}