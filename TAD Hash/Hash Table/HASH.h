#ifndef HASH_H
#define HASH_H

//#include "read.h"
#include "node.h"
#include "linked.h"
#include <sys/time.h>
#include <string.h>

typedef struct Hash_Table {

    Linked_List **linear_list;
    int *weights;
    int max_size;
    int num_insertions;

} Hash_Table;

// Cabeçalho de funções
Node* search_in_hashtable(char *item, int *weights, Hash_Table *table, int M, int *count);
void insert_in_hashtable(Hash_Table *table, char *word, int id_doc, int *pesos, int M, int *count);
//void insert_hash_2(char *word, int id_doc, int *weights, Hash_Table *table, int M);
void print_hashTable(Hash_Table *table, int M);
int is_hashtable_empty(Hash_Table *table);
void hash_initialize(Hash_Table *table, int M);
void gera_pesos(int *pesos, int n);
void free_table(Hash_Table *table);

#endif