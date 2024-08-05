#ifndef I_INDEX_H
#define I_INDEX_H

#include "i_Node.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    index_Node *head;
    index_Node *tail;

} index_List; // Lista encadeada dos pares do indice invertido

// Cabeçalho de funções
int insert_indexNode(index_List *list, int documentID);
index_Node *search_indexNode(index_List *list, int documentID);
index_List *initialize_indexList();
int is_index_empty(index_List *list);
void print_indexList(index_List *list);
int size_indexList(index_List *list);

#endif