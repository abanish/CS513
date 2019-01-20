/*
 * C Program to Construct a Red Black Tree and perform insertion, deletion, level order traversal on it
 */
#include <stdio.h>
#include <stdlib.h>

struct RedBlackNode{
    int key;
    enum {red, black} color;
    struct RedBlackNode *left, *right, *parent;
}*root = NULL, *temp= NULL;

static struct RedBlackNode s = {-1, 1, 0, 0, 0};

#define nil &s
void leftRotate(struct RedBlackNode *t){
    struct RedBlackNode *t_right = t->right;
    if(t_right->left != nil){
        t->right = t_right->left;
    }
    else{
        t->right = nil;
    }
    if(t->right != nil){
        t->right->parent = t;
    }
    if(t->parent != nil){
        t_right->parent = t->parent;
    }
    if(t->parent == nil){
        root=t_right;
    }

    else if(t == t->parent->left){
        t->parent->left = t_right;
    }
    else{
        t->parent->right = t_right;
    }

    t_right->left = t;
    t->parent = t_right;

}

void rightRotate(struct RedBlackNode *t){
    struct RedBlackNode *t_left = t->left;
    if(t_left->right != nil){
        t ->left = t_left->right;
    }
    else{
        t->left = nil;
    }
    if(t->left != nil){
        t->left->parent = t;
    }
    if(t->parent != nil){
        t_left->parent = t->parent;
    }
    if(t->parent == nil){
        root = t_left;
    }
    else if(t == t->parent->right){
        t->parent->right = t_left;
    }
    else{
        t->parent->left = t_left;
    }
    t_left ->right =t;
    t->parent = t_left;
}

void insert();
void levelOrder();
void create();
void searchToInsert();
void rbInsertFixup();
int height();
void printGivenLevel();
void deletion();
void delfix();
struct RedBlackNode* successor();
void searchRBT();
void minimumRBT();
void maximumRBT();
void successorRBT();
void predecessorRBT();
void deleter();

void main(){
    printf("********************************************************\n");
    printf("==========RED BLACK TREE IMPLEMENTATION CS513===========\n");
    printf("********************************************************\n");

    while(1){
        printf("\nOperations implemented on the Red Black Tree. :\n\n ");
        printf("\t1. Insertion\n");
        printf("\t2. Deletion\n");
        printf("\t3. Search\n");
        printf("\t4. Find Minimum\n");
        printf("\t5. Find Maximum\n");
        printf("\t6. Find Successor\n");
        printf("\t7. Find Predecessor\n");
        printf("\t8. Level Order Traversal\n");
        printf("\t9. Exit\n");
        int ch;
         printf("\n\nEnter your choice:\n ");
        scanf("%d", &ch);
        switch(ch){
            case 1: insert();
                    break;
            case 2: deletion();
                    break;
            case 3: searchRBT();
                    break;
            case 4: minimumRBT();
                    break;
            case 5: maximumRBT();
                    break;
            case 6: successorRBT();
                    break;
            case 7: predecessorRBT();
                    break;
            case 8: levelOrder(root);
                    break;
            case 9: exit(1);
                    break;
            default:
                    printf("Wrong Choice, pleas select again\n");
                    break;
        }
    }
}

/*Insert node in Red Black Tree*/
void insert(){
    create();
    if(root == NULL){
        root = temp;
    }
    else{
        searchToInsert(root);
    }
    rbInsertFixup(temp);
    printf("Red Black Insertion Fixup is Finished\n");
    printf("Insertion finished\n");
}

/*create the node*/
void create(){
    int data;
    printf("\nEnter the data you want to insert:\n\n");
    scanf("%d",&data);
    temp = (struct RedBlackNode*) malloc(1* sizeof(struct RedBlackNode));
    temp->key = data;
    temp->color = red;
    temp->left = temp->right = temp->parent = nil;

}

/*search the element to insert*/
void searchToInsert(struct RedBlackNode *t){
    if((temp->key < t->key) && (t->left != nil))
        searchToInsert(t->left);
    else if((temp->key < t->key) && (t->left == nil)){
        t->left = temp;
        printf("Inserted node to left of %d\n",t->key);
        temp->parent = t;
        printf("Parent of the node is %d\n ",t->key);
    }
    else if((temp->key > t->key) && (t->right != nil))
        searchToInsert(t->right);
    else{

        t->right = temp;
        printf("Inserted node to right of %d\n",t->key);
        temp->parent = t;
        printf("Parent of the node is %d \n",t->key);
    }
}


