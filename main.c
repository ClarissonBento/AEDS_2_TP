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

    search_and_print_hashtable("Marte", &table, M);

    // Imprimindo a tabela hash
    print_hashTable(&table, M);

    // Exibindo as contagens de colisões e comparações
    printf("\n\n");
    printf("Total de colisões: %i\n", col);
    printf("Total de comparações: %i\n", com);

    return 0;
}

// Função para buscar um item na tabela hash
Node *search_in_hashtable(char *item, int *weights, Hash_Table *table, int M, int *count) {

    (*count) = 0;

    int hashcode = hash(item, weights, M);
    Node *cabess = table->linear_list[hashcode]->head;
    Node *rabo = table->linear_list[hashcode]->tail;

    while (cabess != NULL) {
        (*count)++;
        
        if (strcmp(cabess->ingredient_name, item) == 0) {

            printf("Encontrado: %s, Documento ID: %d, Ocorrências: %d\n", 
               cabess->ingredient_name, 
               cabess->i_list->head->ID_Document,
               cabess->i_list->head->Occurrences);
            
            return cabess;  // Item encontrado
               
        }
        cabess = cabess->next;
    }

    return NULL;  // Item não encontrado
}