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
    if (pNode->type == NUMBER)
        PRINT_DEBUG ("%lf\n", pNode->value.number);
    if (pNode->type == VARIABLE)
        PRINT_DEBUG ("%c\n", pNode->value.variable);
    if (pNode->type == OPERATION)
        PRINT_DEBUG ("%s\n", OPERATIONS[pNode->value.operation - 1].name);

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
                        pNode->value.number = log (pNode->left->value.number) / log (pNode->left->value.number);
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

bool SimplZO (Node* pNode)
{
    if (pNode == nullptr)
        return true;

    switch (pNode->type)
    {
        case NUMBER:
            return true;
        case VARIABLE:
            return true;

        case OPERATION:
            switch (pNode->value.operation)
            {
                case MUL:
                    if (pNode->left->type == NUMBER && isOne(pNode->left->value.number))
                    {
                        SimpleChange (pNode, 'l');
                        return false;
                    }
                    else if (pNode->right->type == NUMBER && isOne(pNode->right->value.number))
                    {
                        SimpleChange (pNode, 'r');
                        return false;
                    }
                    else if ((pNode->left->type  == NUMBER && isZero(pNode->left->value.number)) ||
                        (pNode->right->type == NUMBER && isZero(pNode->right->value.number)))
                    {
                        TreeDtor (pNode);
                        pNode = CreateNodeNumber (0, nullptr, nullptr);
                        return false;
                    }

                case ADD:
                    if (pNode->left->type == NUMBER && isZero(pNode->left->value.number))
                    {
                        SimpleChange (pNode, 'l');
                        return false;
                    }
                    else if (pNode->right->type == NUMBER && isZero(pNode->right->value.number))
                    {
                        SimpleChange (pNode, 'r');
                        return false;
                    }

                case DIV:
                    if (pNode->left->type == NUMBER && isZero(pNode->left->value.number))
                    {
                        TreeDtor (pNode);
                        pNode = CreateNodeNumber (0, nullptr, nullptr);
                        return false;
                    }
                    else if (pNode->right->type == NUMBER && isOne(pNode->right->value.number))
                    {
                        SimpleChange (pNode, 'r');
                        return false;
                    }

                case EXP:
                    if (pNode->left->type == NUMBER && isZero(pNode->left->value.number))
                    {
                        TreeDtor (pNode);
                        pNode = CreateNodeNumber (0, nullptr, nullptr);
                        return false;
                    }
                    else if (pNode->left->type == NUMBER && isOne(pNode->left->value.number))
                    {
                        TreeDtor (pNode);
                        pNode = CreateNodeNumber (1, nullptr, nullptr);
                        return false;
                    }
                    else if (pNode->right->type == NUMBER && isOne(pNode->right->value.number))
                    {
                        SimpleChange (pNode, 'r');
                        return false;
                    }
                    else if (pNode->right->type == NUMBER && isZero(pNode->right->value.number))
                    {
                        TreeDtor (pNode);
                        pNode = CreateNodeNumber (1, nullptr, nullptr);
                        return false;
                    }
            }
    }

    return SimplZO(pNode->left) && SimplZO(pNode->right);
}

void SimplTree(Node* pNode)
{
    if (pNode == nullptr)
        return;

    while (!SimplConst(pNode) && !SimplZO(pNode))
        PRINT_DEBUG ("SimplTree >>> I do it\n");
}

void SimpleChange (Node* pNode, char value)
{
    if (pNode == nullptr || (value != 'l' && value != 'r'))
        return;

    if (value == 'l')
    {
        pNode->type  = pNode->right->type;
        pNode->value = pNode->right->value;
        TreeDtor (pNode->left);
        pNode->left = pNode->right->left;
        Node* oldpNode = pNode->right;
        pNode->right = pNode->right->right;
        free (oldpNode);
    }
    else
    {
        pNode->type  = pNode->left->type;
        pNode->value = pNode->left->value;
        TreeDtor (pNode->right);
        pNode->right = pNode->left->right;
        Node* oldpNode = pNode->left;
        pNode->left = pNode->left->left;
        free (oldpNode);
    }
}
