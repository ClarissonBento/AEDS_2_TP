
//colocar o nome do grupo
#ifndef AEDS_2_TP_PATRICIA_H
#define AEDS_2_TP_PATRICIA_H

#include "read.h"

Tree Insert(Ingredient key, Tree *p);
Tree search(Tree *p, Ingredient key);
void print_tree(Tree p);



#endif //AEDS_2_TP_PATRICIA_H
