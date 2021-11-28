#include<stdio.h>
#include<stdlib.h>
#include "bufferEntrada.h"

int memoryLimit = 100;

void create(char *archive){
    ITEM_VENDA receiver,auxArray[memoryLimit];
    int counter, total;
    char toSave[20];

    FILE *a = fopen(archive,"r");
    if(a == NULL){
        fprintf(stderr,"\nErro ao abrir arquivo\n");
    }

    while(fread(&receiver,sizeof(ITEM_VENDA),1,a))
        printf("\nid = %d\n",receiver.id);

    fclose(a);

}