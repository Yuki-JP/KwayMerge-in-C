#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include "bufferEntrada.h"

#define LIMIT 1

void s_archive(char *archive, ITEM_VENDA *array, int n_registros){
    int counter;
    FILE *newArchive = fopen(archive,"a");

    for(counter = 0; counter < n_registros; counter++){
        fwrite(array,sizeof(ITEM_VENDA),n_registros,newArchive);
    }
}

void switchPlaces(int *a, int small, int big,ITEM_VENDA item[]){  
    ITEM_VENDA receiver;


    int aux = a[big];
    a[big] =  a[small];
    a[small] = aux;

    receiver.id = item[big].id;
    receiver.id_venda = item[big].id_venda;
    receiver.data = item[big].data;
    receiver.desconto = item[big].desconto;
    strcpy(receiver.obs,item[big].obs);

    item[big].id = item[small].id;
    item[big].id_venda = item[small].id_venda;
    item[big].data = item[small].data;
    item[big].desconto = item[small].desconto;
    strcpy(item[big].obs,item[small].obs); 

    item[small].id = receiver.id;
    item[small].id_venda = receiver.id_venda;
    item[small].data = receiver.data;
    item[small].desconto = receiver.desconto;
    strcpy(item[small].obs,receiver.obs);
};

int partition(int *a, int first, int last, ITEM_VENDA item[]){
    int pivot;
    int yellowLine, purpleLine;

    pivot = a[last];
    yellowLine =  first-1;

    for (purpleLine = first; purpleLine < last; purpleLine++){
        if(a[purpleLine] <= pivot){
            yellowLine++;
            switchPlaces(a,yellowLine,purpleLine,item);
        }
    }
    switchPlaces(a,yellowLine+1,last,item);

    return yellowLine + 1;
}
void quickSort(int *array,int initial, int final, ITEM_VENDA item[]){
    int pointer;

    if( initial < final ) {
        pointer = partition(array,initial,final,item);
        quickSort(array,initial,pointer-1,item);
        quickSort(array,pointer+1,final,item);
    }
}

