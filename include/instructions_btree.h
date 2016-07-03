#ifndef DEF_INSTRUCTIONS_BTREE
#define DEF_INSTRUCTIONS_BTREE

#include "config.h"
#include "btree.h"
#include "types.h"
#include "utils.h"

#if CALC_DEBUG
#include <stdio.h>
#endif

bool_t insbt_is_valid(btree_t t);
void insbt_compute(btree_t t);


#endif
