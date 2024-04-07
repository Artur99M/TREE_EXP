#include "../Tree1/header/tree.h"
#include "../Tree1/header/readfile.h"
#include "../header/Diff.h"
#include "../header/SimpleTreeExp.h"
#include <stdlib.h>


int main()
{
    Node* Tree = (Node*) calloc (1, sizeof(Node));

    readfile (&Tree, "data/data.txt");
    // Node* pNode = TreeCopy (Tree);
    // SimplTree (Tree);
    while (SimplConst(Tree));
    TreePrint (Tree);
    SimplTree (Tree);
    TreePrint (Tree);
    // Node* diff = Diff (Tree);
    // TreeDtor (Tree);
    // TreePrint (diff);
    // TreePrint (diff);
    // TreeDtor (diff);
}
