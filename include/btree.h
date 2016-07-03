#ifndef DEF_BTREE
#define DEF_BTREE


#include <stdlib.h>

#include "utils.h"
#include "types.h"
#include "queue.h"
#include "stack.h"


typedef struct btree_el_t
{
    unsigned int key;
    void* data;
} btree_el_t;

typedef struct btree_node_t* btree_t;

struct btree_node_t
{
    btree_el_t el;
    btree_t left;
    btree_t right;
};

bool_t bt_is_empty(btree_t t);
btree_t bt_left(btree_t t);
btree_t bt_right(btree_t t);
btree_t *bt_left_p(btree_t *t);
btree_t *bt_right_p(btree_t *t);
bool_t bt_is_leave(btree_t t);
bool_t bt_is_internal_node(btree_t t);
unsigned int bt_height(btree_t t);
unsigned int bt_nb_nodes(btree_t t);
unsigned int bt_nb_leaves(btree_t t);
unsigned int bt_nb_internal_nodes(btree_t t);
void bt_dfs_prefix(btree_t t, void (*callback)(btree_t ct, void *data), void *cdata);
void bt_dfs_infix(btree_t t, void (*callback)(btree_t ct, void *data), void *cdata);
void bt_dfs_suffix(btree_t t, void (*callback)(btree_t ct, void *data), void *cdata);
void bt_bfs(btree_t t, void (*callback)(btree_t ct, void *data), void *cdata);
void bt_reverse_bfs(btree_t t, void (*callback)(btree_t ct, void *data), void *cdata);
btree_t bt_create(btree_el_t el, btree_t lt, btree_t rt);
void bt_insert(btree_t *t, btree_el_t el);
bool_t bt_exist(btree_t t, unsigned int key);
void bt_erase(btree_t *t);


#endif
