#include "btree.h"


bool_t bt_is_empty(btree_t t)
{
    return t == NULL;
}

btree_t bt_left(btree_t t)
{
    return bt_is_empty(t) ? NULL : t->left;
}

btree_t bt_right(btree_t t)
{
    return bt_is_empty(t) ? NULL : t->right;
}

btree_t *bt_left_p(btree_t *t)
{
    return bt_is_empty(*t) ? NULL : &((*t)->left);
}

btree_t *bt_right_p(btree_t *t)
{
    return bt_is_empty(*t) ? NULL : &((*t)->right);
}

bool_t bt_is_leave(btree_t t)
{
    if(bt_is_empty(t))
        return FALSE;
    else if(bt_is_empty(t->left) && bt_is_empty(t->right))
        return TRUE;
    else
        return FALSE;
}

bool_t bt_is_internal_node(btree_t t)
{
    return !bt_is_leave(t);
}

unsigned int bt_height(btree_t t)
{
    return bt_is_empty(t) ? 0 : 1 + umax(bt_height(bt_left(t)), bt_height(bt_right(t)));
}

unsigned int bt_nb_nodes(btree_t t)
{
    return bt_is_empty(t) ? 0 : 1 + bt_nb_nodes(bt_left(t)) + bt_nb_nodes(bt_right(t));
}

unsigned int bt_nb_leaves(btree_t t)
{
    if(bt_is_empty(t))
        return 0;
    else if(bt_is_leave(t))
        return 1;
    else
        return bt_nb_leaves(bt_left(t)) + bt_nb_leaves(bt_right(t));
}

unsigned int bt_nb_internal_nodes(btree_t t)
{
    if(bt_is_empty(t))
        return 0;
    else if(bt_is_leave(t))
        return 0;
    else
        return 1 + bt_nb_internal_nodes(bt_left(t)) + bt_nb_internal_nodes(bt_right(t));
}

static void bt_dfs(btree_t t, unsigned int type, void (*callback)(btree_t ct, void *data), void *cdata)
{
    if(!bt_is_empty(t))
    {
        if(type == 1 && callback)
        {
            (*callback)(t, cdata);
        }
        bt_dfs(bt_left(t), type, callback, cdata);
        if(type == 2 && callback)
        {
            (*callback)(t, cdata);
        }
        bt_dfs(bt_right(t), type, callback, cdata);
        if(type == 3 && callback)
        {
            (*callback)(t, cdata);
        }
    }
}

void bt_dfs_prefix(btree_t t, void (*callback)(btree_t ct, void *data), void *cdata)
{
    bt_dfs(t, 1, callback, cdata);
}

void bt_dfs_infix(btree_t t, void (*callback)(btree_t ct, void *data), void *cdata)
{
    bt_dfs(t, 2, callback, cdata);
}

void bt_dfs_suffix(btree_t t, void (*callback)(btree_t ct, void *data), void *cdata)
{
    bt_dfs(t, 3, callback, cdata);
}

void bt_bfs(btree_t t, void (*callback)(btree_t ct, void *data), void *cdata)
{
    btree_t temp;
    queue_t queue = queue_new();

    if(!bt_is_empty(t))
    {
        queue_post(&queue, t);

        while(!queue_is_empty(queue))
        {
            temp = queue_get(&queue);

            (*callback)(temp, cdata);

            if(!bt_is_empty(bt_left(temp)))
                queue_post(&queue, bt_left(temp));
            if(!bt_is_empty(bt_right(temp)))
                queue_post(&queue, bt_right(temp));
        }
    }
}

void bt_reverse_bfs(btree_t t, void (*callback)(btree_t ct, void *data), void *cdata)
{
    btree_t temp;
    stack_t stack = stack_new();
    queue_t queue = queue_new();

    if(!bt_is_empty(t))
    {
        queue_post(&queue, t);

        while(!queue_is_empty(queue))
        {
            temp = queue_get(&queue);

            stack_push(&stack, temp);

            if(!bt_is_empty(bt_left(temp)))
                queue_post(&queue, bt_left(temp));
            if(!bt_is_empty(bt_right(temp)))
                queue_post(&queue, bt_right(temp));
        }

        while(!stack_is_empty(stack))
        {
            temp = stack_pop(&stack);
            callback(temp, cdata);
        }
    }
}

btree_t bt_create(btree_el_t el, btree_t lt, btree_t rt)
{
    btree_t res;
    res = malloc(sizeof(*res));
    if(!res)
        error_handle(FATAL, "Unable to allocate memory\n");
    res->el = el;
    res->left = lt;
    res->right = rt;

    return res;
}

void bt_insert(btree_t *t, btree_el_t el)
{
    if(t)
    {
        if(bt_is_empty(*t))
            *t = bt_create(el, NULL, NULL);
        else
        {
            if(el.key < (*t)->el.key)
                bt_insert(bt_left_p(t), el);
            else
                bt_insert(bt_right_p(t), el);
        }
    }
}

bool_t bt_exist(btree_t t, unsigned int key)
{
    if(bt_is_empty(t))
        return FALSE;
    else if(t->el.key == key)
        return TRUE;
    else if(t->el.key > key)
        return bt_exist(bt_left(t), key);
    else
        return bt_exist(bt_right(t), key);
}

void bt_erase(btree_t *t)
{
     btree_t lt = bt_left(*t);
     btree_t rt = bt_right(*t);

     if(!bt_is_empty(*t))
     {
         bt_erase(&lt);
         bt_erase(&rt);

         if((*t)->el.data)
            free((*t)->el.data);
         free(*t);
         *t = NULL;
     }
}
