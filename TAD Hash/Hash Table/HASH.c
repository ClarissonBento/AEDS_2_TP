#include "HASH.h"
#include "linked.h"

Node* search_in_hashtable(char *item, int *pesos, Hash_Table table, int M) {
    int hashcode = hash(item, pesos, M);
    Node *current = table.linear_list[hashcode];

    while (current != NULL) {
        if (strcmp(current->ingredient_name, item) == 0) {
            return current;  // Item encontrado
        }
        current = current->next;
    }

    return NULL;  // Item não encontrado
}

void insert_in_hashtable(Hash_Table *table, char *word, int id_doc, int *pesos, int M) {

    int hashcode = hash(word, pesos, M);
    Node *new_node = createNode(word, id_doc);

    if (table->linear_list[hashcode] == NULL) {
        table->linear_list[hashcode] = new_node;

    } else {
        Node *current = table->linear_list[hashcode];

        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }

}

// tentei usando a lógica do Ziviani
void insert_hash_2(char *word, int id_doc, int *weights, Hash_Table *table, int M) {

    if (search_in_hashtable(word, weights, *table, M) == NULL) {
        list_append(table->linear_list, word, id_doc);
    } else printf("\nRegistro já existe\n");
    
} 

// Não tô achando o erro
void print_hashTable(Hash_Table *table, int M) {
    
    for (int i = 0; i < M; i++) {
        printf("%i: ", i);

        if (is_emptyList(table->linear_list) == 1) {
            display_list(table->linear_list, MAX_ING);
            printf("\n");
        }
        
    }

}

int is_hashtable_empty(Hash_Table *table) {
    if (table->num_insertions == 0) return 1;
}

void hash_initialize(Hash_Table *table, int M) {

    for (int i = 0; i < M; i++){
        MakeEmpty_List(&table[i]);
    } 
}

void gera_pesos(int *pesos, int n) {
    int i;
    struct timeval semente;
    gettimeofday(&semente, NULL); 
    srand((int)(semente.tv_sec + 1000000*semente.tv_usec));

    for (i = 0; i < n; i++){
        pesos[i] =  1+(int) (10000.0*rand()/(RAND_MAX+1.0));
    }
}

// Função para liberar a memória da tabela hash
void free_table(Hash_Table *table) {

    for (int i = 0; i < table->max_size; i++) {
        Node *current = table->linear_list[i]->head;

        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
        free(table->linear_list[i]);
    }

    free(table->linear_list);
    free(table->weights);
    free(table);
}