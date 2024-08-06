
#ifndef AEDS_2_TP_READ_H
#define AEDS_2_TP_READ_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../Listas_main/lista.c"
#include "../Listas_main/lista.h"
#include "../Patricia/patricia.c"
//#include "../HASH.c"
//#include "HASH.c"

//int tolower(int c);
void LowerCase(char* str);
void ApagarCaracter(char *str, int n);
void Recorrencia(char* str, char* nomeArq, Tree* patricia, Ingredient ing, int id_doc);
void LeArquivo(ListaEncadeada list, Tree* patricia);
void RecebeEntrada(ListaEncadeada* list);
void BuscarTads(Tree patricia);


#endif //AEDS_2_TP_READ_H
