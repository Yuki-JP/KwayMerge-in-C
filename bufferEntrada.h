#include "stdio.h"
#include "stdint.h"


typedef struct ITEM_VENDA{
uint32_t id;
uint32_t id_venda;
uint32_t data;
float desconto;
char obs[1008];
}ITEM_VENDA;

void create(char *archive);
void merge_sort(ITEM_VENDA *array, int e, int d);