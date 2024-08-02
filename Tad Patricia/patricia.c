#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>




short IsExternal(Tree p) {
    return (p->type == EXTERNAL);
}

int SelectPath(Index index, Ingredient key, Tree p) {
    int keyLen = (int)strlen(key.name);
    if (index.position < keyLen && key.name[index.position] != index.letter) {
        return (key.name[index.position] > index.letter) ? 1 : 0;
    } else {
        return 1;
    }
}

int Path(Index Int_Index, char *Ingredient_name) {

    if(Ingredient_name[Int_Index.position]  >=  Int_Index.letter){
        return 1;
    }else{
        return 0;
    }
}

char Internal_char_selection(char *TreeWord, char *NewWord, int Diff_Index) {
    return (TreeWord[Diff_Index] > NewWord[Diff_Index]) ? TreeWord[Diff_Index] : NewWord[Diff_Index];
}

Tree CreateExternalNode(Ingredient key) {
    Tree p = (Tree) malloc(sizeof(PatNode));
    p->node.item.name = strdup(key.name);
    p->type = EXTERNAL;
    return p;
}

Tree CreateInternalNode(int i, Tree left, Tree right, char diff) {
    Tree temp = (Tree) malloc(sizeof(PatNode));
    temp->type = INTERNAL;
    temp->node.InternalNode.left = left;
    temp->node.InternalNode.right = right;
    temp->node.InternalNode.index.position = i;
    temp->node.InternalNode.index.letter = diff;
    return temp;
}

Tree InsertBetween(Ingredient key, Tree *p, int i, char diff, char *compared_char) {
    if (IsExternal(*p)) {

        diff = Internal_char_selection((*p)->node.item.name, key.name, i);
        Tree temp = CreateExternalNode(key);
        Tree New;
        if (strcmp(key.name, (*p)->node.item.name) == 0  || (strcmp(key.name, (*p)->node.item.name) > 0 )){
            New = CreateInternalNode(i, *p, temp, diff);
            return New;
        } else {

            New = CreateInternalNode(i, temp, *p, diff);
            return New;
        }
    } else if (i < (*p)->node.InternalNode.index.position) {// Se o indice do no for menor que o indice que difere os caracteres da palavra
        con++;
        Tree temp = CreateExternalNode(key);
        if (strcmp(key.name, compared_char) == 0 || (strcmp(key.name, compared_char) > 0)){ // Se a palavra que insere for maior ou igual que a palavra do no
            return CreateInternalNode(i, *p, temp, diff); // o indice de comparação do no interno recebe o caracter da palavra que entra,
        } else {
            return CreateInternalNode(i, temp, *p, compared_char[i]); // o indice de comparação do no interno recebe o caracter da palavra que já estava no no que comparamos na inseração
        }
    } else {
        if (Path((*p)->node.InternalNode.index, key.name)) {
            (*p)->node.InternalNode.right = InsertBetween(key, &(*p)->node.InternalNode.right, i, diff, compared_char);
        } else {
            (*p)->node.InternalNode.left = InsertBetween(key, &(*p)->node.InternalNode.left, i, diff, compared_char);
        }
        return *p;
    }
}

Tree Insert(Ingredient key, Tree *p) {
    if (*p == NULL) {
        return CreateExternalNode(key);
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
    int max_size = (int)strlen(key.name);
    i = 0;
    while (i < max_size && key.name[i] == temp->node.item.name[i]) {
        i++;
    }

    if(strcmp(key.name, temp->node.item.name) == 0){
        printf("Palavra já existe\n");
        return *p;
    }

    char diff = Internal_char_selection(temp->node.item.name, key.name, i);
    return InsertBetween(key, p, i, diff, temp->node.item.name);


}

Tree search(Tree *p, Ingredient key) {
    Tree temp = *p;
    while (!IsExternal(temp)) {
        if (Path(temp->node.InternalNode.index, key.name)) {
            temp = temp->node.InternalNode.right;
        } else {
            temp = temp->node.InternalNode.left;
        }
    }
    if (strcmp(temp->node.item.name, key.name) == 0) {
        printf("Palavra encontrada\n");
        return temp;
    } else {
        printf("Palavra não encontrada, %s\n", key.name);
        return NULL;
    }
}

void print_tree(Tree p) {

    if (p == NULL) {
        return;
    }
    if (!IsExternal(p)) {
        print_tree(p->node.InternalNode.left);

    }
    if (IsExternal(p)) {
        printf("%s\n", p->node.item.name);
        con++;
    }
    if (!IsExternal(p)) {
        print_tree(p->node.InternalNode.right);
    }
}

void free_tree(Tree p) {
    if (p == NULL) {
        return;
    }
    if (!IsExternal(p)) {
        free_tree(p->node.InternalNode.left);
        free_tree(p->node.InternalNode.right);
    } else {
        free(p->node.item.name);
    }
    free(p);
}
