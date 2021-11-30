#include <stdlib.h>
#include<stdint.h>
#include <stdio.h>
//#include "bufferEntrada.h"
#include<limits.h>
#define LIMIT 10
#include<string.h>

typedef struct ITEM_VENDA{
uint32_t id;
uint32_t id_venda;
uint32_t data;
float desconto;
char obs[1008];
}ITEM_VENDA;

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

    item[small].id = item[big].id;
    item[small].id_venda = item[big].id_venda;
    item[small].data = item[big].data;
    item[small].desconto = item[big].desconto;
    strcpy(item[small].obs,item[big].obs);

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

void create(char *archive){
    ITEM_VENDA receiver,auxArray[LIMIT];
    int archiveNumber = 0, numberOfBuffer = 0,i = 0,readed;
    ITEM_VENDA toSave[LIMIT];// Lembrar que se guardar mais coisa aqui do que ele aguenta vai dar pau
    char *nameDefiner[30]; // O pica ta
    uint32_t arrayToquick[LIMIT];

    FILE *archiveToRead = fopen(archive,"r");
    if(archiveToRead == NULL){
        fprintf(stderr,"\nErro ao abrir arquivo\n");
    }

    while (i != 10){
        readed = fread(&toSave[numberOfBuffer],sizeof(ITEM_VENDA),1,archiveToRead);
        numberOfBuffer++;
        if(numberOfBuffer == 10){
            archiveNumber++;
            sprintf(nameDefiner,"testeTemp%d.txt",archiveNumber);

            for(int y = 0; y < LIMIT;y++){
                arrayToquick[y] = toSave[y].id;
            }


            quickSort(arrayToquick,0,LIMIT,toSave);
            s_archive(nameDefiner,&toSave,LIMIT);
            numberOfBuffer = 0;
        }
        //printf("Testezinho = %d\n",toSave[i].id);
        i++;
    }
    //fclose(archiveToRead);
}


int main(){
    ITEM_VENDA tester[301];
    ITEM_VENDA *toSave = malloc(LIMIT * sizeof(ITEM_VENDA));// Lembrar que se guardar mais coisa aqui do que ele aguenta vai dar pau
    int numberOfBuffer = 0;
    FILE *archiveToRead = fopen("testeTemp1.txt","r");
    create("teste.dat");

    // for(int h = 0; h < 10;h++){
    //     int readed = fread(&toSave[numberOfBuffer],sizeof(ITEM_VENDA),1,archiveToRead);
    //     printf("id = %d\n", toSave[h].id);
    // }
    // for(int i = 0; i < 100; i++){
    //     int readed = fread(&tester[i],sizeof(ITEM_VENDA),1,"Temp1.txt");
    //     printf("tester[i].id = %d\n",i,tester[i].id);
    // }
}