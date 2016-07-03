#ifndef DEF_TYPES
#define DEF_TYPES


typedef enum bool_t
{
    FALSE,
    TRUE
} bool_t;

typedef enum operation_e
{
    NO,
    ADD,
    SUB,
    MUL,
    DIV
} operation_e;

typedef struct node_data_t
{
    operation_e ope;
    double value;
} node_data_t;


#endif
