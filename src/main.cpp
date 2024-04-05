#include "../Tree/header/tree.h"
#include "../Tree/header/readfile.h"
#include <stdlib.h>


int main()
{
    Node* Tree = (Node*) calloc (1, sizeof(Node));

    readfile (&Tree, "data/data.txt");
    TreePrint (Tree);
}
