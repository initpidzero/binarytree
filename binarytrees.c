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
        unsigned char left;
        unsigned char right;
};

struct depth depth;

static void print_tree(struct tree *tree, int spaces)
{
        if (tree) {
                printf("%*c%d\n", spaces / 2, ' ', tree->value);
                if (tree->left) {
                        printf("%*c/", spaces / 2,' ');
                        print_tree(tree->left, spaces / 2);
                }
                if (tree->right) {
                        printf("%*c\\", spaces + spaces / 2, ' ');
                        print_tree(tree->right, spaces / 2);
                }
        }

        return;
}

/* Get started on tree
 * in: tree - binary tree to be initalised
 * out: tree - initalised binary tree
 * return: 0 on success, 1 on failure
 * */
int init_tree(struct tree **tree, int value)
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
                init_tree(tree, value);
        else
                if((*tree)->value < value)
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

        for (; i < 10; i++) {
                int r = rand() % 100;
                populate_tree(&btree, r);
        }
        depth.left = 0;
        depth.right = 0;
        tree_traversal(btree);

        print_tree(btree, 10);
        printf("depth left = %d depth = right = %d", depth.left, depth.right);
        free(btree);
        return 0;
}
