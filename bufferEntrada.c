#include<stdio.h>
#include<stdlib.h>
#include "bufferEntrada.h"

#define LIMIT 100

void create(char *archive){
    ITEM_VENDA receiver,auxArray[LIMIT];
    int archiveNumber = 0, numberOfBuffer = 0;
    char toSave[LIMIT];

    FILE *a = fopen(archive,"r");
    if(a == NULL){
        fprintf(stderr,"\nErro ao abrir arquivo\n");
    }

    while (fread(&receiver,sizeof(ITEM_VENDA),1,a)){
        fscanf(a,"%d",&toSave[numberOfBuffer]);
        numberOfBuffer++;
        printf("Number of buffer = %d\n",numberOfBuffer);
        if(numberOfBuffer == 100){
            archiveNumber++;
            printf("Archive number = %d\n",archiveNumber);

            sprintf(toSave,"Temp%d.txt",archiveNumber);

            numberOfBuffer = 0;
        }
    }   
    fclose(a);
}

void merge_sort(ITEM_VENDA *array, int e, int d){
    int media;
    if(e<d){
        media = (e+d)/2;
        merge_sort(array,e,media);
        merge_sort(array,media+1,d);
         
    }
}

void merge(ITEM_VENDA *array, int first, int final, int secondFinal){
    ITEM_VENDA *tempE, *tempD;
    int i,j,k;
    int qtdElemFirst = final - first + 1;
    int qtdElemFinal = secondFinal - final;

    tempE = malloc(sizeof(ITEM_VENDA) * (qtdElemFirst+1));
    tempD = malloc(sizeof(ITEM_VENDA) * (qtdElemFinal+1));

    for(i = 0; i < qtdElemFirst;i++){
        tempE[i].id = array[first+i].id;
        tempE[i].id_venda = array[first+i].id_venda;
        tempE[i].data = array[first+i].data;
        tempE[i].desconto = array[first+i].desconto;
        tempE[i].obs[1008] = array[first+i].obs;


    }



}
