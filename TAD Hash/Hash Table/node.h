#ifndef NODE_H
#define NODE_H

#define MAX_ING 20 // numero de ingredientes

#include <stdio.h>
#include <stdlib.h>
#include "read.h"
#include "i_Node.h"

typedef struct Node {  
    ingredient ingredient;
    struct Node *next;
    i_Node *par;

} Node;



//funções
Node* CreateNode(ingredient ing_name);
int Hash_Code(char *word, int *pesos, int M);
int Choosin_M(int number);

#endif