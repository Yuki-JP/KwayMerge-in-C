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

typedef struct ARCHIVECONTROL{
    FILE *archive;
    int position;
    int size;
    ITEM_VENDA *buffer;
}ARCHIVECONTROL;

////////////////////////////buffer Saída abaixo/////////////////////
void merge(char *archiveName, int qttArch, int size){
    ARCHIVECONTROL *auxStruct;
    char nameDefiner[30];
    int *buffer = (int*) malloc(size*sizeof(int));
    int size = LIMIT / (qttArch+1);
    int small = 0;
    int qttBuffer = 0;

    auxStruct = (ARCHIVECONTROL*)malloc(qttArch*sizeof(ARCHIVECONTROL));

    for(int i = 0; i < qttArch; i++){
        sprintf(nameDefiner,"temp%d.txt",i+1); // Definindo nome pra leitura
        auxStruct[i].archive = fopen(nameDefiner,"r");
        auxStruct[i].size = 0;
        auxStruct[i].position = 0;
        auxStruct[i].buffer = (ARCHIVECONTROL*)malloc(size*sizeof(ARCHIVECONTROL));
        dataReceive(auxStruct,size);
    }

    while(searchSmaller(archiveName, qttArch, size, &small) == 1){
        buffer[qttBuffer] = small;
        qttBuffer++;

        if(qttBuffer == size){

        }
    }
    

}

int searchSmaller(ARCHIVECONTROL* archive, int qttArchive, int K, int* small){
    int found = -1;

    for(int i=0; i<qttArchive; i++){
        if(archive[i].position < archive[i].size){
            if(found == -1)
                found = i;
            else{
                if(archive[i].buffer[archive[i].position] < archive[found].buffer[archive[found].position])
                    found = i;
            }
        }
    }

    if(found != -1){
        *small = archive[found].buffer[archive[found].position];
        archive[found].position++;
        if(archive[found].position == archive[found].size)
            dataReceive(&archive[found], K);
        return 1;
    
    }else
        return 0;
}

void dataReceive(ARCHIVECONTROL *control, int size){
    int counter;

    if(control->archive == NULL)
        return;

    control->position = 0;
    control->size = 0;
    printf("\nENtei no data Receivw\n");
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

////////////////////////////buffer Entrada abaixo////////////////////////
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

void create(char *archive){
    ITEM_VENDA receiver,auxArray[LIMIT];
    int archiveNumber = 0, numberOfBuffer = 0,i = 0,readed,counter = 0;
    ITEM_VENDA toSave[LIMIT];// Lembrar que se guardar mais coisa aqui do que ele aguenta vai dar pau
    char *nameDefiner[30]; // O pica ta
    uint32_t arrayToquick[LIMIT];

    FILE *archiveToRead = fopen(archive,"r");
    if(archiveToRead == NULL){
        fprintf(stderr,"\nErro ao abrir arquivo\n");
    }

    while (i != 10){
        readed = fread(&toSave[numberOfBuffer],sizeof(ITEM_VENDA),1,archiveToRead);
        counter++;
        numberOfBuffer++;
        if(numberOfBuffer == 10){
            archiveNumber++;
            sprintf(nameDefiner,"testeTemp%d.txt",archiveNumber);
            for(int y = 0; y < LIMIT;y++){
                arrayToquick[y] = toSave[y].id;
            }
            quickSort(arrayToquick,0,LIMIT - 1,toSave);
            s_archive(nameDefiner,&toSave,LIMIT);
            numberOfBuffer = 0;
        }
        i++;
    }
    if(numberOfBuffer > 0){ //caso sobre alguma struct
        archiveNumber++;
        sprintf(nameDefiner,"testeTemp%d.txt",archiveNumber);

        for(int y = 0; y < numberOfBuffer;y++){
            arrayToquick[y] = toSave[y].id;
        }

        quickSort(arrayToquick,0,LIMIT - 1,toSave);
        s_archive(nameDefiner,&toSave,LIMIT);
        numberOfBuffer = 0;
    }
    int size = LIMIT / (counter+1);
    merge(archive,counter,size);
    //fclose(archiveToRead);

}




int main(){
    ITEM_VENDA tester[301];
    ITEM_VENDA *toSave = malloc(LIMIT * sizeof(ITEM_VENDA));// Lembrar que se guardar mais coisa aqui do que ele aguenta vai dar pau
    int numberOfBuffer = 0;
    FILE *archiveToRead = fopen("testeTemp1.txt","r");
    create("teste.dat");


}

//aaa