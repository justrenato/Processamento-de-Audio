#include "filtros.h"


int main(int argc, char const *argv[])
{
	FILE *entradawav = fopen ("adele.wav","r");
	FILE *saidawav = fopen ("saida.wav","w+");
	tipoWav wave;
	int32_t sampleRate = 50000;
	fread(&wave,44,1,entradawav);
	fwrite(&wave,44,1,saidawav);
	fseek(saidawav,24,SEEK_SET); //coloca o ponteiro no bit 34 da saida
	fwrite(&sampleRate,2,1,saidawav); //le o BitsPerSample

	return 0;
}