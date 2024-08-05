#include "HASH.h"
#include "linked.h"

// Função para inicializar a tabela hash
void hash_initialize(Hash_Table *table, int M) {
    table->linear_list = (Linked_List **)malloc(M * sizeof(Linked_List *));

    for (int i = 0; i < M; i++) {
        table->linear_list[i] = initialize_LinkedList();
    }

    table->weights = (int *)malloc(M * sizeof(int));
    gera_pesos(table->weights, M);
    table->max_size = M;
    table->num_insertions = 0;
}

// Função para buscar um item na tabela hash
Node* search_in_hashtable(char *item, int *weights, Hash_Table *table, int M, int *count) {

    (*count) = 0;
    
    int hashcode = hash(item, weights, M);
    Node *current = table->linear_list[hashcode]->head;

    while (current != NULL) {
        (*count)++;
        if (strcmp(current->ingredient_name, item) == 0) {
            return current;  // Item encontrado
        }
        current = current->next;
    }

    return NULL;  // Item não encontrado
}

// Função para inserir um item na tabela hash
void insert_in_hashtable(Hash_Table *table, char *word, int id_doc, int *weights, int M, int *count) {

    (*count) = 0;

    int hashcode = hash(word, weights, M);
    Node *current = table->linear_list[hashcode]->head;

    // Verifica se o node já existe primeiro
    while (current != NULL) {

        if (strcmp(current->ingredient_name, word) == 0) {
            
            index_Node *index_current = current->i_list->head;

            while (index_current != NULL) { // Incrementa a ocorrência caso já exista
                if (index_current->ID_Document == id_doc) {
                    index_current->Occurrences++;
                    return;
                }
                index_current = index_current->next;
            }
            // Se o ID do documento não foi encontrado, adiciona um novo nó de índice
            insert_indexNode(current->i_list, id_doc);
            return;
        }
        current = current->next;
        (*count)++;
    }
    
    // Se o node não existir, ai sim cria um novo nnode
    Node *new_node = createNode(word, id_doc);

    if (new_node == NULL) {
        printf("\nErro ao criar um novo node hash.c\n");
        return;
    }

    if (is_emptyList(table->linear_list[hashcode])) {
        table->linear_list[hashcode]->head = new_node;
        table->linear_list[hashcode]->tail = new_node;

    } else {
        //current = table->linear_list[hashcode]->tail;
        //current->next = new_node;
        table->linear_list[hashcode]->tail->next = new_node;
        table->linear_list[hashcode]->tail = new_node;
    }

    table->num_insertions++;
}

/* Tentei usando a lógica do Ziviani
void insert_hash_2(char *word, int id_doc, int *weights, Hash_Table *table, int M) {

    if (search_in_hashtable(word, weights, table, M) == NULL) {
        int hashcode = hash(word, weights, M);
        list_append(table->linear_list[hashcode], word, id_doc);
    } else {
        printf("\nRegistro já existe\n");
    }
}
*/

// Função para imprimir a tabela hash
void print_hashTable(Hash_Table *table, int M) {
    for (int i = 0; i < M; i++) {
        printf("%i: ", i);
        if (!is_emptyList(table->linear_list[i])) {
            display_list(table->linear_list[i], MAX_ING);
            //printf("\n");
        } else {
            printf("Bucket vazio\n");
        }
    }
}

// Função para verificar se a tabela hash está vazia
int is_hashtable_empty(Hash_Table *table) {
    return table->num_insertions == 0;
}

// É a do Ziviani mesmo
void gera_pesos(int *pesos, int n) {
    
    struct timeval semente;
    gettimeofday(&semente, NULL); 
    srand((int)(semente.tv_sec + 1000000*semente.tv_usec));

    for (int i = 0; i < n; i++){
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