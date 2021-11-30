#include <stdlib.h>
#include<stdint.h>
#include <stdio.h>
//#include "bufferEntrada.h"
#include<limits.h>
#define LIMIT 100

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

void create(char *archive){
    ITEM_VENDA receiver,auxArray[LIMIT];
    int archiveNumber = 0, numberOfBuffer = 0,i = 0,readed;
    ITEM_VENDA *toSave = malloc(100 * sizeof(ITEM_VENDA));// Lembrar que se guardar mais coisa aqui do que ele aguenta vai dar pau
    char *nameDefiner[30]; // O pica ta

    FILE *archiveToRead = fopen(archive,"r");
    if(archiveToRead == NULL){
        fprintf(stderr,"\nErro ao abrir arquivo\n");
    }

    while (i != 10){
        readed = fread(&toSave[numberOfBuffer],sizeof(ITEM_VENDA),1,archiveToRead);
        numberOfBuffer++;
        if(numberOfBuffer == 10){
            archiveNumber++;
            sprintf(nameDefiner,"Temp%d.txt",archiveNumber);
            for(int i=0; i<10; i++){
                printf("%d\n", toSave[i].id);
            }
            merge_sort(toSave,0,9);
            for(int i=0; i<10; i++){
                printf("depois %d\n", toSave[i].id);
            }
            s_archive(nameDefiner,&toSave,LIMIT);
            numberOfBuffer = 0;
        }
        //printf("Testezinho = %d\n",toSave[i].id);
        i++;
    }
    fclose(archiveToRead);
}

void merge_sort(ITEM_VENDA *array, int e, int d){
    int media;
    if(e<d){
        media = (e+d)/2;
        merge_sort(array,e,media);
        merge_sort(array,media+1,d);
        merge(array,e,media,d);
        
    }
}

void merge(ITEM_VENDA *array, int first, int final, int secondFinal){
    ITEM_VENDA *tempE, *tempD;
    int i,j,k;
    int qtdElemFirst = final - first + 1;
    int qtdElemFinal = secondFinal - final;

    tempE = malloc(sizeof(ITEM_VENDA) * (qtdElemFirst+1));
    tempD = malloc(sizeof(ITEM_VENDA) * (qtdElemFinal+1));
    //printf("Testezinho2 = %d\n",array[10].id);
    for(i = 0; i < 3;i++){
        //printf("i = %d ,array[first+i].id = %d\n",i,array[first+i].id);
        tempE[i]->id = array[first+i]->id;
        tempE[i]->id_venda = array[first+i]->id_venda;
        tempE[i]->data = array[first+i]->data;
        tempE[i]->desconto = array[first+i]->desconto;
        tempE[i]->obs[1008] = array[first+i]->obs[1008];
    }
    tempE[qtdElemFirst].id = INT_MAX;

    for(j = 0; j < qtdElemFinal;j++){
        tempD[i]->id = array[final+1+j]->id;
        tempD[i]->id_venda = array[final+1+j]->id_venda;
        tempD[i]->data = array[final+1+j]->data;
        tempD[i]->desconto = array[final+1+j]->desconto;
        tempD[i]->obs[1008] = array[final+1+j]->obs[1008];
    }
    tempD[qtdElemFinal].id =  INT_MAX;

    i = 0;
    j = 0;

    for (k = first; k <= final; k++){
        if(tempE[i].id <= tempD[j].id){
            array[k].id = tempE[i].id;
            array[k].id_venda = tempE[i].id_venda;
            array[k].data = tempE[i].data;
            array[k].desconto = tempE[i].desconto;
            array[k].obs[1008] = tempE[i].obs[1008];
            i++;
        } 
        else{
            array[k] = tempD[j];
            array[k].id_venda = tempD[j].id_venda;
            array[k].data = tempD[j].data;
            array[k].desconto = tempD[j].desconto;
            array[k].obs[1008] = tempD[j].obs[1008];
            j++;
        }
    }
    


    // free(tempE->id);
    // free(tempE->id_venda);
    // free(tempE->data);

    //free(tempE->obs);
    //free(tempE);

    printf("1\n");
    if(tempD){
        printf("2\n");
        for(int w=0; w<=final; w++){
            printf("antes1 %d\n", w);
            free(&tempD[w]);
            printf("depois1 %d\n", final);

        }
        printf("3\n");
    }



    if(tempE){
        printf("2\n");
        for(int w=0; w<=final; w++){
            printf("antes2 %d\n", w);
            free(&tempE[w]);
            printf("depois2\n %d\n", w);
        }
        printf("3\n");
    }
}
int main(){
    ITEM_VENDA tester[301];
    create("teste.dat");

    // for(int i = 0; i < 100; i++){
    //     int readed = fread(&tester[i],sizeof(ITEM_VENDA),1,"Temp1.txt");
    //     printf("tester[i].id = %d\n",i,tester[i].id);
    // }
}