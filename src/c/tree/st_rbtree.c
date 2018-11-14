#include <stdio.h>
#include <malloc.h>
#include "st_rbtree.h"
#include "st_log.h"


/*	ȫ�ֱ�������	*/

extern RBNode * RBNullNode ;
extern RBNode * Current, * Sibling, * Parent, * GrParent, * GrGrParent ;


/*	�ֲ���������	*/

static RBNode * singleRotateWithLeft (RBNode * const parent) ;
static RBNode * singleRotateWithRight (RBNode * const parent) ;
static RBNode * rotate (RBNode * const parent, const RBItem item) ;
static void handleReorient (pRBTree * const prbt, const RBItem item) ;
static void changeColor (void) ;
static void traversal (const RBNode * const pn, void (* pfun) (const RBNode * const pn)) ;
static void release (RBNode * const pn) ;


/*	�ӿں�������	*/

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
        if (item < Current->item)			//���ж��ֲ���
            Current = Current->left ;
        else
            Current = Current->right ;
        /*����ڲ�����������У������������Ǻ�ɫ����Ҫ����Ӧ����,��Ϊ����Ӧ���ƻ�����3,4*/
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

/*	�ֲ���������	*/

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
    /*����������Ӷ��Ǻ�ɫ����current��child���л�ɫ*/
    Current->color = Red ;
    Current->left->color = Current->right->color = Black ;

    if (Red == Parent->color)	
    {
        /*��������Ǻ�ɫ������үүΪ��ɫ*/
        GrParent->color = Red ;	
        /*�ж���֮���ͻ���һ������ת,�����֮���Σ���ת����*/
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

/* �ͷ�node�µ����� */
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

//������������ҽ��
//----------------------------------------------------  
//rb_search_auxiliary������
//rb_node_t* rb_search�������ҵ��Ľ��
//----------------------------------------------------
static rb_node_t* rb_search_auxiliary(RBKey_t key, rb_node_t* root, rb_node_t** save)
{
    rb_node_t *node = root, *parent = NULL;

    int ret;

    while(node)
    {
        parent = node ;
        // ���ֲ��Һ��ʵĲ����
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
    rb_node_t* right = node->right;			//ָ��ָ��ָ�� right<--node->right

    if ((node->right = right->left))
    {
        right->left->parent = node;			//�ñ������ע��ͼ��node��Ϊb�ĸ�ĸ
    }
    right->left = node;						//node��Ϊright������


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
    node->parent = right;					//right��Ϊnode�ĸ�ĸ


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


//�塢�������3�ֲ������
//�������������ص������Ժ���������3������������е��޸�������
//--------------------------------------------------------------  
//������޸������3�����
//Ϊ���������ע���б�ʾ���㣬ҲΪ���������������ҵĂzƪ�������Ӧ��
//��z��ʾ��ǰ��㣬p[z]��ʾ��ĸ��p[p[z]]��ʾ�游��y��ʾ���塣
//--------------------------------------------------------------
static rb_node_t* rb_insert_rebalance(rb_node_t *node, rb_node_t *root)
{
    rb_node_t *parent, *gparent, *uncle, *tmp;

    //parent Ϊnode�ĸ�ĸ���ҵ���ĸ����ɫΪ��ʱ
    while ((parent = node->parent) && parent->color == RED)
    {
        gparent = parent->parent;

        if (parent == gparent->left)
        {
            uncle = gparent->right;							//��������ĸ������y���Ǹ�ĸ���Һ��ӡ�

            if (uncle && uncle->color == RED)				 //���1��z������y�Ǻ�ɫ��
            {
                uncle->color = BLACK;						//��������y��Ϊ��ɫ
                parent->color = BLACK;						//z�ĸ�ĸp[z]Ҳ��Ϊ��ɫ�����z��p[z]���Ǻ�ɫ�����⡣
                gparent->color = RED;
                node = gparent;
            }
            else                                            //���2��z������y�Ǻ�ɫ�ģ�
            {
                if (parent->right == node)
                {
                    root = rb_rotate_left(parent, root);
                    //parent��node���н�������ɫ����
                    tmp = parent;
                    parent = node;
                    node = tmp;
                }
                // parent��gparent���б�ɫ
                parent->color = BLACK;
                gparent->color = RED;
                //�ٽ�����ת
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


    if((node = rb_search_auxiliary(key, root, &parent)))		//����rb_search_auxiliary�ҵ������
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

    return rb_insert_rebalance(node, root);						//������󣬵���rb_insert_rebalance�޸������
}


rb_node_t* st_rbt_search(RBKey_t key, rb_node_t* root)
{
    return rb_search_auxiliary(key, root, NULL);
}


//�ߡ��������4��ɾ�����
//----------------------------------------------------------------  
//������޸�ɾ����4�����
//Ϊ�˱�ʾ����ע�͵ķ��㣬ҲΪ���������������ҵĂzƪ�������Ӧ��
//x��ʾҪɾ���Ľ�㣬*other��w��ʾ�ֵܽ�㣬
//----------------------------------------------------------------  
static rb_node_t* rb_erase_rebalance(rb_node_t *node, rb_node_t *parent, rb_node_t *root)
{
    rb_node_t *other, *o_left, *o_right;						//x���ֵ�*other���ֵ�����*o_left,*o_right

    // node����ɫ�Ǻ�ɫ��node=NULL�� node����root
    while ((!node || node->color == BLACK) && node != root)
    {
        if (parent->left == node)
        {
            other = parent->right;
            //���1��x���ֵ�w�Ǻ�ɫ��
            if (other->color == RED)							
            {
                other->color = BLACK;
                parent->color = RED;							//�����У��ı���ɫ��w->�ڡ�p[x]->�졣
                root = rb_rotate_left(parent, root);			//�ٶ�p[x]��һ������
                printf("parent [%d]\n", parent->key);
                other = parent->right;							//x�����ֵ�new w ����ת֮ǰw��ĳ�����ӡ���ʵ����������
            }

            //���2��x���ֵ�w�Ǻ�ɫ����w����������Ҳ��ɫ
            if ((!other->left || other->left->color == BLACK) &&
                    (!other->right || other->right->color == BLACK))
            {
                other->color = RED;								//����w��w���������Ӷ��Ǻ�ɫ�ģ�����x��w�ϵ�ȥ��һ��ɫ�����ǣ��ֵ�w��Ϊ��ɫ��
                node = parent;									//p[x]Ϊ�½��x
                parent = node->parent;							//x<-p[x]  
            }
            else                                                //���3��x���ֵ�w�Ǻ�ɫ���ң�w�������Ǻ�ɫ���Һ���Ϊ��ɫ��
            {
                if (!other->right || other->right->color == BLACK)
                {
                    if ((o_left = other->left))					//w��������left[w]����ɫ������
                    {
                        o_left->color = BLACK;					//w�����ӱ�Ϊ�ɺ�->��ɫ
                    }

                    other->color = RED;							//w�ɺ�->��
                    root = rb_rotate_right(other, root);		//�ٶ�w�����������Ӷ�������ʻָ���
                    other = parent->right;						//�仯��ģ��������Һ��ӣ���Ϊ�µ��ֵܽ��
                }
                //���4��x���ֵ�w�Ǻ�ɫ��
                other->color = parent->color;					//���ֵܽڵ�Ⱦ�ɵ�ǰ�ڵ㸸�ڵ����ɫ��
                parent->color = BLACK;							//�ѵ�ǰ�ڵ㸸�ڵ�Ⱦ�ɺ�ɫ

                if (other->right)								//��w���Һ����Ǻ�
                {	
                    other->right->color = BLACK;				//�ֵܽڵ�w�Һ���Ⱦ�ɺ�ɫ
                }

                root = rb_rotate_left(parent, root);
                node = root;									//����x��Ϊ����

                break;
            }
        }
        else                                                    //������������������ԭ��һ�¡������ԡ�
        {
            other = parent->left;

            if (other->color == RED)
            {
                other->color = BLACK;
                parent->color = RED;
                root = rb_rotate_right(parent, root);
                other = parent->left;
            }
            //���uncle������child�������ڻ����������Ӷ��Ǻ�ɫ
            if ((!other->left || other->left->color == BLACK) &&
                    (!other->right || other->right->color == BLACK))
            {
                other->color = RED;				// uncle�ɺ�ɫ���ɫ
                node = parent;					// nodeָ��parent
                parent = node->parent;			// parentΪԭ����parent��parent
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
        node->color = BLACK;						//���node[����������Ϊ�˸����]����Ϊ��ɫ��
    } 

    return root;

}

/**
 * ��һ��ɾ���ڵ㣬���ҵ���Ҫɾ���Ľڵ�
	rb_node_t* st_rbt_erase(RBKey_t key, rb_node_t *root)
	1 ����Ϊ�գ��Һ���Ϊ��
	�0�2�� ֱ��ɾ������ڵ㡣child = NULL�� parentΪ node��parent��
	�0�2���node is black ����Ҫ���õ�������__rb_erase_color(child, parent, root);
	2 ���� Ϊ�գ��Һ��Ӳ�Ϊ�գ�
	�0�2 ɾ���Ľڵ�Ϊnode��child = node->right��parent = node->parent��
	�0�2 ���node is black ����Ҫ���õ��������0�2__rb_erase_color(child, parent, root);
	3 ���Ӵ��ڣ��Һ���Ϊ��
	�0�2 ɾ���ڵ�Ϊnode�� child = node->left,parent = node->parent��
	�0�2 ���node is black �0�2���� ��������__rb_erase_color(child, parent, root);
	4 ���Ӳ�Ϊ�գ��Һ���Ҳ��Ϊ��
	�0�2�Һ��Ӵ��ڣ���Ѱ��node�ĺ�̣���Ѱ���Һ���Ϊ���ľ�����Сkey�Ľڵ㡣����֮Ѱ�� ���ӵ����ӵ����ӣ�ֱ����û�����ӽڵ�Ϊֹ��
	node = node->rb_right;
	while ((left = node->rb_left) != NULL)
	node = left;
	child = node->rb_right;�0�2
	node Ϊ���node�ĺ�̣� child Ϊ �ҵ��ĺ�̵��Һ��ӣ�����ΪNULL����
 */
rb_node_t* st_rbt_erase(RBKey_t key, rb_node_t *root)
{
    rb_node_t *child, *parent, *old, *left, *node;

    color_t color;

    if (!(node = rb_search_auxiliary(key, root, NULL)))				//����rb_search_auxiliary����Ҫɾ����node
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

        old->left->parent = node;				// ���������Ӵ��ϸ���

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












