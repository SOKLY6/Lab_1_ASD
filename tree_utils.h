#ifndef TREE_UTILS_H
#define TREE_UTILS_H

typedef struct Node{
    struct Node *parent;
    int value;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct Tree{
    Node *root;
    int(*cmp)(int, int);
} Tree;

Tree * tree_init(void);
int insert_node(Tree *tree, int value);
void print_tree(const Node *root, int level);
int delete_node(Tree *tree, int value);
void get_depth(const Node *root, size_t current_depth, size_t *depth);
void destroy_root(Node *root);
void destroy_tree(Tree *tree);

#endif