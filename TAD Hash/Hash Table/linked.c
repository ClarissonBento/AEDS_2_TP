#include "linked.h"

// Função para inicializar uma nova lista encadeada (das colisões)
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

// Função para verificar se a lista está vazia
int is_emptyList(Linked_List *list) {
    return list->head == NULL;
}

// Função para adicionar um nó ao final da lista
void list_append(Linked_List *list, char *word, int doc_id) {

    Node *new_node = createNode(word, doc_id);

    if (new_node == NULL) {
        printf("\nErro ao criar um novo nó.\n");
        return;
    }

    if (is_emptyList(list)) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

// Printar a lista encadeada das colisões
void display_list(Linked_List *list, int N) { // N = num de chaves

    if (is_emptyList(list)) {
        printf("\nLista encadeada vazia.\n");
        return;
    }

    Node *aux = list->head;
    
    while (aux != NULL) {
        printf("%.*s ", N, aux->ingredient_name); // ajustar se necessário
        aux = aux->next;
    }
    printf("\n");
}

// Função para contar o número de nós na lista
int count_list(Linked_List *list) {
    int count = 0;
    Node *current = list->head;
    
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