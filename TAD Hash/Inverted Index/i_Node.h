#ifndef I_NODE_H
#define I_NODE_H

typedef struct i_Node {
    float num_Occurrence;
    float ID_document;
    struct i_Node *next;

} i_Node;


#endif