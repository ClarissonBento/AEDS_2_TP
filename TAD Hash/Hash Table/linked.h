#ifndef LINKED_H
#define LINKED_H

#include "node.h"

typedef struct {
    Node *head, *tail;
} Linked_List;

// Cabeçalho de funções
Linked_List *initialise_LinkedList();
void list_append(Linked_List *list, char *word, int doc_id);
int is_emptyList(Linked_List *list);
void display_list(Linked_List *list, int N);
int count_list(Linked_List list);
void MakeEmpty_List(Linked_List *list);

#endif