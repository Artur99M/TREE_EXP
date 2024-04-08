#include "../Tree1/header/tree.h"
#include "../Tree1/header/readfile.h"
#include "../header/Diff.h"
#include "../header/SimpleTreeExp.h"
#include <stdlib.h>
#include <stdio.h>


int main()
{
    Node* Tree = (Node*) calloc (1, sizeof(Node));

    readfile (&Tree, "data/data.txt");
    TreePrint (Tree);
    putchar ('\n');
    // SimplTree (Tree);
    while (!Simpl01 (Tree));
    TreePrint (Tree);
    // Node* diff = Diff (Tree);
    TreeDtor (Tree);
    // TreePrint (diff);
    // putchar ('\n');
    // SimplTree (diff);
    // putchar ('\n');
    // TreePrint (diff);
    // TreeDtor (diff);
}
