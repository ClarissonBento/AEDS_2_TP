#ifndef NODE_H
#define NODE_H

#define MAX_ING 36 // numero de ingredientes

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "read.h"
#include "../Inverted Index/i_Node.h"
#include "../Inverted Index/i_Index.h"

typedef struct Node {
    char ingredient_name[50];
    //ingredient ingredient;
    struct Node *next;
    index_List *i_list;
} Node;

// Cabeçalho de funções
Node* createNode(char *word, int id_doc);
int hash(char *word, int *pesos, int M);
int choosin_M(int number);

#endif