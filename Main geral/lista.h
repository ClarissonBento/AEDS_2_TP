#ifndef TAD_LISTA_ENCADEADA_H
#define TAD_LISTA_ENCADEADA_H

typedef struct {
    char fileName[40];
} Item;

typedef struct Celula{
    Item elemento;
    struct Celula* proximo;
} Celula;
typedef Celula* Apontador;

typedef struct {
    Apontador primeiro;
    Apontador ultimo;
    int tamanho;
} ListaEncadeada;

void InicializaLista(ListaEncadeada* lista);
void InsereFim(ListaEncadeada* lista, Item item);
void ImprimeLista(ListaEncadeada lista);
int ListaVazia(ListaEncadeada lista);
void DestroiLista(ListaEncadeada* lista);

#endif
