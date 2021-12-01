#include "stdio.h"
#include "stdint.h"
#include "bufferSaida.h"
#define LIMIT 10

void merge(char *archiveName, int qttArch, int size){
    ARCHIVECONTROL *auxStruct;
    char nameDefiner[30];
    int *buffer = (int*) malloc(size*sizeof(int));
    int size = LIMIT / (qttArch+1);

    auxStruct = (ARCHIVECONTROL*)malloc(qttArch*sizeof(ARCHIVECONTROL));

    for(int i = 0; i < qttArch; i++){
        sprintf(nameDefiner,"temp%d.txt",i+1); // Definindo nome pra leitura
        auxStruct[i].archive = fopen(nameDefiner,"r");
        auxStruct[i].size = 0;
        auxStruct[i].position = 0;
        auxStruct[i].buffer = (ARCHIVECONTROL*)malloc(size*sizeof(ARCHIVECONTROL));
        dataReceive(auxStruct,size);
    }

}

void dataReceive(ARCHIVECONTROL *control, int size){
    int counter;

    if(control->archive == NULL)
        return;

    control->position = 0;
    control->size = 0;

    for(counter = 0; counter < size; counter++){
        if(fread(control->buffer,sizeof(ITEM_VENDA),1,control->archive)){
            fread(control->buffer,sizeof(ITEM_VENDA),1,control->archive);
            control->size++;
        }
        else{
            fclose(control->archive);
            control->archive = NULL;
            break;
        }
    }   
    
}
