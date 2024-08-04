
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "patricia.h"



// LISTA ENCADEADA
static index_Node *initialize_indexNode(int documentID) {
    /* Função responsável pela inicialização da lista de ocorrência
       de um determinado ingrediente de um determinado doc */
    index_Node *i_node = (index_Node*)malloc(sizeof(index_Node));
    if (i_node == NULL) {
        printf("\nErro no node do indice invertido da tabela hash\n");
        return NULL;
    }
    i_node->ID_Document = documentID;
    i_node->Occurrences = 1;
    i_node->next = NULL;
    return i_node;
}

static Occurences Search_Id_Doc(Occurences list, int documentID) {
    /*
     * Função usada para procurar se a palavra inserida já tem seu id_doc inicializado, e incrementa a quantidade
    */
    Occurences current = list;
    while (current != NULL) {
        if (current->ID_Document == documentID) {
            current->Occurrences++;
            return current;
        }
        current = current->next;
    }
    return NULL;
}

static void insert_new_occurence(Occurences list, int documentID) {
    /*
     * Função responsável por inserir um novo id_doc em uma palavra já inserida na arvore
    */
    Occurences new_node = Search_Id_Doc(list, documentID);
    if (new_node != NULL) {
        return;
    } else {
        new_node = initialize_indexNode(documentID);
        if (new_node == NULL) {
            printf("\nFalhou em alocar memória pra um novo node do indice invertido\n");
            return;
        }
        if (list == NULL) {
            list = new_node;
        } else {
            Occurences current = list;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_node;
        }
    }
}

// PATRICIA

static short IsExternal(Tree p) { // verificação se no é exeterno.
    return (p->type == EXTERNAL);
}

static int Path(Index Int_Index, char *Ingredient_name) {
    /* Função responsável por percorrer a arvore usando a lógica de comparação de caracteres,
       onde o menor caracter é o que está mais a esquerda e o maior e igual a direita.
    */
    if (Ingredient_name[Int_Index.position] >= Int_Index.letter) {
        return 1;
    } else {
        return 0;
    }
}

static char Internal_char_selection(char *TreeWord, char *NewWord, int Diff_Index) {
    /* Função responsável por selecionar o caracter que será usado como indice de comparação do no interno
       caso o caracter da palavra inserida ser maior que o da palavra em comparação da arvore, esse é o indice interno
       se não, o da arvore assume o posto.
    */
    return (TreeWord[Diff_Index] > NewWord[Diff_Index]) ? TreeWord[Diff_Index] : NewWord[Diff_Index];
}

static Tree CreateExternalNode(Ingredient key, int id_doc) {
    /* Função de criação de nó externo da árvore Patricia */
    Tree p = (Tree) malloc(sizeof(PatNode));
    if (p == NULL) {
        printf("\nErro ao alocar memória para o nó externo da árvore Patricia\n");
        return NULL;
    }
    strncpy(p->node.item.name, key.name, 20); // copiar a string para o array
    p->node.item.list = (Occurences)malloc(sizeof(index_Node)); // alocação de memoria para a lista de indices invertidos
    if (p->node.item.list == NULL) {
        printf("\nErro ao alocar memória para a lista de índices\n");
        return NULL;
    }
    p->node.item.list = initialize_indexNode(id_doc); // criação da lista
    p->type = EXTERNAL;
    return p;
}

static Tree CreateInternalNode(int i, Tree left, Tree right, char diff) {
    // Função de criação de nó interno da arvore patricia conforme expecificado pelo professor Ziviani
    Tree temp = (Tree) malloc(sizeof(PatNode));
    temp->type = INTERNAL;
    temp->node.InternalNode.left = left;
    temp->node.InternalNode.right = right;
    temp->node.InternalNode.index.position = i;
    temp->node.InternalNode.index.letter = diff;
    return temp;
}

