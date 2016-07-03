#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "btree.h"
#include "instructions_btree.h"


static void cb_print_tree(btree_t ct, void *data);

int main(void)
{
    btree_t tree;
    btree_el_t el;
    bool_t tree_valid;

    el.key = 2;
    el.data = malloc(sizeof(node_data_t));
    ((node_data_t*)el.data)->ope = DIV;
    ((node_data_t*)el.data)->value = 0.f;
    tree = bt_create(el, NULL, NULL);

    el.key = 1;
    el.data = malloc(sizeof(node_data_t));
    ((node_data_t*)el.data)->ope = NO;
    ((node_data_t*)el.data)->value = 1.f;
    bt_insert(&tree, el);

    el.key = 3;
    el.data = malloc(sizeof(node_data_t));
    ((node_data_t*)el.data)->ope = NO;
    ((node_data_t*)el.data)->value = 4.f;
    bt_insert(&tree, el);

    tree_valid = insbt_is_valid(tree);

    puts("\nBEFORE\n");
    bt_bfs(tree, cb_print_tree, NULL);

    if(tree_valid)
        insbt_compute(tree);

    puts("\nAFTER\n");
    bt_bfs(tree, cb_print_tree, NULL);

    bt_erase(&tree);

    return EXIT_SUCCESS;
}

static void cb_print_tree(btree_t ct, void *data)
{
    if(ct && ct->el.data)
        printf("Node %3d:\n     Ope: %d\n   Value: %f\n", ct->el.key, ((node_data_t*)ct->el.data)->ope, ((node_data_t*)ct->el.data)->value);
}
