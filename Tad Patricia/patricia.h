
//colocar o nome do grupo
#ifndef AEDS_2_TP_PATRICIA_H
#define AEDS_2_TP_PATRICIA_H



// LLISTA

typedef struct index_Node {
    int Occurrences;
    int ID_Document;
    struct index_Node *next;

} index_Node;

typedef index_Node *Occurences;


// PATRICIA
typedef enum {
    INTERNAL, EXTERNAL
} NodeType;

typedef struct Index {
    char letter;
    int position;
} Index;


typedef struct Ingredient {
    char *name;
    Occurences list;
} Ingredient;

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

Tree Insert(Ingredient key, Tree *p, int *com, int id_doc, int command);
Tree search(Tree *p, Ingredient key, int *com, int command);
void print_tree(Tree p);
void free_tree(Tree p);



#endif //AEDS_2_TP_PATRICIA_H
