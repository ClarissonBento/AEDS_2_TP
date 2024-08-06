#ifndef NODE_H
#define NODE_H

#define MAX_ING 36 // numero de ingredientes

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "../Inverted_Index/i_Node.c"
#include "../Inverted_Index/i_Index.c"

typedef struct Node {
    char ingredient_name[50];
    //ingredient ingredient;
    struct Node *next;
    index_List *i_list;
} Node;

// Cabeçalho de funções
Node *createNode(char *word, int id_doc);
int hash(char *word, int *weights, int M);
int choose_M(int num);
int is_prime(int n);

#endif