#include "../header/SimpleTreeExp.h"
#include "../Tree1/header/tree.h"
#include "../DEBUG/def.h"
#include <stdio.h>
#include <math.h>

void SimpleChange (Node* pNode, char value);
const double Eps = 1e-9;

#define CONST(pNode) pNode->left->type == NUMBER && pNode->right->type == NUMBER
#define CONST1(pNode) pNode->left->type == NUMBER
#define ChangeConst(pNode) pNode->type = NUMBER; TreeDtor (pNode->left); TreeDtor (pNode->right); pNode->left = nullptr; pNode->right = nullptr;
#define pi 3.1415f

bool isZero (double x)
{
    return abs (x) < Eps;
}
bool isOne (double x)
{
    return abs (x - 1) < Eps;
}


bool SimplConst(Node* pNode)
{
    if (pNode == nullptr)
        return true;


    PRINT_DEBUG ("SimplConst >>> pNode->type = %d, pNode->value = ", pNode->type);
    #ifdef DEBUG
    if (pNode->type == NUMBER)
        fprintf (stderr, "%lf\n", pNode->value.number);
    if (pNode->type == VARIABLE)
        fprintf (stderr, "%c\n", pNode->value.variable);
    if (pNode->type == OPERATION)
        fprintf (stderr, "%s\n", OPERATIONS[pNode->value.operation - 1].name);
    #endif

    switch (pNode->type)
    {
        case NUMBER:
            return true;
        case VARIABLE:
            return true;

        case OPERATION:
            switch (pNode->value.operation)
            {
                PRINT_DEBUG ("SimplConst >>> I\'m in case OPERATION\n");
                case ADD:
                    if (CONST(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple\n");
                        pNode->value.number = pNode->left->value.number + pNode->right->value.number;
                        ChangeConst (pNode);
                        return false;
                    }
                case SUB:
                    if (CONST(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple\n");
                        pNode->value.number = pNode->left->value.number - pNode->right->value.number;
                        ChangeConst (pNode);
                        return false;
                    }
                case MUL:
                    if (CONST(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple\n");
                        pNode->value.number = pNode->left->value.number * pNode->right->value.number;
                        ChangeConst (pNode);
                        return false;
                    }
                case DIV:
                    if (CONST(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple\n");
                        pNode->value.number = pNode->left->value.number / pNode->right->value.number;
                        ChangeConst (pNode);
                        return false;
                    }
                case SIN:
                    if (CONST1(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple\n");
                        pNode->value.number = sin(pNode->left->value.number);
                        ChangeConst (pNode);
                        return false;
                    }
                case COS:
                    if (CONST1(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple\n");
                        pNode->value.number = cos(pNode->left->value.number);
                        ChangeConst (pNode);
                        return false;
                    }
                case TG:
                    if (CONST1(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple\n");
                        pNode->value.number = tan(pNode->left->value.number);
                        ChangeConst (pNode);
                        return false;
                    }
                case CTG:
                    if (CONST1(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple\n");
                        pNode->value.number = 1 / tan(pNode->left->value.number);
                        ChangeConst (pNode);
                        return false;
                    }
                case EXP:
                    if (CONST(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple\n");
                        pNode->value.number = pow(pNode->left->value.number, pNode->left->value.number);
                        ChangeConst (pNode);
                        return false;
                    }
                case LOG:
                    if (CONST(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple\n");
                        pNode->value.number = log (pNode->right->value.number) / log (pNode->left->value.number);
                        ChangeConst (pNode);
                        return false;
                    }
                case ARCSIN:
                    if (CONST1(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple\n");
                        pNode->value.number = asin(pNode->left->value.number);
                        ChangeConst (pNode);
                        return false;
                    }
                case ARCCOS:
                    if (CONST1(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple\n");
                        pNode->value.number = acos(pNode->left->value.number);
                        ChangeConst (pNode);
                        return false;
                    }
                case ARCTG:
                    if (CONST1(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple\n");
                        pNode->value.number = atan(pNode->left->value.number);
                        ChangeConst (pNode);
                        return false;
                    }
                case ARCCTG:
                    if (CONST1(pNode))
                    {
                        PRINT_DEBUG ("SimplConst >>> I\'m doing more simple\n");
                        pNode->value.number = pi - atan(pNode->left->value.number);
                        ChangeConst (pNode);
                        return false;
                    }
            }
    }

    return (SimplConst (pNode->left) && SimplConst(pNode->right));
}

void SimplTree(Node* pNode)
{
    if (pNode == nullptr)
        return;

    while (true)
        if (SimplConst(pNode) && Simpl01(pNode))
            break;
}

void SimpleChange (Node* pNode, char value)
{
    if (pNode == nullptr || (value != 'l' && value != 'r'))
        return;

    PRINT_DEBUG ("SimpleChange >>> run\n");
    PRINT_DEBUG ("SimpleChange >>> start: pNode = %p, pNode->value = \"%lg\", pNode->type = %d, pNode->left = %p, pNode->right = %p\n", pNode, pNode->value.number, pNode->type, pNode->left, pNode->right);

    if (value == 'r')
    {
        TreeDtor (pNode->left);
        Node* oldnode = pNode->right;
        *pNode = *oldnode;
        free (oldnode);
    }
    else
    {
        TreeDtor (pNode->right);
        Node* oldnode = pNode->left;
        *pNode = *oldnode;
        free (oldnode);
    }
    PRINT_DEBUG ("SimpleChange >>> finish: pNode = %p, pNode->value = \"%lg\", pNode->type = %d, pNode->left = %p, pNode->right = %p\n", pNode, pNode->value.number, pNode->type, pNode->left, pNode->right);
}

void ChangeToNum (Node* pNode, double num)
{
    if (pNode == nullptr)
        return;
    PRINT_DEBUG ("ChangeToNum >>> start: pNode = %p, pNode->value = \"%lg\", pNode->type = %d, pNode->left = %p, pNode->right = %p\n", pNode, pNode->value.number, pNode->type, pNode->left, pNode->right);

    TreeDtor (pNode->left);  pNode->left  = nullptr;
    TreeDtor (pNode->right); pNode->right = nullptr;
    pNode->value.number = num;
    pNode->type = NUMBER;

PRINT_DEBUG ("ChangeToNum >>> finish: pNode = %p, pNode->value = \"%lg\", pNode->type = %d, pNode->left = %p, pNode->right = %p\n", pNode, pNode->value.number, pNode->type, pNode->left, pNode->right);
}

bool Simpl01 (Node* pNode)
{
    if (pNode == nullptr)
        return true;

    if (pNode->type != OPERATION)
        return true;

    PRINT_DEBUG("Simpl01 >>> run\n");
    PRINT_DEBUG ("Simpl01 >>> finish: pNode = %p, pNode->value = \"%lg\", pNode->type = %d, pNode->left = %p, pNode->right = %p\n", pNode, pNode->value.number, pNode->type, pNode->left, pNode->right);

    switch (pNode->value.operation)
    {
        case MUL:
            PRINT_DEBUG("Simpl01 >>> MUL\n");
            if (pNode->left->type  == NUMBER && isOne (pNode->left->value.number))
            { SimpleChange (pNode, 'r'); return false; }
            if (pNode->right->type == NUMBER && isOne (pNode->right->value.number))
            { SimpleChange (pNode, 'l'); return false; }

            if (pNode->left->type  == NUMBER && isZero (pNode->left->value.number))
            { ChangeToNum (pNode, 0);    return false; }
            if (pNode->right->type == NUMBER && isZero (pNode->right->value.number))
            { ChangeToNum (pNode, 0);    return false; }

        case ADD:
            if (pNode->left->type  == NUMBER && isZero (pNode->left->value.number))
            { SimpleChange (pNode, 'r'); return false; }
            if (pNode->right->type == NUMBER && isZero (pNode->left->value.number))
            { SimpleChange (pNode, 'l'); return false; }

        case DIV:
            if (pNode->left->type  == NUMBER && isZero (pNode->left->value.number))
            { ChangeToNum (pNode, 0);    return false; }

        case EXP:
            if (pNode->left->type  == NUMBER && isOne (pNode->left->value.number))
            { ChangeToNum (pNode, 1);    return false; }
            if (pNode->right->type  == NUMBER && isOne (pNode->right->value.number))
            { SimpleChange (pNode, 'l'); return false; }

            if (pNode->left->type  == NUMBER && isZero (pNode->left->value.number))
            { ChangeToNum (pNode, 0);    return false; }
            if (pNode->right->type == NUMBER && isZero (pNode->right->value.number))
            { ChangeToNum (pNode, 1);    return false; }
    }

    PRINT_DEBUG ("Simpl01 >>> finish: pNode = %p, pNode->value = \"%lg\", pNode->type = %d, pNode->left = %p, pNode->right = %p\n", pNode, pNode->value.number, pNode->type, pNode->left, pNode->right);

    return Simpl01(pNode->left) && Simpl01(pNode->right);
}

