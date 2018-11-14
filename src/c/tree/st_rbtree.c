#include <stdio.h>
#include <malloc.h>
#include "st_rbtree.h"
#include "st_log.h"


/*	全局变量引用	*/

extern RBNode * RBNullNode ;
extern RBNode * Current, * Sibling, * Parent, * GrParent, * GrGrParent ;


/*	局部函数声明	*/

static RBNode * singleRotateWithLeft (RBNode * const parent) ;
static RBNode * singleRotateWithRight (RBNode * const parent) ;
static RBNode * rotate (RBNode * const parent, const RBItem item) ;
static void handleReorient (pRBTree * const prbt, const RBItem item) ;
static void changeColor (void) ;
static void traversal (const RBNode * const pn, void (* pfun) (const RBNode * const pn)) ;
static void release (RBNode * const pn) ;


/*	接口函数定义	*/

/*	(*prbt) -> root -> right is the real root instead of (*prbt) -> root.	*/
stbool st_rbtree_create (pRBTree * const prbt)
{
    RBNullNode = (RBNode *) malloc (sizeof (RBNode)) ;
    if (NULL == RBNullNode)
        return FALSE ;
    *prbt = (pRBTree) malloc (sizeof (RBTree)) ;
    if (NULL == *prbt)
    {
        free (RBNullNode) ;
        RBNullNode = NULL ;
        return FALSE ;
    }
    (*prbt)->root = (RBNode *) malloc (sizeof (RBNode)) ;
    if (NULL == (*prbt)->root)
    {
        free (RBNullNode) ;
        RBNullNode = NULL ;
        free (*prbt) ;
    }
    RBNullNode->item = INFINITY ;
    RBNullNode->left = RBNullNode->right = RBNullNode ;
    RBNullNode->color = Black ;

    (*prbt)->root->item = NEGATIVE_INFINITY ;
    (*prbt)->root->left = (*prbt)->root->right = RBNullNode ;
    (*prbt)->root->color = Black ;			// the root node color is black

    (*prbt)->current = 0 ;

    return TRUE ;
}

stbool st_rbtree_empty (const pRBTree * const prbt)
{
    if (0 == (*prbt)->current)
        return TRUE ;
    else
        return FALSE ;
}

stbool st_rbtree_insert (pRBTree * const prbt, const RBItem item)
{
    RBNode * newNode ;

    GrParent = Parent = Current = (*prbt)->root ;		
    RBNullNode->item = item ;

    while (Current->item != item)
    {
        GrGrParent = GrParent ;
        GrParent = Parent ;
        Parent = Current ;
        if (item < Current->item)			//进行二分插入
            Current = Current->left ;
        else
            Current = Current->right ;
        /*如果在插入遍历过程中，若两子树都是红色，需要做适应操作,因为不适应，破坏性质3,4*/
        if (Red == Current->left->color && Red == Current->right->color)
            handleReorient (prbt, item) ;				// change color and keep balance
    }
    if (Current != RBNullNode)			// if the insert node == some tree node , return  false
        return FALSE ;
    newNode = (RBNode *) malloc (sizeof (RBNode)) ;
    if (NULL == newNode)
        return FALSE ;
    newNode->item = item ;
    newNode->left = newNode->right = RBNullNode ;

    if (item <Parent->item)
        Parent->left = newNode ;
    else
        Parent->right = newNode ;
    Current = newNode ;
    handleReorient (prbt, item) ;

    (*prbt)->current++ ;

    return TRUE ;
}

