#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct tree {
        int value;
        struct tree *left;
        struct tree *right;
};

struct depth {
        struct tree *tree;
        unsigned char left;
        unsigned char right;
};

struct depth depth;

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
                printf("%*c%d\n", spaces, ' ', tree->value);
                if (tree->left) {
                        printf("%*c/\n", spaces,' ');
                        printf("%*c", spaces / 2,' ');
                        print_tree(tree->left, spaces / 2);
                }
                if (tree->right) {
                        printf("%*c\\\n", spaces + spaces / 2, ' ');
                        printf("%*c", spaces + spaces / 2, ' ');
                        print_tree(tree->right, spaces);
                }
        }

        return;
}

/* remove node from tree
 * in: tree
 * in: value
 * out: tree
 * return 0 or 1
 */
int remove_tree_node(struct tree *tree, int value)
{
        struct tree *parent = NULL;
        parent = NULL;

        return 0;
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

/* Add a tree node
 * in: tree - binary tree to be initalised
 * out: tree - initalised binary tree
 * return: 0 on success, 1 on failure
 * */
int add_tree_node(struct tree **tree, int value)
{
        *tree = (struct tree *)malloc(sizeof(struct tree));
        if (!(*tree) || errno)
                fprintf(stderr, "malloc failed: %s", strerror(errno));
        memset(*tree, 0, sizeof(struct tree));
        (*tree)->left = NULL;
        (*tree)->right = NULL;
        (*tree)->value = value;
        return 0;
}

/*
 * in: tree - binary tree to be initalised
 * out: tree - initalised binary tree
 * return: 0 on success, 1 on failure
 */
int populate_tree(struct tree **tree, int value)
{
        if(*tree == NULL)
                add_tree_node(tree, value);
        else
                if((*tree)->value > value)
                        populate_tree(&((*tree)->left), value);
                else
                        populate_tree(&((*tree)->right), value);
        return 0;
}

/*
 */
int tree_traversal(struct tree *tree)
{
        struct tree *temp = tree;

        while (temp) {
                if (temp->left) {
                        depth.left++;
                        tree_traversal(temp->left);
                }
                if (temp->right) {
                        depth.right++;
                        tree_traversal(temp->right);
                }
                break;
        }

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

int main(int argc, char *argv[])
{
        (void )argc;
        (void )argv;
        struct tree *btree = NULL;
        int i = 0;

        for (; i < 11; i++) {
                int r = rand() % 100;
                populate_tree(&btree, r);
        }
        depth.left = 0;
        depth.right = 0;
        tree_traversal(btree);

        //print_tree(btree, 10);
        inorder(btree);
        printf("depth left = %d depth = right = %d\n", depth.left, depth.right);
        printf("min = %d max = %d\n", tree_min(btree)->value, tree_max(btree)->value);
        free(btree);
        return 0;
}
