#ifndef LINKED_H
#define LINKED_H

#include "node.h"

typedef struct {
    Node *head, *tail;
} Linked_List;

void MakeEmpty_List(Linked_List *list);
void List_Append(Linked_List *list, ingredient ing_name);
int Is_Empty(Linked_List list);
void Display_List(Linked_List list, int N_list);
int List_Count(Linked_List list);

#endif