/*	The central idea is go to delete a red leaf.	*/
stbool st_rbtree_delete (pRBTree * const prbt, const RBItem item)
{
    stbool found = FALSE ;
    RBNode * record ;
    RBItem scapegoat ;
    stint temp ;

    if (st_rbtree_empty (prbt))
        return FALSE ;
    Current = (*prbt)->root ;
    /*	First, look for it.	*/
    while (Current != RBNullNode)
    {
        if (item == Current->item)
        {
            found = TRUE ;
            record = Current ;
            break ;
        }
        else if (item < Current->item)
        {
            Parent = Current ;
            Current = Current->left ;
        }
        else
        {
            Parent = Current ;
            Current = Current->right ;
        }
    }
    /*	If not found.	*/
    if (FALSE == found)
        return FALSE ;
    if (Current->right != RBNullNode)
    {
        Parent = Current ;
        Current = Parent->right ;
        scapegoat = Current->item ;
        /*	Without optimizing it.	*/
        while (Current->left != RBNullNode)
        {
            Parent = Current ;
            Current = Current->left ;
            scapegoat = Current->item ;
        }
        /*	Make it be a lead.	*/
        if (Current->right != RBNullNode)
        {
            temp = Current->color ;
            Current->color = Current->right->color ;
            Current->right->color = temp ;
            Parent->left = singleRotateWithRight (Current) ;
        }
    }
    else if (Current->left != RBNullNode)
    {
        Parent = Current ;
        Current = Parent->left ;
        scapegoat = Current->item ;
        while (Current->right != RBNullNode)
        {
            Parent = Current ;
            Current = Current->right ;
            scapegoat = Current->item ;
        }
        if (Current->left != RBNullNode)
        {
            temp = Current->color ;
            Current->color = Current->left->color ;
            Current->left->color = temp ;
            Parent->right = singleRotateWithLeft (Current) ;
        }
    }
    /*	If Current is a leaf.	*/
    else
    {
        /*	If current is a red leaf.	*/
        if (Red == Current->color)
        {
            if (Current == Parent->left)
                Parent->left = RBNullNode ;
            else
                Parent->right = RBNullNode ;
            free (Current) ;
            (*prbt)->current-- ;
            return TRUE ;
        }
        else
            scapegoat = Current->item ;
    }
    /*	Next hasn't be integrated.	*/
    (*prbt)->root->color = Red ;
    Current = (*prbt)->root ;
    /*	Make sure RBNullNode -> item hasn't appear in the tree.	*/
    RBNullNode->item = (*prbt)->root->item ;
    /*	Core loop.	*/
    while (Current->item != scapegoat)
    {
        if (scapegoat < Current->item)
        {
            /*	Updata node.	*/
            GrParent = Parent ;
            Parent = Current ;
            Current = Parent->left ;
            Sibling = Parent->right ;
            /*	If Current has a leaf at least.	*/
            if (Red == Current->left->color || Red == Current->right->color)
            {
                if (scapegoat < Current->item)
                {
                    /*	If Current drops onto a black node.	*/
                    if (Black == Current->left->color)
                    {
                        Current->color = Red ;
                        Current->right->color = Black ;
                        Parent->left = singleRotateWithRight (Current) ;
                    }
                    /*	If Current drops on to a red node, update node and continue.	*/
                    else
                    {
                        GrParent = Parent ;
                        Parent = Current ;
                        Current = Parent->left ;
                        Sibling = Parent->right ;
                        continue ;
                    }
                }
                else
                {
                    /*	If Current drops onto a black node.	*/
                    if (Black == Current->right->color)
                    {
                        Current->color = Red ;
                        Current->left->color = Black ;
                        Parent->left = singleRotateWithLeft (Current) ;
                    }
                    /*	If Current drops on to a red node, update node and continue.	*/
                    else
                    {
                        GrParent = Parent ;
                        Parent = Current ;
                        Current = Parent->right ;
                        Sibling = Parent->left ;
                        continue ;
                    }
                }
            }
            /*	If Current has two black children.	*/
            if (Black == Current->left->color && Black == Current->right->color)
            {
                /*	If Sibling's left child is red.	*/
                if (Red == Sibling->left->color)
                {
                    Parent->right = singleRotateWithLeft (Sibling) ;
                    Parent->color = Black ;
                    Current->color = Red ;
                    if (Parent == GrParent->left)
                        GrParent->left = singleRotateWithRight (Parent) ;
                    else
                        GrParent->right = singleRotateWithRight (Parent) ;
                }
                /*	If Sibling's right child is red.	*/
                else if (Red == Sibling->right->color)
                {
                    Parent->color = Black ;
                    Sibling->right->color = Black ;
                    Sibling->color = Red ;
                    Current->color = Red ;
                    if (Parent == GrParent->left)
                        GrParent->left = singleRotateWithRight (Parent) ;
                    else
                        GrParent->right = singleRotateWithRight (Parent) ;
                }
                /*	If Sibling has two black children.	*/
                else
                    changeColor () ;
            }
        }
        /*	The circumstances of whirling has a little strange.	*/
        else
        {
            GrParent = Parent ;
            Parent = Current ;
            Current = Parent->right ;
            Sibling = Parent->left ;
            if (Red == Current->left->color || Red == Current->right->color)
            {
                if (scapegoat < Current->item)
                {
                    if (Black == Current->left->color)
                    {
                        Current->color = Red ;
                        Current->right->color = Black ;
                        Parent->right = singleRotateWithRight (Current) ;
                    }
                    else
                    {
                        GrParent = Parent ;
                        Parent = Current ;
                        Current = Parent->left ;
                        Sibling = Parent->right ;
                        continue ;
                    }
                }
                else
                {
                    if (Black == Current->right->color)
                    {
                        Current->color = Red ;
                        Current->left->color = Black ;
                        Parent->left = singleRotateWithLeft (Current) ;
                    }
                    else
                    {
                        GrParent = Parent ;
                        Parent = Current ;
                        Current = Parent->right ;
                        Sibling = Parent->left ;
                        continue ;
                    }
                }
            }
            if (Black == Current->left->color && Black == Current->right->color)
            {
                if (Red == Sibling->left->color)
                {
                    Parent->color = Black ;
                    Sibling->left->color = Black ;
                    Sibling->color = Red ;
                    Current->color = Red ;
                    if (Parent == GrParent->left)
                        GrParent->left = singleRotateWithLeft (Parent) ;
                    else
                        GrParent->right = singleRotateWithLeft (Parent) ;
                }
                else if (Red == Sibling->right->color)
                {
                    Parent->left = singleRotateWithRight (Sibling) ;
                    Parent->color = Black ;
                    Current->color = Red ;
                    if (Parent == GrParent->left)
                        GrParent->left = singleRotateWithLeft (Parent) ;
                    else
                        GrParent->right = singleRotateWithLeft (Parent) ;
                }
                else
                {
                    changeColor () ;
                    if (Red == RBNullNode->color)
                    {
                        putchar ('\a') ;
                        RBNullNode->color = Black ;
                    }
                }
            }
        }
    }
    /*	Replace.	*/
    record->item = scapegoat ;
    if (scapegoat == Parent->left->item)
        Parent->left = RBNullNode ;
    else
        Parent->right = RBNullNode ;
    free (Current) ;
    (*prbt)->root->color = Black ;
    (*prbt)->root->right->color = Black ;

    (*prbt)->current-- ;

    return TRUE ;
}

