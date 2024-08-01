#include "linked.h"

// Essas funções são da lista encadeada

void MakeEmpty_List(Linked_List *list) {
    list->head = (Node *)malloc(sizeof(Node));
    list->tail = list->head; 
    list->head->next = NULL;
}

// Função para adicionar um nó ao final da lista
void List_Append(Linked_List *list, ingredient ing_name) {

    if (list == NULL) return -1;

    Node *new_node = CreateNode(ing_name);

    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

int Is_Empty(Linked_List list) {
    if (list.head == list.tail) return 1;
    else return 0;
}

void Display_List(Linked_List list, int N) { // N = num de chaves
    Node *Aux;
    Aux = list.head->next;
    
    while (Aux != NULL) {
        printf("%.*s ", N, Aux->ingredient.name); // ajustar se necessário
        Aux = Aux->next;
    }
}

int List_Count(Linked_List list) {
    int count = 0;
    Node *current = list.head;
    
    // Percorre a lista até o final
    while (current != NULL) {
        count++;
        current = current->next;
    }
    
    return count;
}

/* Ziviani, talvez tirar
void List_Insert(ingredient ing_name, Linked_List *Lista) {

    Lista->tail->next = (Node *)malloc(sizeof(Node));
    Lista->tail = Lista->tail->next; 
    Lista->tail->ingredient = ing_name;
    Lista->tail->next = NULL;
}*/