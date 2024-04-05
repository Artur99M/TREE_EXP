#ifndef TREE_H
#define TREE_H
#define MAX_STR_SIZE 64
#include "../../header/TREE_EXP.h"
typedef VALUE elem_t;

typedef struct Node
{
    TYPE   type;
    elem_t value;
    Node*  right;
    Node*  left;
} Node;

enum TREE_ERROR
{
    TREE_NO_ERROR                 = 0,
    TREE_NULLPTR                  = 1,
    TREE_ELEM_NULLPTR             = 2,
    TREE_CALLOC_ERROR             = 4,
    TREE_NO_ELEM                  = 8,
    TREE_ADD_ERROR                = 16,
    ELEM_IS_VALUE_OF_NODE_OF_TREE = 32,
    TREE_FILE_NULLPTR             = 64,
    TREE_HZ_ERROR                 = 128,
    TREE_VOID                     = 256
};

TREE_ERROR TreePrint (const Node*);
TREE_ERROR TreeFPrint (Node*, char*);
Node* TreeCopy (const Node*);
Node* CreateNode (TYPE, elem_t, Node*, Node*);
void TreeDtor (Node*);
#endif