void st_rbtree_traverse (const pRBTree * const prbt, void (* pfun) (const RBNode * const pn))
{
    traversal ((*prbt)->root->right, pfun) ;
    putchar ('\n') ;
}

void st_rbtree_release (const pRBTree * const prbt)
{
    release ((*prbt)->root->right) ;
    free ((*prbt)->root) ;
    free (*prbt) ;
    free (RBNullNode) ;
}

/*	局部函数定义	*/

/*	child will become the new root of the subtree.	*/
static RBNode * singleRotateWithLeft (RBNode * const parent)
{
    RBNode * child ;

    child = parent->left ;
    parent->left = child->right ;
    child->right = parent ;

    return child ;
}

static RBNode * singleRotateWithRight (RBNode * const parent)
{
    RBNode * child ;

    child = parent->right ;
    parent->right = child->left ;
    child->left = parent ;

    return child ;
}

static RBNode * rotate (RBNode * const parent, const RBItem item)
{
    if (item < parent->item)
    {
        return parent->left = item < parent->left->item ?
            singleRotateWithLeft (parent->left)
            : singleRotateWithRight (parent->left) ;
    }
    else
    {
        return parent->right = item < parent->right->item ?
            singleRotateWithLeft (parent->right)
            : singleRotateWithRight (parent->right) ;
    }
}

