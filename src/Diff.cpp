#include "../header/Diff.h"
#include "../Tree1/header/tree.h"
#ifndef nullptr
#define nullptr 0x0
#endif
#define CNN(x) CreateNodeNumber(x, nullptr, nullptr)
// Node* CreateNodeNumber  (double, Node*, Node*);
// Node* CreaNodeOperation (OP,     Node*, Node*);
// Node* CreaNodeVariable  (char,   Node*, Node*);
#ifndef exp
#define exp 2.718281828f
#endif
#define _D(x) Diff(x)
#define _C(x) TreeCopy(x)
#define _ADD(left, right) CreateNodeOperation(ADD, left, right)
#define _SUB(left, right) CreateNodeOperation(SUB, left, right)
#define _MUL(left, right) CreateNodeOperation(MUL, left, right)
#define _DIV(left, right) CreateNodeOperation(DIV, left, right)
#define _EXP(left, right) CreateNodeOperation(EXP, left, right)
#define _SIN(x) CreateNodeOperation (SIN, x, nullptr)
#define _COS(x) CreateNodeOperation (COS, x, nullptr)
#define _LN(x) CreateNodeOperation ( LOG, CreateNodeNumber(exp, nullptr, nullptr), x)

Node* Diff (const Node* pNode)
{
    if (pNode == nullptr)
        return nullptr;

    switch (pNode->type)
    {
        case NUMBER:
            return CreateNodeNumber (0, nullptr, nullptr);
        case VARIABLE:
            return CreateNodeNumber (1, nullptr, nullptr);
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
                    _EXP(_C(pNode->right), CreateNodeNumber (2, nullptr, nullptr)));

                case SIN:
                    return _MUL (_COS (_C(pNode->left)), _D(pNode->left));
                case COS:
                    return _MUL (_SIN (_C(pNode->left)), _D(pNode->left));
                case EXP:
                    if (pNode->left->type != NUMBER && pNode->right->type == NUMBER)
                        return _MUL(_MUL (_C(pNode->right), _EXP(_C(pNode->left), _SUB(_C(pNode->right),
                        CreateNodeNumber (1, nullptr, nullptr)))), _D(pNode->left));
                    if (pNode->left->type == NUMBER && pNode->right->type != NUMBER)
                        return _MUL (_MUL (_LN (_C(pNode->left)), _C(pNode)), _D(pNode->right));
                    if (pNode->left->type != NUMBER && pNode->right->type != NUMBER)
                        _MUL (_EXP (CNN(exp), _MUL (_C(pNode->left), _LN(pNode->right))), _D (_MUL (_C(pNode->left), _LN(pNode->right))));
                case LOG:
                    if (pNode->left->type == NUMBER && pNode->right->type != NUMBER)
                        return _MUL (_DIV(CreateNodeNumber(1, nullptr, nullptr), _MUL(_C(pNode->right), _LN(_C(pNode->left)))),
                        _D(pNode->right));
                    if (pNode->left->type != NUMBER && pNode->right->type == NUMBER)
                        return _D(_DIV (CreateNodeNumber(1, nullptr, nullptr),
                                        CreateNodeOperation(LOG, _C(pNode->right), _C(pNode->left))));
                    if (pNode->left->type != NUMBER && pNode->right->type != NUMBER)
                        return _D (_DIV ( _LN (pNode->left), _LN (pNode->right)));
                case ARCSIN:
                    return _MUL (_DIV (CNN(1), _EXP (_ADD (CNN(1), _EXP(_C(pNode->left),
                    CNN(2))), CNN(0.5f))), _D(pNode->left));
                case ARCCOS:
                    return _MUL (_SUB (CNN(0), _DIV (CNN(1), _EXP (_ADD (CNN(1), _EXP(_C(pNode->left),
                    CNN(2))), CNN(0.5f)))), _D(pNode->left));
                case ARCTG:
                    return _MUL(_DIV(CNN(1), _ADD(CNN(1), _EXP(_C(pNode->left), CNN(2)))), _D(pNode->left));
                case ARCCTG:
                    return _MUL(_SUB (CNN(0), _DIV(CNN(1), _ADD(CNN(1), _EXP(_C(pNode->left), CNN(2))))), _D(pNode->left));

            }
    }
    return nullptr;
}
