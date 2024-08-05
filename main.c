#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./TAD Hash/Hash Table/HASH.h"
#include "./TAD Hash/Hash Table/linked.h"
#include "./TAD Hash/Hash Table/node.h"
#include "./TAD Hash/Inverted Index/i_Index.h"
#include "./TAD Hash/Inverted Index/i_Node.h"

//#define MAX_ING 50

int main() {
    int M = choose_M(10);  // Escolhendo o tamanho da tabela hash
    printf("Valor de M (tamanho da tabela hash): %i\n", M);

    Hash_Table table;
    hash_initialize(&table, M);

    // Inserindo alguns elementos na tabela hash
    insert_in_hashtable(&table, "Tomate", 1, table.weights, M);
    insert_in_hashtable(&table, "HallsPreto", 2, table.weights, M);
    insert_in_hashtable(&table, "Pedro", 3, table.weights, M);
    insert_in_hashtable(&table, "Pedro", 4, table.weights, M); // Tentativa de inserir um item duplicado

    // Buscando elementos na tabela hash
    Node *result = search_in_hashtable("Tomate", table.weights, &table, M);
    if (result != NULL) {
        printf("Encontrado: %s, Documento ID: %i\n", result->ingredient_name, result->i_list->head->ID_Document);
    } else {
        printf("Tomate não encontrado.\n");
    }

    result = search_in_hashtable("HallsPreto", table.weights, &table, M);
    if (result != NULL) {
        printf("Encontrado: %s, Documento ID: %i\n", result->ingredient_name, result->i_list->head->ID_Document);
    } else {
        printf("HallsPreto não encontrado.\n");
    }

    // Imprimindo a tabela hash
    print_hashTable(&table, M);

    return 0;
}