#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./TAD Hash/Hash Table/HASH.h"
#include "./TAD Hash/Hash Table/linked.h"
#include "./TAD Hash/Hash Table/node.h"
#include "./TAD Hash/Inverted Index/i_Index.h"
#include "./TAD Hash/Inverted Index/i_Node.h"

int main() {

    int col = 0;
    int com = 0;

    int M = choose_M(10);  // Escolhendo o tamanho da tabela hash
    printf("Valor de M (tamanho da tabela hash): %d\n", M);

    Hash_Table table;
    hash_initialize(&table, M);

    // Inserindo alguns elementos na tabela hash
    insert_in_hashtable(&table, "Pedro", 1, table.weights, M, &col);
    insert_in_hashtable(&table, "Ouro", 2, table.weights, M, &col);
    insert_in_hashtable(&table, "Teste", 3, table.weights, M, &col);
    insert_in_hashtable(&table, "Marte", 4, table.weights, M, &col); // Tentativa de inserir um item duplicado
    insert_in_hashtable(&table, "Marte", 4, table.weights, M, &col);
    insert_in_hashtable(&table, "Pedro", 3, table.weights, M, &col);
    insert_in_hashtable(&table, "Ouro", 3, table.weights, M, &col);
    insert_in_hashtable(&table, "Terra", 4, table.weights, M, &col);

    // Buscando elementos na tabela hash
    Node *result = search_in_hashtable("Marte", table.weights, &table, M, &com);
    if (result != NULL) {
        printf("Encontrado: %s, Documento ID: %d, Ocorrências: %d\n", 
               result->ingredient_name, 
               result->i_list->head->ID_Document,
               result->i_list->head->Occurrences);
    } else {
        printf("Busca falhou\n");
    }

    result = search_in_hashtable("Teste", table.weights, &table, M, &com);
    if (result != NULL) {
        printf("Encontrado: %s, Documento ID: %d, Ocorrências: %d\n", 
               result->ingredient_name, 
               result->i_list->head->ID_Document,
               result->i_list->head->Occurrences);
    } else {
        printf("Busca falhou 2\n");
    }

    // Imprimindo a tabela hash
    print_hashTable(&table, M);

    // Exibindo as contagens de colisões e comparações
    printf("\n\n");
    printf("Total de colisões: %i\n", col);
    printf("Total de comparações: %i\n", com);

    return 0;
}