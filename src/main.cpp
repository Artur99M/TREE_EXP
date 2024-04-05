#include "../Tree1/header/tree.h"
#include "../Tree1/header/readfile.h"
#include <stdlib.h>


int main()
{
    Node* Tree = (Node*) calloc (1, sizeof(Node));

    readfile (&Tree, "data/data.txt");

    Node* pNode = TreeCopy (Tree);
    TreePrint (Tree);
    putchar ('\n');
    TreePrint (pNode);
}
