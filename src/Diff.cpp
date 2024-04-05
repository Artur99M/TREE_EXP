#include "../header/Diff.h"
#include "../Tree1/header/tree.h"
#ifndef nullptr
#define nullptr 0x0
#endif
#ifndef exp
#define exp 2.718281828f
#endif
#define _D(x) Diff(x)
#define _C(x) TreeCopy(x)
#define _ADD(left, right) CreateNode(OPERATION, ADD, left, right)
#define _SUB(left, right) CreateNode(OPERATION, SUB, left, right)
#define _MUL(left, right) CreateNode(OPERATION, MUL, left, right)
#define _DIV(left, right) CreateNode(OPERATION, DIV, left, right)
#define _EXP(left, right) CreateNode(OPERATION, EXP, left, right)
#define _SIN(x) CreateNode (OPERATION, SIN, x, nullptr)
#define _COS(x) CreateNode (OPERATION, COS, x, nullptr)
#define _LN(x) CreteNode (OPERATION, LOG, CreateNode(NUMBER, exp, nullptr, nullptr), x)

Node* Diff (const Node* pNode)
{
    if (pNode == nullptr)
        return nullptr;

    switch (pNode->type)
    {
        case NUMBER:
            return CreateNode (NUMBER,  0, nullptr, nullptr);
        case VARIABLE:
            return CreateNode (VARIABLE, 1, nullptr, nullptr);
        case OPERATION:
            switch (pNode->value.operation)
            {
                case ADD:
                    return _ADD (_D(pNode->left), _D(pNode->right));
                    // return CreateNode (OPERATION, ADD, Diff(pNode->left), Diff (pNode->right));
                case SUB:
                    return _SUB (_D(pNode->left), _D(pNode->right));
                    // return CreateNode (OPERATION, SUB, Diff(pNode->left), Diff (pNode->right));
                case MUL:
                    return       _ADD (_MUL (_D(pNode->left), _C(pNode->right)), _MUL (_C(pNode->left), _D(pNode->right)));
                case DIV:
                    return _DIV (_SUB (_MUL (_D(pNode->left), _C(pNode->right)), _MUL (_C(pNode->left), _D(pNode->right))),
                    _EXP(_C(pNode->right), CreateNode (NUMBER, 2, nullptr, nullptr)));

                case SIN:
                    return _MUL (_COS (_C(pNode->left)), _D(pNode->left));
                case COS:
                    return _MUL (_SIN (_C(pNode->left)), _D(pNode->left));
                case EXP:
                    if (pNode->left->type != NUMBER && pNode->right->type == NUMBER)
                        return _MUL (_MUL (CreateNode (NUMBER, pNode->right->value.number - 1, nullptr, nullptr),
                        _C(pNode->left)), _D(pNode->left));
                    if (pNode->left->type == NUMBER && pNode->right->type != NUMBER)
                        return _MUL (_MUL (_LN (_C(pNode->left)), _C(pNode)), _D(pNode->right))
                    // ещё один случай
            }
    }
    return nullptr;
}
