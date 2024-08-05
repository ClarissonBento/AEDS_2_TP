#include "./TAD Hash/Hash Table/HASH.h"
#include "./TAD Hash/Hash Table/linked.h"
#include "./TAD Hash/Hash Table/node.h"
#include "./TAD Hash/Inverted Index/i_Index.h"
#include "./TAD Hash/Inverted Index/i_Node.h"

#include <stdio.h>
#include <string.h>
/*
void hash_initialize(Hash_Table *table, int M);

int main(){
    Hash_Table *table;
    int N = 10; // numero de chaves (ou ingredientes)
    char palavra[50];
    int pesos[50]; // vetor de pesos

    int M; // o valor primo ideal
    M = choose_M(N);

    hash_initialize(table, M);
    is_hashtable_empty(table);

    printf("Tabela está vazia? ");
    if (is_hashtable_empty(table) == 1) printf("Sim\n");
    else printf("Não\n");

    int tam_palavra; // tamanho da palavra

    strcpy(palavra, "romanov");
    tam_palavra = strlen(palavra);
    gera_pesos(pesos, tam_palavra);
    insert_in_hashtable(table, palavra, 1, pesos, M);

    printf("Tabela está vazia? ");
    if (is_hashtable_empty(table) == 1) printf("Sim\n");
    else printf("Não\n");

    return 0; 
}
*/