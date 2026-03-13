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
        if (result == 0){
            return 2;
        } else if (result > 0){
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
    if (parent == NULL) {
        tree->root = new_node;
    } else {
        if (tree->cmp(value, parent->value) >= 0) {
            parent->right = new_node;
        } else {
            parent->left = new_node;
        }
    }
    return 0;
}

void print_tree(const Node *root, int level){
    if (root == NULL) {
        return;
    }
    print_tree(root->right, level + 1);
    printf("%*s", level * 4, "");
    printf("%d\n", root->value);
    print_tree(root->left, level + 1);
}

int delete_node(Tree *tree, int value){
    Node *current = tree->root;
    int result;
    
    while (current != NULL) {
        result = tree->cmp(value, current->value);
        if (result == 0) break;
        current = (result > 0) ? current->right : current->left;
    }
    if (current == NULL) return 1;
    
    int childs = (current->left != NULL) + (current->right != NULL);
    
    if (childs == 0) {
        if (current->parent == NULL) {
            tree->root = NULL;
        } else if (current->parent->left == current) {
            current->parent->left = NULL;
        } else {
            current->parent->right = NULL;
        }
    }
    else if (childs == 1) {
        Node *child = current->left ? current->left : current->right;
        child->parent = current->parent;
        
        if (current->parent == NULL) {
            tree->root = child;
        } else if (current->parent->left == current) {
            current->parent->left = child;
        } else {
            current->parent->right = child;
        }
    }
    else if (childs == 2) {
        Node *swap = current->right;
        while (swap->left != NULL) {
            swap = swap->left;
        }
        if (swap->parent->left == swap) {
            swap->parent->left = swap->right;
        } else {
            swap->parent->right = swap->right;
        }
        if (swap->right != NULL) {
            swap->right->parent = swap->parent;
        }
        swap->parent = current->parent;
        swap->left = current->left;
        swap->right = current->right;
        
        if (swap->left != NULL) swap->left->parent = swap;
        if (swap->right != NULL) swap->right->parent = swap;
        
        if (current->parent == NULL) {
            tree->root = swap;
        } else if (current->parent->left == current) {
            current->parent->left = swap;
        } else {
            current->parent->right = swap;
        }
    }
    free(current);
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