static Tree InsertBetween(Ingredient key, Tree *p, int i, char diff, char *compared_string, int *com, int id_doc) {
    /* Função de inserções de nos na arvore adptada para a inseração de strings, em vez de chars */
    if (IsExternal(*p)) {
        diff = Internal_char_selection((*p)->node.item.name, key.name, i);
        Tree temp = CreateExternalNode(key, id_doc);
        Tree New;
        if (strcmp(key.name, (*p)->node.item.name) == 0 || (strcmp(key.name, (*p)->node.item.name) > 0)) {
            // no externo com a palavra maior ou igual sendo alocada a direita, e a arvore filha a esquerda e criação do no interno
            (*com)++;
            New = CreateInternalNode(i, *p, temp, diff);
            return New;
        } else {
            (*com)++;
            New = CreateInternalNode(i, temp, *p, diff);
            return New;
        }
    } else if (i < (*p)->node.InternalNode.index.position) { // Se o indice do no for menor que o indice que difere os caracteres da palavra
        Tree temp = CreateExternalNode(key, id_doc);
        if (strcmp(key.name, compared_string) == 0 || (strcmp(key.name, compared_string) > 0)) { // Se a palavra que insere for maior ou igual que a palavra do no
            (*com)++;
            return CreateInternalNode(i, *p, temp, diff); // o indice de comparação do no interno recebe o caracter da palavra que entra,
        } else {
            (*com)++;
            return CreateInternalNode(i, temp, *p, compared_string[i]); // o indice de comparação do no interno recebe o caracter da palavra que já estava no nó que comparamos na inseração
        }
    } else {
        if (Path((*p)->node.InternalNode.index, key.name)) {
            (*com)++;
            (*p)->node.InternalNode.right = InsertBetween(key, &(*p)->node.InternalNode.right, i, diff, compared_string, com, id_doc);
        } else {
            (*com)++;
            (*p)->node.InternalNode.left = InsertBetween(key, &(*p)->node.InternalNode.left, i, diff, compared_string, com, id_doc);
        }
        return *p;
    }
}

Tree Insert(Ingredient key, Tree *p, int *com, int id_doc, int command) {
    /* Função responsável pelo inserção da palavra na patricia, onde id_doc é o documento de origem,
       com é a variável responsável pela contabilização de comparações
       e command reponsável pela pela impressão do conteúdo pedido no item 6 da especificação do TP
    */
    if (*p == NULL) {
        return CreateExternalNode(key, id_doc);
    }
    Tree temp = *p;
    int i;
    while (!IsExternal(temp)) {
        if (Path(temp->node.InternalNode.index, key.name)) {
            temp = temp->node.InternalNode.right;
        } else {
            temp = temp->node.InternalNode.left;
        }
    }

    if (strcmp(key.name, temp->node.item.name) == 0) {
        insert_new_occurence(temp->node.item.list, id_doc);
        return *p;
    }

    int max_size = (int)strlen(key.name);
    i = 0;
    while (i < max_size && key.name[i] == temp->node.item.name[i]) {
        i++;
    }

    char diff = Internal_char_selection(temp->node.item.name, key.name, i);
    temp = InsertBetween(key, p, i, diff, temp->node.item.name, com, id_doc);
    if (command == 1) {
        printf("Palavra %s inserida, foram necessária(s) %d comparações\n", key.name, *com);
    }
    (*com) = 0;
    return temp;
}

Tree search(Tree *p, Ingredient key, int *com, int command) {
    /* Função responsável pela busca de uma palavra solicitada. caso encontrada, ela retorna com o endereço do no onde a palavra está */
    Tree temp = *p;
    while (!IsExternal(temp)) {
        if (Path(temp->node.InternalNode.index, key.name)) {
            temp = temp->node.InternalNode.right;
            (*com)++;
        } else {
            temp = temp->node.InternalNode.left;
            (*com)++;
        }
    }
    if (strcmp(temp->node.item.name, key.name) == 0) {
        if (command == 1) {
            printf("Palavra %s  encontrada, foram necessária(s) %d comparações\n", key.name, *com);
            (*com) = 0;
            return temp;
        } else {
            return temp;
        }
    } else {
        printf("Palavra %s não encontrada, \n", key.name);
        return NULL;
    }
}

static void Print_Node(Ingredient node) {
    /* Função auxiliar para impressão da lista de índices invertido de uma palavra */
    printf("%s:", node.name);
    printf(" [");
    Occurences current = node.list;
    while (current != NULL) {
        printf("qtd: %d, doc_id: %d", current->Occurrences, current->ID_Document);
        printf("]");
        if (current->next != NULL) {
            printf("--->");
            printf("[");
        }
        current = current->next;
    }
    printf("\n");
    return;
}

void print_tree(Tree p) {
    /* Função responsável pela impressão da arvore em ordem alfabética e de seu indice invertido */
    if (p == NULL) {
        return;
    }
    if (!IsExternal(p)) {
        print_tree(p->node.InternalNode.left);
    }
    if (IsExternal(p)) {
        Print_Node(p->node.item);
    }
    if (!IsExternal(p)) {
        print_tree(p->node.InternalNode.right);
    }
}

void free_tree(Tree p) {
    // Função responsável pela liberação de memória da arvore
    if (p == NULL) {
        return;
    }
    if (!IsExternal(p)) {
        free_tree(p->node.InternalNode.left);
        free_tree(p->node.InternalNode.right);
    } else {
        // não é necessário liberar p->node.item.name, pois não usamos strdup mais
    }
    free(p);
}


