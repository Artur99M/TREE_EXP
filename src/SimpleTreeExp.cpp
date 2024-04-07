#include "../header/SimpleTreeExp.h"
#include <math.h>

#define CONST(pNode) pNode->left->type == NUMBER && pNode->right->type == NUMBER
#define ChangeConst(pNode) pNode->type = NUMBER; TreeDtor (pNode->left); TreeDtor (pNode->right)
#define pi 3.1415f


bool SimplConst(Node* pNode)
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
                    case ADD:
                        if (CONST(pNode))
                        {
                            pNode->value.number = pNode->left->value.number + pNode->right->value.number;
                            ChangeConst (pNode);
                            return false;
                        }
                    case SUB:
                        if (CONST(pNode))
                        {
                            pNode->value.number = pNode->left->value.number - pNode->right->value.number;
                            ChangeConst (pNode);
                            return false;
                        }
                    case MUL:
                        if (CONST(pNode))
                        {
                            pNode->value.number = pNode->left->value.number * pNode->right->value.number;
                            ChangeConst (pNode);
                            return false;
                        }
                    case DIV:
                        if (CONST(pNode))
                        {
                            pNode->value.number = pNode->left->value.number / pNode->right->value.number;
                            ChangeConst (pNode);
                            return false;
                        }
                    case SIN:
                        if (CONST(pNode))
                        {
                            pNode->value.number = sin(pNode->left->value.number);
                            ChangeConst (pNode);
                            return false;
                        }
                    case COS:
                        if (CONST(pNode))
                        {
                            pNode->value.number = cos(pNode->left->value.number);
                            ChangeConst (pNode);
                            return false;
                        }
                    case TG:
                        if (CONST(pNode))
                        {
                            pNode->value.number = tan(pNode->left->value.number);
                            ChangeConst (pNode);
                            return false;
                        }
                    case CTG:
                        if (CONST(pNode))
                        {
                            pNode->value.number = 1 / tan(pNode->left->value.number);
                            ChangeConst (pNode);
                            return false;
                        }
                    case EXP:
                        if (CONST(pNode))
                        {
                            pNode->value.number = pow(pNode->left->value.number, pNode->left->value.number);
                            ChangeConst (pNode);
                            return false;
                        }
                    case LOG:
                        if (CONST(pNode))
                        {
                            pNode->value.number = log (pNode->left->value.number) / log (pNode->left->value.number);
                            ChangeConst (pNode);
                            return false;
                        }
                    case ARCSIN:
                        if (CONST(pNode))
                        {
                            pNode->value.number = asin(pNode->left->value.number);
                            ChangeConst (pNode);
                            return false;
                        }
                    case ARCCOS:
                        if (CONST(pNode))
                        {
                            pNode->value.number = acos(pNode->left->value.number);
                            ChangeConst (pNode);
                            return false;
                        }
                    case ARCTG:
                        if (CONST(pNode))
                        {
                            pNode->value.number = atan(pNode->left->value.number);
                            ChangeConst (pNode);
                            return false;
                        }
                    case ARCCTG:
                        if (CONST(pNode))
                        {
                            pNode->value.number = pi - atan(pNode->left->value.number);
                            ChangeConst (pNode);
                            return false;
                        }
                }
        }
}