static void handleReorient (pRBTree * const prbt, const RBItem item)
{
    /*如果两个儿子都是红色，则将current和child进行换色*/
    Current->color = Red ;
    Current->left->color = Current->right->color = Black ;

    if (Red == Parent->color)	
    {
        /*如果父亲是红色，则设爷爷为红色*/
        GrParent->color = Red ;	
        /*判断是之字型还是一字型旋转,如果是之字形，旋转两次*/
        if ((item < GrParent->item) != (item < Parent->item))
            Parent = rotate (GrParent, item) ;
        Current = rotate (GrGrParent, item) ;
        Current->color = Black ;
    }
    (*prbt)->root->right->color = Black ;
}

/*	Won't change RBNullNode's color.	*/
static void changeColor (void)
{
    if (Parent->left != RBNullNode)
        Parent->left->color = Red ;
    Parent->color = Black ;
    Parent->right->color = Red ;
}

static void traversal (const RBNode * const pn, void (* pfun) (const RBNode * const pn))
{
    if (pn != RBNullNode)
    {
        traversal (pn->left, pfun) ;
        (* pfun) (pn) ;
        traversal (pn->right, pfun) ;
    }
}

/* 释放node下的子树 */
static void release (RBNode * const pn)
{
    if (pn != RBNullNode)
    {
        release (pn->left) ;
        release (pn->right) ;
        free (pn) ;
    }
}




/*-------------complete the down2up RBTREE -----------------*/;
void    rb_traverse(rb_node_t* root)
{
    if(root != NULL)
    {
        rb_traverse(root->left);
        printf("%d ", root->key);
        rb_traverse(root->right);
    }
}


static rb_node_t* rb_new_node(RBKey_t key, data_t data)
{
    rb_node_t *node = (rb_node_t*)malloc(sizeof(struct rb_node_t));

    if (!node)
    {
        printf("malloc error!\n");
        exit(-1);
    }
    node->key = key, node->data = data;

    return node;
}

//三、红黑树查找结点
//----------------------------------------------------  
//rb_search_auxiliary：查找
//rb_node_t* rb_search：返回找到的结点
//----------------------------------------------------
static rb_node_t* rb_search_auxiliary(RBKey_t key, rb_node_t* root, rb_node_t** save)
{
    rb_node_t *node = root, *parent = NULL;

    int ret;

    while(node)
    {
        parent = node ;
        // 二分查找合适的插入点
        if(key < node->key)
        {
            node = node->left ;
        }
        else if(key > node->key)
        {
            node = node->right ;
        }
        else
        {
            return node ;
        }
    }

    if (save)
    {
        *save = parent;
    }

    return NULL ;
}


/*-----------------------------------------------------------
  |   node           right
  |   / \    ==>     / \
  |   a  right     node  y
  |       / \       / \    
  |       b  y     a   b    
  -----------------------------------------------------------*/

static rb_node_t* rb_rotate_left(rb_node_t* node, rb_node_t* root)
{
    rb_node_t* right = node->right;			//指定指针指向 right<--node->right

    if ((node->right = right->left))
    {
        right->left->parent = node;			//好比上面的注释图，node成为b的父母
    }
    right->left = node;						//node成为right的左孩子


    if ((right->parent = node->parent))		// set the new parent
    {
        if (node == node->parent->right)
        {
            node->parent->right = right;
        }
        else
        {
            node->parent->left = right;
        }
    }
    else
    {
        root = right;						
    }
    node->parent = right;					//right成为node的父母


    return root;

}



