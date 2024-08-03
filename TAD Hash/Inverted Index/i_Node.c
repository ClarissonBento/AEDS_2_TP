#include "i_Node.h"
#include <stdio.h>
#include <stdlib.h>

index_Node *initialize_indexNode(int documentID) {

    index_Node *i_node = (index_Node*)malloc(sizeof(index_Node));

    if (i_node == NULL) {
        printf("\nErro no node do indice invertido da tabela hash\n");
        return NULL;
    }

    i_node->ID_Document = documentID;
    i_node->Occurrences = 1;
    i_node->next = NULL;

    return i_node;
}