void rbInsertFixup(struct RedBlackNode *t){
    printf("Red Black Insertion Fixup Initialized...\n");

    struct RedBlackNode *parent_pt = nil;
    struct RedBlackNode *grand_parent = nil;
    while((t != root) && (t->color != black) && (t->parent->color == red)){

            parent_pt = t->parent;
            grand_parent = t->parent->parent;

            /*Case A: Parent is left child of grand parent*/
            if(parent_pt == grand_parent->left ){

                struct RedBlackNode *uncle = grand_parent->right;


                /*Case 1 the uncle pointer is red, only coloring required*/
                if((uncle != nil) && (uncle->color == red)){
                    parent_pt->color = black;
                    uncle->color = black;
                    grand_parent->color = red;
                    t=grand_parent;
                }

                else
                {
                    /*Case 2 node t is right child of its parent. Left rotation required*/
                    printf("Uncle is black\n");
                    if(t == parent_pt->right){
                        leftRotate(parent_pt);
                        t = parent_pt;
                        parent_pt = t ->parent;
                    }

                    /*Case 3: node t is left child of its parent and case 3 always follows case 2*/

                    rightRotate(grand_parent);
                    t->parent->color = black;
                    t->parent->parent->color = red;
                    t = parent_pt;
                }

            }
            /*Case B: parent of pt is right child of grand-parent of pt*/
            else{
                printf("Parent is on the right side of grand parent\n");
                struct RedBlackNode *uncle = grand_parent->left;

                /*Case 1: The uncle pt is red*/
                if((uncle != NULL) && (uncle->color == red)){
                    parent_pt->color = black;
                    uncle->color = black;
                    grand_parent->color = red;
                    t=t->parent->parent;
                }

                else{
                    /*case 2: t is left child of parent*/
                    if(t == parent_pt->left){
                        rightRotate(parent_pt);
                        t= parent_pt;

                    }

                    /*case 3 t is the right child of parent*/

                    leftRotate(grand_parent);
                    t->parent->color= black;
                    t->parent->parent->color = red;
                    t = parent_pt;
                }

            }
    }
    /*Root is always black in Red Black Tree*/
    printf("Setting root color to black\n");
    root->color = black;

}

/*level order traversal of Red Black Tree*/
void levelOrder(struct RedBlackNode *t)
{
    printf("Printing elements in level order traversal \n");
    if(root == NULL){
        printf("EMPTY TREE\n");
    }
    int h = height(t);
    int i;
    for (i = 1; i<=h; i++)
        printGivenLevel(t, i);
    printf("\n\n Note: -1 denotes nil nodes\n\n");
}

void printGivenLevel(struct RedBlackNode *t, int level){
    if (t == NULL)
        return;
    if (level == 1){
        printf("%d ", t->key);
        if(t->color == black){
            printf("(BLACK)\t");
        }
        else{
            printf("(RED)\t");
        }
    }
    else if (level > 1)
    {
        printGivenLevel(t->left, level-1);
        printGivenLevel(t->right, level-1);
    }
}

int height(struct RedBlackNode * t){
    if (t==NULL)
        return 0;
    else
    {
        /* compute the height of each subtree */
        int lheight = height(t->left);
        int rheight = height(t->right);

        /* use the larger one */
        if (lheight > rheight)
            return(lheight+1);
        else return(rheight+1);
    }
}

void deletion(){
    if(root == NULL){
        printf("EMPTY TREE\n");
        return;
    }
    int x;
    printf("Enter the key of the node to be deleted\n");
    scanf("%d",&x);
    struct RedBlackNode *t = root;
    struct RedBlackNode *s = NULL;
    struct RedBlackNode *r = NULL;

    int found = 0;
    //search the element in the red black tree
    while( t != NULL && found == 0){
        if(t->key == x){
            found = 1;
        }
        if(found ==0){
            if(t->key <x)
                t = t->right;
            else
                t = t->left;
        }
    }

    if(found == 0)
    {
        printf("\nElement not found\n");
        return;
    }
    else{
        printf("Element found \n");
        printf("Element to be deleted: %d\n",t->key);
        printf("Color: ");
        if(t->color==black){
            printf("Black\n");
        }
        else{
            printf("Red\n");
        }

        deleter(t);

}
printf("Deletion Completed!\n");
}

