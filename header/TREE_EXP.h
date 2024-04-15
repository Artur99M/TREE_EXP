#ifndef TREE_EXP_H
#define TREE_EXP_H
enum TYPE
{
    OPERATION   = 1,
    NUMBER      = 2,
    VARIABLE    = 3
};

enum OP
{
    ADD    = 1,
    SUB    = 2,
    MUL    = 3,
    DIV    = 4,
    SIN    = 5,
    COS    = 6,
    TG     = 7,
    CTG    = 8,
    EXP    = 9,
    LOG    = 10,
    ARCSIN = 11,
    ARCCOS = 12,
    ARCTG  = 13,
    ARCCTG = 14,
    EQUAL  = 15
};

union VALUE
{
    double number;
    char variable;
    OP operation;
};

typedef struct operation
{
    char name[7];
    OP value;
} operation;

const int num_operation = 15;
const operation OPERATIONS[] =
    {
    {"+", ADD},
    {"-", SUB},
    {"*", MUL},
    {"/", DIV},
    {"sin", SIN},
    {"cos", COS},
    {"tg", TG},
    {"ctg", CTG},
    {"^", EXP},
    {"log", LOG},
    {"arcsin", ARCSIN},
    {"arccos", ARCCOS},
    {"arctg", ARCTG},
    {"arcctg", ARCCTG},
    {"=", EQUAL}
    };
// #include "../Tree/header/tree.h"
#endif
