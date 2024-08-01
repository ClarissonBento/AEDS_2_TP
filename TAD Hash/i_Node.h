#ifndef I_NODE_H
#define I_NODE_H

typedef struct i_Node {
    
    long numberOfOccurrences;
    long documentID;
    struct PairNode *next;
} i_Node;


#endif