void deleter(struct RedBlackNode* z){
    struct RedBlackNode * x, *y;

    if (z->left == nil || z->right == nil) {
        y = z;
    } else {
        y = successor(z);
    }

    if (y->left != nil) {
        x = y->left;
    } else {
        x = y->right;
    }


    x->parent = y->parent;

    if (y->parent == nil) {
        root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    if (y != z) {
        z->key = y->key;
    }

    if (y->color == black) {
        printf("Deletion fix initialized\n");
        //delfix(x);
        printf("Deletion fix Completed");
    }
}

//fix red black tree violations after deletion
void delfix(struct RedBlackNode *p)
{
     while (p!= root && p->color == black) {
        if (p == p->parent->left) {
            struct RedBlackNode * w = p->parent->right;
            if (w->color == red) {
                w->color = black;
                p->parent->color = red;
                leftRotate(p->parent);
                w = p->parent->right;
            }

            if (w->left->color == black && w->right->color == black) {
                w->color = red;
                p = p->parent;
            } else if (w->right->color == black) {
                w->left->color = black;
                w->color = red;
                rightRotate(w);
                w = p->parent->right;
            } else {
                w->color = p->parent->color;
                p->parent->color = black;
                w->right->color = black;
                leftRotate(p->parent);
                p = root;
            }
        } else {
            struct RedBlackNode* w = p->parent->left;
            if (w->color == red) {
                w->color = black;
                p->parent->color = red;
                rightRotate(p->parent);
                w = p->parent->left;
            }

            if (w->left->color == black && w->right->color == black) {
                w->color = red;
                p = p->parent;
            } else if (w->left->color == black) {
                w->left->color = black;
                w->color = red;
                leftRotate(w);
                w = p->parent->left;
            } else {
                w->color = p->parent->color;
                p->parent->color = black;
                w->left->color = black;
                rightRotate(p->parent);
                p = root;
            }
        }
    }
    p->color = black;

}



/*find succesor for deletion*/
struct RedBlackNode* successor(struct RedBlackNode *t){
    struct RedBlackNode *y = NULL;
    if(t->left != NULL)
    {
        y = t->left;
        while(y->right != NULL)
            y = y->right;
    }
    else{
        y=t->right;
        while(y->left != NULL)
            y = y->left;
    }
    return y;
}

/*search element in Red Black Tree*/
void searchRBT(){
    if(root == NULL)
    {
        printf("\nEmpty Tree\n");
        return;
    }
    int x;
    printf("\nEnter key of the node to be searched\n");
    scanf("%d",&x);
    struct RedBlackNode *t = root;
    int found = 0;
    while(t != NULL && found == 0)
    {
        if(t->key == x)
            found = 1;
        if(found == 0)
        {
            if(t->key<x)
                t= t->right;
            else
                t=t->left;
        }
    }
    if(found == 0)
        printf("\nElement not found\n");
    else
    {
        printf("\n\tFound Node:");
        printf("\n\t Key: %d", t->key);
        printf("\n\t Color: ");
        if(t->color == black)
            printf("Black\n");
        if(t->color == red)
            printf("Red\n");

    }

}

/*minimum element in Red Black Tree*/
void minimumRBT(){
    if(root == NULL){
        printf("\nEmpty Tree\n");
        return;
    }
    struct RedBlackNode *t = root;
    if(t->left == nil)
        printf("Minimum element in the Red Black Tree is %d\n", t->key);
    else{
        while(t->left != nil){
            t= t->left;
        }
        printf("Minimum element in the Red Black Tree is %d\n", t->key);
    }

}

/*maximum element in Red Black Tree*/
void maximumRBT(){
    if(root == nil){
        printf("\nEmpty Tree\n");
        return;
    }
    struct RedBlackNode *t = root;
    if(t->right == nil)
        printf("Maximum element in the Red Black Tree is %d", t->key);
    else{
        while(t->right != nil){
            t= t->right;
        }
        printf("Maximum element in the Red Black Tree is %d\n", t->key);
    }
}

/*predecessor in Red Black Tree*/
void predecessorRBT(){
    if(root == NULL){
        printf("\nEmpty Tree\n");
        return;
    }
    int x;
    printf("\nEnter key of the node for which predecessor is to be searched\n");
    scanf("%d",&x);
    struct RedBlackNode *t = root;
    struct RedBlackNode *y = NULL;
    struct RedBlackNode *pre = NULL;
    while(t != nil){

        if(t->key == x ){
            if(t->left != nil)
            {
                y = t->left;
                while(y->right != nil)
                    y = y->right;
                pre = y;
            }

            break;
        }
        if(t->key < x){
            pre = t;
            t = t ->right;
        }
        else
            break;

    }
    if(pre != nil)
        printf("Predecessor is : %d\n", pre->key);
    else
        printf("\nPredecessor not found for the element\n");
}

/*successor in Red Black Tree*/
void successorRBT(){
    if(root == NULL){
        printf("\nEmpty Tree\n");
        return;
    }
    int x;

    printf("\nEnter key of the node for which successor is to be searched\n");
    scanf("%d",&x);
    struct RedBlackNode *t = root;
    struct RedBlackNode *y = NULL;
    struct RedBlackNode *suc = NULL;

    while(t != nil){

        if(t->key == x ){
            if(t->right != nil)
            {
                y = t->right;
                while(y->left != nil)
                    y = y->left;
                suc = y;
            }
            break;
        }
        if(t->key > x){
            suc = t;
            t = t ->left;
        }
        else
            break;
    }
    if(suc != nil)
        printf("\nSuccessor is : %d\n", suc->key);
    else
        printf("\n No successor found for given element\n");
}
