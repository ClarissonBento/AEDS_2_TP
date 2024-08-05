
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "patricia.h"
#define N 2  // Colocar a quantidade de documentos


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

Tree search(Tree *p, char *name) {
    /* Função responsável pela busca de uma palavra solicitada. caso encontrada, ela retorna com o endereço do no onde a palavra está */
    Tree temp = *p;
    while (!IsExternal(temp)) {
        if (Path(temp->node.InternalNode.index, name)) {
            temp = temp->node.InternalNode.right;

        } else {
            temp = temp->node.InternalNode.left;

        }
    }
    if (strcmp(temp->node.item.name, name) == 0) {
        return temp;

    } else {
        printf("Palavra %s não encontrada, \n", name);

        return NULL;
    }
}

Tree search_performace(Tree *p, char *name, int *com, int command) {
    // Função para testar numero de comparações feitas na busca
    Tree temp = *p;
    while (!IsExternal(temp)) {
        if (Path(temp->node.InternalNode.index, name)) {
            temp = temp->node.InternalNode.right;
            (*com)++;
        } else {
            temp = temp->node.InternalNode.left;
            (*com)++;
        }
    }
    if (strcmp(temp->node.item.name, name) == 0) {
        if (command == 1) {
            printf("Palavra %s  encontrada, foram necessária(s) %d comparações\n", name, *com);
            (*com) = 0;
            return temp;
        } else {
            return temp;
        }
    } else {
        printf("Palavra %s não encontrada, \n", name);
        (*com) = 0;
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


// TF-IDF

static void patricia_get_terms(Tree p, int *ni) {
    if (p == NULL) {
        return;
    }
    if (IsExternal(p)) {
        Occurences current = p->node.item.list;
        while (current != NULL) {
            ni[current->ID_Document]++;
            current = current->next;
        }
        return;
    } else {
        patricia_get_terms(p->node.InternalNode.left, ni);
        patricia_get_terms(p->node.InternalNode.right, ni);
        return;
    }
}


static int patricia_get_dj(Tree patricia, char *term){
    Tree temp = search(&patricia, term);
    int cont = 0;
    Occurences current = temp->node.item.list;
    while (current != NULL) {
        cont++;
        current = current->next;
    }
    return cont;
}

static double wij(Tree p, char *term, int doc_number){
    Tree temp = search(&p, term);
    int fij = 0;
    if(temp == NULL){
        return 0;
    }
    Occurences  temp2 = temp->node.item.list;
    while(temp2 != NULL){
        if(temp2->ID_Document == doc_number){
            fij = temp2->Occurrences;
            break;
        }
        temp2 = temp2->next;
    }
    int dj = patricia_get_dj(p, term);
    double  w = fij * log2(N)/dj;
    return w;
}


static void selection_sort(double *arr, int n) {
    int i, j, min_idx;
    double temp;

    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) { // Ordenar em ordem crescente
                min_idx = j;
            }
        }
        // Troca o menor elemento encontrado com o primeiro elemento
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}



void tf_idf(char *words[], Tree patricia, int qtd_terms){
    double doc_relevance[N] = {0};
    double ri = 0, w = 0;
    int ni[N+1];
    for(int i =0; i < N; i++) ni[i+1] = 0;
    patricia_get_terms(patricia, ni);


    for(int j =1; j < N+1; j++){
        ri = 1.0/ni[j];
        for(int k =0; k < qtd_terms; k++){
            w += wij(patricia, words[k], j);
        }
        ri = ri * w;
        printf("Relevancia do documento %d: %f\n", j, ri);
        doc_relevance[j - 1] = ri; // salva a relevancia do documento na posição doc_number - 1
        w = 0;
    }

    selection_sort(doc_relevance, N);
    printf("Documentos mais relevantes: \n");
    for(int i = 0; i < N; i++){
        printf("Documento %d: %.2f \n",i+1,  doc_relevance[i]);
    }
    printf("\n");
    return;

}
