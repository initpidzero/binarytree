#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct tree {
        int value;
        struct tree *left;
        struct tree *right;
};

/* Get started on tree
 * in: tree - binary tree to be initalised
 * out: tree - initalised binary tree
 * return: 0 on success, 1 on failure
 * */
int init_tree(struct tree **tree, int value)
{
        *tree = (struct tree *)malloc(sizeof(struct tree));
        if(!(*tree) || errno)
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

int main(int argc, char **argv)
{
        struct tree *btree = NULL;
        int i = 0;
        for (; i < 10; i++) {
                int r = rand();
                populate_tree(&btree, r);
        }
        return 0;
}
