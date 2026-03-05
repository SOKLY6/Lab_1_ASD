#include <stdio.h>
#include <stdlib.h>
#include "tree_utils.h"
#include "comparators.h"

Tree * tree_init(void){
    Tree *tree = malloc(sizeof(Tree));

    if (tree == NULL) {
        return NULL;
    }
    tree->root = NULL;
    tree->cmp = compare_value;
    return tree;
}

int insert_node(Tree *tree, int value){
    Node *current = tree->root;
    Node *parent = NULL;
    int result;
    while (current != NULL) {
        parent = current;
        result = tree->cmp(value, current->value);
        if (result >= 0){
            current = current->right;
        } else if (result < 0) {
            current = current->left;
        }
    }
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL){
        return 1;
    }
    new_node->parent = parent;
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    current = new_node;
    return 0;
}

void print_tree(const Node *root, int level){
    if (root == NULL) {
        return;
    }
    printf("%*s", level * 4, "");
    printf("%d\n", root->value);
    print_tree(root->left, level + 1);
    print_tree(root->right, level + 1);
}

int delete_node(Tree *tree, int value){
    Node *current = tree->root;
    int result;
    while (current != NULL) {
        result = tree->cmp(value, current->value);
        if (result == 0){
            break;
        }
        else if (result > 0){
            current = current->right;
        } else if (result < 0) {
            current = current->left;
        }
    }
    if (current == NULL) {
        return 1;
    }
    if (current->left == NULL && current->right == NULL) {
        if (current->parent == NULL) {
            tree->root = NULL;
        } else if (current->parent->left == current) {
            current->parent->left = NULL;
        } else {
            current->parent->right = NULL;
        }
        free(current);
    } else if (current->left != NULL && current->right == NULL){
        if (current->parent == NULL) {
            tree->root = current->left;
            current->left->parent = NULL;
        } else if (current->parent->left == current) {
            current->parent->left = current->left;
            current->left->parent = current->parent;
        } else if (current->parent->right == current) {
            current->parent->right = current->left;
            current->right->parent = current->parent;
        }
        free(current);
    } else if (current->left == NULL && current->right != NULL){
        if (current->parent == NULL) {
            tree->root = current->right;
            current->right->parent = NULL;
        } else if (current->parent->left == current) {
            current->parent->left = current->right;
            current->right->parent = current->parent;
        } else if (current->parent->right == current) {
            current->parent->right = current->right;
            current->right->parent = current->parent;
        }
        free(current);
    } else if (current->left != NULL && current->right != NULL){
        Node *swap = current->right;
        while (swap->left != NULL) {
            swap = swap->left;
        }
        if (swap->right != NULL) {
            swap->parent->left = swap->right;
            swap->right->parent = swap->parent;
        } else {
            swap->parent->left = NULL;
        }
        Node *temp = current->left;
        current->left = swap->left;
        swap->left = temp;

        temp = current->right;
        current->right = swap->right;
        swap->right = temp;

        temp = current->parent;
        current->parent = swap->parent;
        swap->parent = temp;

        free(current);
    }
    return 0;
}

void get_depth(const Node *root, size_t current_depth, size_t *depth){

    if (root->left == NULL && root->right == NULL) {
        if (current_depth > *depth) {
            *depth = current_depth;
        }
        return;
    }

    if (root->left != NULL){
        get_depth(root->left, current_depth+1, depth);
    }
    if (root->right != NULL){
        get_depth(root->right, current_depth+1, depth);
    }
}

void destroy_root(Node *root) {
    if (root == NULL) {
        return;
    }
    destroy_root(root->left);
    destroy_root(root->right);

    free(root);
    return;
}

void destroy_tree(Tree *tree){
    if (tree == NULL) {
        return;
    }
    destroy_root(tree->root);
    free(tree);
    return;
}
