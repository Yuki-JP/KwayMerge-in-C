#include "stdio.h"
#include "stdint.h"
#include "bufferEntrada.h"
typedef struct ARCHIVECONTROL{
    FILE *archive;
    int position;
    int size;
    ITEM_VENDA *buffer;
}ARCHIVECONTROL;

void merge(char *archiveName, int qttArch, int size);
void dataReceive(ARCHIVECONTROL *control, int size);