/*-----------------------------------------------------------
  |       node           left
  |       / \            / \
  |    left  y   ==>    a   node
  |   / \               / \
  |  a   b             b   y
  -----------------------------------------------------------*/

static rb_node_t* rb_rotate_right(rb_node_t* node, rb_node_t* root)
{
    rb_node_t* left = node->left;

    if ((node->left = left->right))
    {
        left->right->parent = node;
    }

    left->right = node;

    if ((left->parent = node->parent))
    {
        if (node == node->parent->right)
        {
            node->parent->right = left;
        }
        else
        {
            node->parent->left = left;
        }
    }
    else
    {
        root = left;
    }

    node->parent = left;

    return root;
}


//五、红黑树的3种插入情况
//接下来，咱们重点分析针对红黑树插入的3种情况，而进行的修复工作。
//--------------------------------------------------------------  
//红黑树修复插入的3种情况
//为了在下面的注释中表示方便，也为了让下述代码与我的倆篇文章相对应，
//用z表示当前结点，p[z]表示父母、p[p[z]]表示祖父、y表示叔叔。
//--------------------------------------------------------------
static rb_node_t* rb_insert_rebalance(rb_node_t *node, rb_node_t *root)
{
    rb_node_t *parent, *gparent, *uncle, *tmp;

    //parent 为node的父母，且当父母的颜色为红时
    while ((parent = node->parent) && parent->color == RED)
    {
        gparent = parent->parent;

        if (parent == gparent->left)
        {
            uncle = gparent->right;							//定义叔叔的概念，叔叔y就是父母的右孩子。

            if (uncle && uncle->color == RED)				 //情况1：z的叔叔y是红色的
            {
                uncle->color = BLACK;						//将叔叔结点y着为黑色
                parent->color = BLACK;						//z的父母p[z]也着为黑色。解决z，p[z]都是红色的问题。
                gparent->color = RED;
                node = gparent;
            }
            else                                            //情况2：z的叔叔y是黑色的，
            {
                if (parent->right == node)
                {
                    root = rb_rotate_left(parent, root);
                    //parent和node进行交换，颜色不变
                    tmp = parent;
                    parent = node;
                    node = tmp;
                }
                // parent和gparent进行变色
                parent->color = BLACK;
                gparent->color = RED;
                //再进行旋转
                root = rb_rotate_right(gparent, root);
            }
        } 
        else 
        {
            uncle = gparent->left;

            if (uncle && uncle->color == RED)
            {
                uncle->color = BLACK;
                parent->color = BLACK;
                gparent->color = RED;

                node = gparent;

            }
            else
            {
                if (parent->left == node)
                {
                    root = rb_rotate_right(parent, root);

                    tmp = parent;
                    parent = node;
                    node = tmp;
                }

                parent->color = BLACK;
                gparent->color = RED;

                root = rb_rotate_left(gparent, root);
            }
        }
    }

    root->color = BLACK;

    return root;
}




rb_node_t* st_rbt_insert(RBKey_t key, data_t data, rb_node_t* root)
{
    rb_node_t* parent = NULL , *node = NULL ;


    if((node = rb_search_auxiliary(key, root, &parent)))		//调用rb_search_auxiliary找到插入结
    {
        return root ;
    }

    node = rb_new_node(key, data);
    node->parent = parent ;
    node->left = node->right = NULL ;
    node->color = RED ;

    if(parent)
    {
        if(parent->key > key)
            parent->left = node ;
        else if(parent->key < key)
            parent->right = node ;
    }
    else
    {
        root = node ;
    }

    return rb_insert_rebalance(node, root);						//插入结点后，调用rb_insert_rebalance修复红黑树
}


