#include <stdio.h>
#include <stdlib.h>

#define N_potions = 15

typedef struct Slot {

    char ingrediente[30];
    struct Slot *next;
    
} Slot;

typedef struct {

    Slot *head;
    Slot *tail;

} Lista_Encadeada;

typedef struct Tabela_Hash {

    Lista_Encadeada **lista_linear;
    int *pesos;
    int tamanho_max;
    int numInsertions;

} Tabela_Hash;