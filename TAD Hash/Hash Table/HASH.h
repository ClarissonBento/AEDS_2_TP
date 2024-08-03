#ifndef HASH_H
#define HASH_H

#include "read.h"
#include "node.h"
#include "linked.h"
#include <sys/time.h>

typedef struct Hash_Table {

    Linked_List **linear_list;
    int *weights;
    int max_size;
    int num_insertions;

} Hash_Table;

#endif