
//colocar o nome do grupo
#ifndef AEDS_2_TP_PATRICIA_H
#define AEDS_2_TP_PATRICIA_H

#include "read.h"
typedef enum {
    INTERNAL, EXTERNAL
} NodeType;

typedef struct Index {
    char letter;
    int position;
} Index;

typedef struct Ingredient {
    char *name;
} Ingredient;

typedef char *IngredientType;

typedef struct pat *Tree;
typedef struct pat {
    NodeType type;
    union {
        struct {
            Index index;
            Tree left, right;
        } InternalNode;
        Ingredient item;
    } node;
} PatNode;



Tree Insert(Ingredient key, Tree *p);
Tree search(Tree *p, Ingredient key);
void print_tree(Tree p);



#endif //AEDS_2_TP_PATRICIA_H
