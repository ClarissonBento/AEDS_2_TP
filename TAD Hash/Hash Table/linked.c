#include "linked.h"

// Essas funções são da lista encadeada

Linked_List *initialise_LinkedList() {

    Linked_List *list = (Linked_List *)malloc(sizeof(Linked_List));

    if (list == NULL) {
        printf("\nErro no linked.c\n");
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;

    return list;
}

// Função para adicionar um nó ao final da lista
void list_append(Linked_List *list, char *word, int doc_id) {

    is_emptyList(list);

    Node *new_node = createNode(*word, doc_id); // conferir isso

    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

int is_emptyList(Linked_List *list) {
    if (list->head == list->tail) return 1;
}

void display_list(Linked_List *list, int N) { // N = num de chaves
    Node *aux;
    aux = list->head->next;
    
    while (aux != NULL) {
        printf("%.*s ", N, aux->ingredient_name); // ajustar se necessário
        aux = aux->next;
    }
}

int count_list(Linked_List list) {
    int count = 0;
    Node *current = list.head;
    
    // Percorre a lista até o final
    while (current != NULL) {
        count++;
        current = current->next;
    }
    
    return count;
}

// Esse faz lista fazia talvez seja desnecessário

void MakeEmpty_List(Linked_List *list) {
    list->head = (Node *)malloc(sizeof(Node));
    list->tail = list->head; 
    list->head->next = NULL;
}

/* Ziviani, talvez tirar
void List_Insert(ingredient ing_name, Linked_List *Lista) {

    Lista->tail->next = (Node *)malloc(sizeof(Node));
    Lista->tail = Lista->tail->next; 
    Lista->tail->ingredient = ing_name;
    Lista->tail->next = NULL;
}*/