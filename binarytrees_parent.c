#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* binary tree with parent node */
struct tree {
        int value;
        struct tree *left;
        struct tree *right;
        struct tree *parent;
};

struct depth {
        struct tree *tree;
        unsigned char left;
        unsigned char right;
};

/* Find node with the key
 * in: tree: root of the tree
 * in: key: key to match the node
 * return the node with corresponding key value
 */
static struct tree *tree_traversal(struct tree *tree, int key)
{
        struct tree *temp = tree;

        while (temp && temp->value != key) {
                if (key < temp->value) {
                        temp = temp->left;
                } else {
                        temp = temp->right;
                }
        }

        return temp;
}

struct depth depth;
#define TOTALNODES 10
/* in order print */
static void inorder(struct tree *tree)
{
        if (tree) {
                inorder(tree->left);
                printf("%d\n", tree->value);
                inorder(tree->right);
        }
}

/* pre-order traversal here */
static void print_tree(struct tree *tree, int spaces)
{
        if (tree) {
                spaces = spaces + TOTALNODES;
                printf("%*c%d\n", spaces - TOTALNODES, ' ', tree->value);
                if (tree->left) {
                        print_tree(tree->left, spaces);
                }
                if (tree->right) {
                        print_tree(tree->right, spaces);
                }
        }

        return;
}

/* replace u with v */
static void transplace(struct tree *tree, struct tree *u, struct tree *v)
{
        if (tree == NULL)
                return;
        if (u == tree) {
                v = u;
                v->parent = NULL;
        }
        v->parent = u->parent;
        if ( u->parent->left == u)
                u->parent->left = v;
        else
                u->parent->right = v;

}

/* Find maximum node in tree
 * in: tree to find maximum node
 * return: adress of node with maximum key value
 * */
static struct tree *tree_max(struct tree *tree)
{
        struct tree *temp = tree;
        while (temp->right)
                temp = temp->right;

        return temp;
}

/* Find minimum node in tree
 * in: tree to find minimum node
 * return: adress of node with minimum key value
 * */
static struct tree *tree_min(struct tree *tree)
{
        struct tree *temp = tree;
        while (temp->left)
                temp = temp->left;

        return temp;
}

/* find successor, biggest element since this node */
static struct tree *successor(struct tree *node)
{
        struct tree *succ;
        struct tree *temp = node;

        if(node->right) {
                succ = tree_min(node->right);
                return succ;
        }

        succ = node->parent;
        while (succ && temp == succ->right) { /* if it is right child */
                temp = succ;
                succ = succ->parent;

        }
        return succ;
}

/* find predecessor, smallest element since this node */
static struct tree *predecessor(struct tree *node)
{
        struct tree *pred;
        struct tree *temp = node;
        if (node->left) {
                pred = tree_max(node->left);
                return pred;
        }
        pred = node->parent;
        while (pred && temp == pred->left) { /* if it is a left child */
                temp = pred;
                pred = pred->parent;
        }
        return pred;
}

/* remove node from tree
 * in: tree
 * in: value
 * out: tree
 * return 0 or 1
 */
int remove_tree_node(struct tree *tree, int value)
{
        struct tree *node = tree_traversal(tree, value);
        if (node == NULL)
                return -1;

        if (node->left == NULL)
               transplace(tree, node, node->right);
        else if (node->right == NULL)
               transplace(tree, node, node->left);
        else {
                struct tree *succ = tree_min(node->right);
                if (succ->parent != node) {
                        transplace(tree, succ, succ->right);
                        succ->right= node->right;
                        succ->right->parent = node->parent;
                }
                transplace(tree, node, succ);
                succ->left = node->left;
                succ->left->parent = succ;
        }
        free(node);
        return 0;
}

/* Add a tree node
 * in: tree - binary tree to be initalised
 * out: tree - initalised binary tree
 * return: 0 on success, 1 on failure
 * */
int add_tree_node(struct tree **tree, int value, struct tree *parent)
{
        *tree = (struct tree *)malloc(sizeof(struct tree));
        if (!(*tree) || errno)
                fprintf(stderr, "malloc failed: %s", strerror(errno));
        memset(*tree, 0, sizeof(struct tree));
        (*tree)->left = NULL;
        (*tree)->right = NULL;
        (*tree)->value = value;
        (*tree)->parent = parent;
        return 0;
}

/*
 * in: tree - binary tree to be initalised
 * out: tree - initalised binary tree
 * return: 0 on success, 1 on failure
 */
int populate_tree(struct tree **tree, int value, struct tree *parent)
{
        if(*tree == NULL)
                add_tree_node(tree, value, parent);
        else
                if((*tree)->value > value)
                        populate_tree(&((*tree)->left), value, *tree);
                else
                        populate_tree(&((*tree)->right), value, *tree);
        return 0;
}
/* Free the tree node, if it doesn't have any branches
 * in: tree - tree node
 **/
void free_tree(struct tree *tree)
{
        if (tree) {
               if (!(tree->left) && !(tree->right))
                       free(tree);
               else if (tree->left)
                       free_tree(tree->left);
               else if (tree->right)
                       free_tree(tree->right);
        }
        return;
}

static void test_ps(struct tree *tree, int key)
{

        struct tree *temp =  tree_traversal(tree, key);
        if (temp) {
                temp = predecessor(temp);
        }
        if (temp)
                printf("pred of %d is %d\n", key, temp->value);
        else
                printf("pred of %d is %d\n", key, 0);

        temp =  tree_traversal(tree, key);
        if (temp) {
                temp = successor(temp);
        }
        if (temp)
                printf("succ of %d is %d\n", key, temp->value);
        else
                printf("succ of %d is %d\n", key, 0);
}

int main(int argc, char *argv[])
{
        (void )argc;
        (void )argv;
        struct tree *btree = NULL;
        int i = 0;
        int test;

        for (; i < TOTALNODES; i++) {
                int r = rand() % 100;
                populate_tree(&btree, r, NULL);
                if(i == 3) test = r;
        }
        depth.left = 0;
        depth.right = 0;

        print_tree(btree, 0);
        inorder(btree);
        printf("depth left = %d depth = right = %d\n", depth.left, depth.right);
        printf("min = %d max = %d\n", tree_min(btree)->value, tree_max(btree)->value);
        test_ps(btree, test);
        remove_tree_node(btree, test);
        print_tree(btree, 0);
        free(btree);
        return 0;
}
