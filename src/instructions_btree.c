#include "instructions_btree.h"


static void cb_insbt_validate_tree_level(btree_t t, void *data)
{
    if(t && t->el.data && data && *((bool_t*)data) == TRUE)
    {
        bool_t *res = (bool_t*)data;
        #if CALC_DEBUG
        printf("Node %d ", t->el.key);
        #endif

        if(bt_is_leave(t) && ((node_data_t*)t->el.data)->ope == NO)
        {
            *res = TRUE;
            #if CALC_DEBUG
            puts("is leave and OPE = NO.             --- VALID");
            #endif
        }
        else if(bt_is_internal_node(t) && ((node_data_t*)t->el.data)->ope != NO)
        {
            *res = TRUE;
            #if CALC_DEBUG
            puts("is internal node and OPE != NO.    --- VALID");
            #endif
        }
        else
        {
            *res = FALSE;
            #if CALC_DEBUG
            puts("is not good.                       --- NOT VALID");
            #endif
        }
    }
}

bool_t insbt_is_valid(btree_t t)
{
    bool_t res;

    if(t)
    {
        res = TRUE;

        bt_dfs_prefix(t, cb_insbt_validate_tree_level, &res);
    }
    else
        res = FALSE;

    #if CALC_DEBUG
    if(res)
        puts("\nTree                                      --- VALID");
    else
        puts("\nTree                                      --- NOT VALID");
    #endif

    return res;
}

static void cb_insbt_compute_node(btree_t t, void *data)
{
    if(t && t->el.data && t->left && t->left->el.data && t->right && t->right->el.data)
    {
        switch(((node_data_t*)t->el.data)->ope)
        {
        case NO:
            break;
        case ADD:
            ((node_data_t*)t->el.data)->value = ((node_data_t*)bt_left(t)->el.data)->value + ((node_data_t*)bt_right(t)->el.data)->value;
            break;
        case SUB:
            ((node_data_t*)t->el.data)->value = ((node_data_t*)bt_left(t)->el.data)->value - ((node_data_t*)bt_right(t)->el.data)->value;
            break;
        case MUL:
            ((node_data_t*)t->el.data)->value = ((node_data_t*)bt_left(t)->el.data)->value * ((node_data_t*)bt_right(t)->el.data)->value;
            break;
        case DIV:
            if(double_equals(((node_data_t*)bt_right(t)->el.data)->value, 0.f))
            {
                ((node_data_t*)t->el.data)->value = 0.f;
            }
            else
            {
                ((node_data_t*)t->el.data)->value = ((node_data_t*)bt_left(t)->el.data)->value / ((node_data_t*)bt_right(t)->el.data)->value;
            }
            break;
        default:
            break;
        }

        ((node_data_t*)t->el.data)->ope = NO;
    }
}

void insbt_compute(btree_t t)
{
    if(t)
    {
        bt_reverse_bfs(t, cb_insbt_compute_node, NULL);
    }
}
