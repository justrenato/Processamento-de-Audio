#include "filtros.h"

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
