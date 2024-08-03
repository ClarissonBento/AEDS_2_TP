#include "node.h"

//Cria um novo nó
//colocar tratamento de erros se necessário
Node* CreateNode(ingredient ing_name) {
    Node *new_node = (Node*) malloc(sizeof(Node));
    new_node->ingredient = ing_name;
    new_node->next = NULL;

    return new_node;
}

// Verificar esse calculo de hash code depois
int Hash_Code(char *word, int *weights, int M) {
    int hashcode = 0;
    int key_size = strlen(word);

    for (int i = 0; i < key_size; i++) {
        hashcode += (unsigned int)word[i] * weights[i]; // unsigned int pra garantir que não tenha num negativo
    }

    hashcode = hashcode % M;

    return hashcode;
}

// Função pra calcular o M segundo o Singed(?)
int Choosin_M(int num) {

    int twoPow = 0;

    while (pow(2, twoPow) < num) twoPow++;
    
    return (int) pow(2, twoPow);
}