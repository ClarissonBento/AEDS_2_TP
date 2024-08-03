#include "HASH.h"
#include "linked.h"

void Insere(ingredient x, int *weights, Hash_Table table) {
    
    if (Pesquisa(x.name, weights, table) == NULL)
    List_Append(x, &table[h(x.name, weights)]);
    else printf(" Registro ja  esta  presente\n");
} 

void Imprime(Hash_Table *table, int M) {
    
    for (int i = 0; i < M; i++) {
        printf("%i: ", i);

        if (!Is_Empty(table->linear_list))
        Display_List(table[i]->linear_list, MAX_ING);
        printf("\n");
        
    }

}

void Hash_Initialize(Hash_Table *table, int M) {

    for (int i = 0; i < M; i++){
        MakeEmpty_List(&table[i]);
    } 
}

void GeraPesos(int *pesos, int n) {
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