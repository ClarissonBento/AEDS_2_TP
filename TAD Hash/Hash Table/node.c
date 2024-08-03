#include "node.h"
#include <stdio.h>
#include <stdlib.h>

//Cria um novo nó
//colocar tratamento de erros se necessário
Node *createNode(char *word, int id_doc) {

    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("\nFalhou, erro no node.h\n");
        return NULL;
    }

    strcpy(new_node->ingredient_name, word);
    new_node->next = NULL;
    new_node->i_list = initialize_indexList();
    insert_indexNode(new_node->i_list, id_doc);

    return new_node;
}

// Verificar esse calculo de hash code depois
int hashcode(char *word, int *weights, int M) {
    int hashcode = 0;
    int key_size = strlen(word);

    for (int i = 0; i < key_size; i++) {
        hashcode += (unsigned int)word[i] * weights[i]; // unsigned int pra garantir que não tenha num negativo
    }

    hashcode = hashcode % M;

    return hashcode;
}

// Função pra calcular o M segundo o Singed(?)
int choosin_M(int num) {

    int twoPow = 0;

    while (pow(2, twoPow) < num) twoPow++;
    
    return (int) pow(2, twoPow);
}