rb_node_t* st_rbt_search(RBKey_t key, rb_node_t* root)
{
    return rb_search_auxiliary(key, root, NULL);
}


//七、红黑树的4种删除情况
//----------------------------------------------------------------  
//红黑树修复删除的4种情况
//为了表示下述注释的方便，也为了让下述代码与我的倆篇文章相对应，
//x表示要删除的结点，*other、w表示兄弟结点，
//----------------------------------------------------------------  
static rb_node_t* rb_erase_rebalance(rb_node_t *node, rb_node_t *parent, rb_node_t *root)
{
    rb_node_t *other, *o_left, *o_right;						//x的兄弟*other，兄弟左孩子*o_left,*o_right

    // node的颜色是黑色，node=NULL， node不是root
    while ((!node || node->color == BLACK) && node != root)
    {
        if (parent->left == node)
        {
            other = parent->right;
            //情况1：x的兄弟w是红色的
            if (other->color == RED)							
            {
                other->color = BLACK;
                parent->color = RED;							//上俩行，改变颜色，w->黑、p[x]->红。
                root = rb_rotate_left(parent, root);			//再对p[x]做一次左旋
                printf("parent [%d]\n", parent->key);
                other = parent->right;							//x的新兄弟new w 是旋转之前w的某个孩子。其实就是左旋后
            }

            //情况2：x的兄弟w是黑色，且w的俩个孩子也黑色
            if ((!other->left || other->left->color == BLACK) &&
                    (!other->right || other->right->color == BLACK))
            {
                other->color = RED;								//由于w和w的俩个孩子都是黑色的，则在x和w上得去掉一黑色，于是，兄弟w变为红色。
                node = parent;									//p[x]为新结点x
                parent = node->parent;							//x<-p[x]  
            }
            else                                                //情况3：x的兄弟w是黑色的且，w的左孩子是红色，右孩子为黑色。
            {
                if (!other->right || other->right->color == BLACK)
                {
                    if ((o_left = other->left))					//w和其左孩子left[w]，颜色交换。
                    {
                        o_left->color = BLACK;					//w的左孩子变为由黑->红色
                    }

                    other->color = RED;							//w由黑->红
                    root = rb_rotate_right(other, root);		//再对w进行右旋，从而红黑性质恢复。
                    other = parent->right;						//变化后的，父结点的右孩子，作为新的兄弟结点
                }
                //情况4：x的兄弟w是黑色的
                other->color = parent->color;					//把兄弟节点染成当前节点父节点的颜色。
                parent->color = BLACK;							//把当前节点父节点染成黑色

                if (other->right)								//且w的右孩子是红
                {	
                    other->right->color = BLACK;				//兄弟节点w右孩子染成黑色
                }

                root = rb_rotate_left(parent, root);
                node = root;									//并把x置为根。

                break;
            }
        }
        else                                                    //下述情况与上述情况，原理一致。分析略。
        {
            other = parent->left;

            if (other->color == RED)
            {
                other->color = BLACK;
                parent->color = RED;
                root = rb_rotate_right(parent, root);
                other = parent->left;
            }
            //如果uncle的两个child都不存在或者两个孩子都是黑色
            if ((!other->left || other->left->color == BLACK) &&
                    (!other->right || other->right->color == BLACK))
            {
                other->color = RED;				// uncle由黑色变红色
                node = parent;					// node指向parent
                parent = node->parent;			// parent为原来的parent的parent
            }
            else
            {
                if (!other->left || other->left->color == BLACK)
                {
                    if ((o_right = other->right))
                    {
                        o_right->color = BLACK;
                    }

                    other->color = RED;
                    root = rb_rotate_left(other, root);
                    other = parent->left;
                }

                other->color = parent->color;
                parent->color = BLACK;

                if (other->left)
                {
                    other->left->color = BLACK;
                }

                root = rb_rotate_right(parent, root);
                node = root;

                break;
            }
        }
    }

    if (node)
    {
        node->color = BLACK;						//最后将node[上述步骤置为了根结点]，改为黑色。
    } 

    return root;

}

