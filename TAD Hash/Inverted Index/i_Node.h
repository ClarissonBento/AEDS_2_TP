#ifndef I_NODE_H
#define I_NODE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct index_Node {
    int Occurrences;
    int ID_Document;
    struct index_Node *next;

} index_Node;

index_Node *initialize_indexNode(int documentID);

#endif