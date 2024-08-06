#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

void InicializaLista(ListaEncadeada* lista) { //Iniciar a lista
    lista->primeiro = malloc(sizeof(ListaEncadeada)); //Alocar o tamanho da lista
    lista->ultimo = lista->primeiro; //Igualar o primeiro e ultimo apontador
    lista->primeiro->proximo = NULL; //Fim da lista eh nulo
    lista->tamanho = 0; //Tamanho da lista iniciado como 0
}

void InsereFim(ListaEncadeada* lista, Item item) { //Inserir uma celula no final da lista
    lista->ultimo->proximo = (Celula*) malloc(sizeof(Celula)); //Alocar a nova celula no lugar da antiga ultima
    lista->ultimo = lista->ultimo->proximo; //Apontar o ultimo a nova celula
    lista->ultimo->elemento = item; //Adicionar o novo item a nova celula
    lista->ultimo->proximo = NULL; //Igualar a proxima celula da ultima como nula
    lista->tamanho++; //Aumentar o tamanho em 1 apos adicionar a celula
}

void ImprimeLista(ListaEncadeada lista){ //Imprimir os elementos da lista
    Celula *ptr_celula = lista.primeiro->proximo; //Ponteiro de celulas para percorrer a lista
    
    if(ListaVazia(lista) == 1){ //Se a lista estiver vazia terminar funcao
        printf("Lista vazia\n");
        return;
    }
    while(ptr_celula != NULL){ //Enquando o ponteiro apontar para uma celula existente, ou nao nula
        ptr_celula = ptr_celula->proximo; //Ponteiro apontar para a proxima celula
    }
}

int ListaVazia(ListaEncadeada lista){ //Testar se a lista esta vazia
    return (lista.primeiro == lista.ultimo); //Retorna 1 se a os apontadores primeiro e ultimo sao iguais, ou seja a lista eh vazia
}

void DestroiLista(ListaEncadeada* lista){ //Libera a memoria de toda a lista
    Celula *ptr_temp, *ptr_celula = lista->primeiro->proximo; //Ponteiros de celulas para percorrer a lista

    while(ptr_celula != NULL){ //Enquando o ponteiro apontar para uma celula existente, ou nao nula
        ptr_temp = ptr_celula->proximo; //Ponteiro aponta para a proxima celula
        free(ptr_celula); //Libera a memoria da celula atual
        ptr_celula = ptr_temp; //Novo ponteiro aponta para a proxima
    }
    free(lista->primeiro); //Libera a memoria da celula cabeca
}