#include "i_Index.h"
#include <stdio.h>
#include <stdlib.h>

// Função para inicializar uma nova lista encadeada
index_List *initialize_indexList() {
    index_List *new_index = (index_List *)malloc(sizeof(index_List));
    
    if (new_index == NULL) {
        printf("Erro aqui no indice invertido da tabela hash.\n");
        return NULL;
    }

    new_index->head = NULL;
    new_index->tail = NULL;

    return new_index;
}

// Função para verificar se a lista está vazia
int is_index_empty(index_List *list) {
    return list->head == NULL;
}

// Função para inserir um novo node no indice invertido
int insert_indexNode(index_List *list, int documentID) {

    index_Node *new_node = initialize_indexNode(documentID);

    if (new_node == NULL) {
        printf("\nFalhou em alocar memória pra um novo node do indice invertido da tabela hash\n");
        return 0;
    }

    if (is_index_empty(list)) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }

    return 1;
}

// Função para buscar um node no indice invertido
index_Node *search_indexNode(index_List *list, int documentID) {
    
    if (is_index_empty(list)) {
        printf("\nTentou buscar num indice invertido vazio\n");
        return NULL;
    }

    index_Node *i_node = list->head;

    while (i_node && i_node->ID_Document != documentID) {
        i_node = i_node->next;
    }

    return i_node;
}

// Printar o indice invertido
void print_indexList(index_List *list) {

    if (is_index_empty(list)) {
        printf("\nINDICE INVERTIDO VAZIO\n");
        return;
    }

    index_Node *current = list->head;

    while (current != NULL) {
        printf("| <N = %i | ID = %i> ", current->Occurrences, current->ID_Document);
        current = current->next;
    }
    printf("\n");
}

// Praticamente desnecessário
int size_indexList(index_List *list) {

    int size = 0;
    struct index_Node *current_node = list->head;

    while (current_node) {
        size += sizeof(index_Node);
        current_node = current_node->next;
    }

    size += sizeof(index_List);

    return size;
}