/**
 * 第一步删除节点，先找到需要删除的节点
	rb_node_t* st_rbt_erase(RBKey_t key, rb_node_t *root)
	1 左孩子为空，右孩子为空
	 则 直接删除这个节点。child = NULL， parent为 node的parent。
	 如果node is black ，需要调用调整函数__rb_erase_color(child, parent, root);
	2 左孩子 为空，右孩子不为空，
	  删除的节点为node，child = node->right，parent = node->parent。
	  如果node is black ，需要调用调整函数 __rb_erase_color(child, parent, root);
	3 左孩子存在，右孩子为空
	  删除节点为node， child = node->left,parent = node->parent；
	  如果node is black  调用 调整函数__rb_erase_color(child, parent, root);
	4 左孩子不为空，右孩子也不为空
	 右孩子存在，则寻找node的后继，即寻找右孩子为根的具有最小key的节点。换言之寻找 左孩子的左孩子的左孩子，直到，没有左孩子节点为止。
	node = node->rb_right;
	while ((left = node->rb_left) != NULL)
	node = left;
	child = node->rb_right; 
	node 为入参node的后继， child 为 找到的后继的右孩子（可能为NULL）。
 */
rb_node_t* st_rbt_erase(RBKey_t key, rb_node_t *root)
{
    rb_node_t *child, *parent, *old, *left, *node;

    color_t color;

    if (!(node = rb_search_auxiliary(key, root, NULL)))				//调用rb_search_auxiliary查找要删除的node
    {
        printf("key %d is not exist!\n");

        return root;
    }

    old = node;							// node "old" save the delete node

    // if the node have the rl childen
    if (node->left && node->right)
    {
        node = node->right;						// find the min node at right sub tree ;

        while ((left = node->left) != NULL)
        {
            node = left;
        }

        child = node->right;
        parent = node->parent;
        color = node->color;

        if (child)								// if the right child exist, set the child parent
        {
            child->parent = parent;
        }

        if (parent)
        {
            if (parent->left == node)
            {
                parent->left = child;			// this type is : the node  have left child
            }
            else
            {
                parent->right = child;			// this type is : the node have no left child
            }
        }
        else
        {
            root = child;
        }

        if (node->parent == old)				// this type is : the node have no left child
        {
            parent = node;
        }

        node->parent = old->parent;				// replace
        node->color = old->color;
        node->right = old->right;
        node->left = old->left;

        if (old->parent)						// this type is not root :
        {
            if (old->parent->left == old)		// this type is : left sub tree
            {
                old->parent->left = node;		
            }
            else
            {
                old->parent->right = node;		// this type is : right sub tree
            }
        } 
        else                                    // this type is the node is root :
        {
            root = node;
        }

        old->left->parent = node;				// 给两个孩子从认父亲

        if (old->right)
        {
            old->right->parent = node;
        }
    }
    else                                        // this type is : only one child
    {
        if (!node->left)
        {
            child = node->right;
        }
        else if (!node->right)
        {
            child = node->left;
        }

        parent = node->parent;
        color = node->color;

        if (child)
        {
            child->parent = parent;				// replace parent
        }

        if (parent)								// check whether is root
        {
            if (parent->left == node)
            {
                parent->left = child;
            }
            else
            {
                parent->right = child;
            }
        }
        else
        {
            root = child;
        }
    }

    free(old);									// delete the node

	if(NULL == child)
		printf("NULL, [%d], [%d], [%d]\n", parent->key, root->key, color);
	else
		printf("not null [%d], [%d], [%d]\n", child->key, parent->key, parent->color);

    if (color == BLACK)
    {
        root = rb_erase_rebalance(child, parent, root);
    }

    return root;
}












