#ifndef	__ST_GTREE_H__
#define	__ST_GTREE_H__

#include "stlib.h"

ST_BEGIN_DECLS;

/* 遍历的方式 */
typedef enum
{
  ST_IN_ORDER,
  ST_PRE_ORDER,
  ST_POST_ORDER,
  ST_LEVEL_ORDER
} STGTraverseType;

typedef struct _STGTreeNode
{
  stpointer   key;         				/* 键值key for this node */
  stpointer   value;       				/* 排序值value stored at this node */
  struct _STGTreeNode *left;        	/* left subtree */
  struct _STGTreeNode *right;       	/* right subtree */
  stint8      balance;     				/* 平衡因子height (left) - height (right) */
  stuint8     left_child;  				/* flag of LR child */
  stuint8     right_child;
}STGTreeNode;

typedef struct _STGTree
{
  STGTreeNode        *root;
  STCompareDataFunc  key_compare;
  STDestroyNotify    key_destroy_func;
  STDestroyNotify    value_destroy_func;
  stpointer          key_compare_data;
  stuint             nnodes;
}STGTree;

typedef stbool (*STGTraverseFunc) (stpointer  key,
                                   stpointer  value,
                                   stpointer  data);

/* Balanced binary trees
 */

STGTree*   st_tree_new             (STCompareFunc      key_compare_func);
STGTree*   st_tree_new_with_data   (STCompareDataFunc  key_compare_func,
                                 stpointer          key_compare_data);
STGTree*   st_tree_new_full        (STCompareDataFunc  key_compare_func,
                                 stpointer          key_compare_data,
                                 STDestroyNotify    key_destroy_func,
                                 STDestroyNotify    value_destroy_func);
void     st_tree_destroy         (STGTree            *tree);
void     st_tree_insert          (STGTree            *tree,
                                 stpointer          key,
                                 stpointer          value);
void     st_tree_replace         (STGTree            *tree,
                                 stpointer          key,
                                 stpointer          value);
stbool st_tree_remove          (STGTree            *tree,
                                 stconstpointer     key);
stbool st_tree_steal           (STGTree            *tree,
                                 stconstpointer     key);
stpointer st_tree_lookup          (STGTree            *tree,
                                 stconstpointer     key);
stbool st_tree_lookup_extended (STGTree            *tree,
                                 stconstpointer     lookup_key,
                                 stpointer         *orist_key,
                                 stpointer         *value);
void     st_tree_foreach         (STGTree            *tree,
                                 STGTraverseFunc	   func,
                                 stpointer	   user_data);


void     st_tree_traverse        (STGTree            *tree,
                                 STGTraverseFunc     traverse_func,
                                 STGTraverseType     traverse_type,
                                 stpointer          user_data);


stpointer st_tree_search          (STGTree            *tree,
                                 STCompareFunc      search_func,
                                 stconstpointer     user_data);
stint     st_tree_height          (STGTree            *tree);
stint     st_tree_nnodes          (STGTree            *tree);

ST_END_DECLS;
#endif	/* __ST_GTREE_H__ */
