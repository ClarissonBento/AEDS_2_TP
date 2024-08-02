// colocar o nome dos membros


#include "patricia.h"


short IsExternal(Tree p) {
    return (p->type == EXTERNAL);
}

int SelectPath(Index index, Ingredient key, int i) {
    int max_size = (int)strlen(key.name);
    int id = (int) index.letter;
    int key_char = (int) key.name[i];
    if (index.position >= max_size || id > key_char) {
        return 0; // \0 is placed on the left side of the tree
    } else {
        return 1;
    }
}

Tree CreateExternalNode(Ingredient key) {
    Tree p = (Tree) malloc(sizeof(PatNode));
    p->node.item.name = (char *)malloc((strlen(key.name) + 1) * sizeof(char));
    p->node.item = key;
    p->type = EXTERNAL;
    return p;
}

Tree CreateInternalNode(int i, Tree *left, Tree *right, char diff) {
    Tree temp;
    temp = (Tree) malloc(sizeof(PatNode));
    temp->type = INTERNAL;
    temp->node.InternalNode.left = *left;
    temp->node.InternalNode.right = *right;
    temp->node.InternalNode.index.position = i;
    temp->node.InternalNode.index.letter = diff;
    return temp;
}

Tree InsertBetween(Ingredient key, Tree *p, int i, char diff) {
    if (IsExternal(*p) || i < (*p)->node.InternalNode.index.position) {
        // create external node
        Tree temp = CreateExternalNode(key);
        if (SelectPath((*p)->node.InternalNode.index, key, i) == 1) {
            return(CreateInternalNode(i, p, &temp, diff));
        } else {
            return(CreateInternalNode(i, &temp, p, diff));
        }
    } else {
        if (SelectPath((*p)->node.InternalNode.index, key, i) == 1) {
            (*p)->node.InternalNode.right = InsertBetween(key, &(*p)->node.InternalNode.right, i, diff);
        } else {
            (*p)->node.InternalNode.left = InsertBetween(key, &(*p)->node.InternalNode.left, i, diff);
        }
        return (*p);
    }
}

Tree Insert(Ingredient key, Tree *p) {
    if (*p == NULL) {
        return(CreateExternalNode(key));
    }
    Tree temp = *p;
    int i = 0;
    while (!IsExternal(temp)) {
        if (SelectPath(temp->node.InternalNode.index, key, i) == 1) {
            temp = temp->node.InternalNode.right;
            i++;
        } else {
            temp = temp->node.InternalNode.left;
            i++;
        }
    }
    int max_size = (int)strlen(key.name);
    i = 0;
    while ((i < max_size) && ((int)key.name[i] == (int)temp->node.item.name[i])) {
        i++;
    }
    if (i >= max_size) {
        printf("Handle here\n");
        return *p;
    } else {
        return InsertBetween(key, p, i, key.name[i]);
    }
}



