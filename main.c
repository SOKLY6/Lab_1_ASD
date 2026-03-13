#include <stdio.h>
#include "tree_utils.h"
#include "comparators.h"
#include "input.h"
#include "menu.h"

int main(void) {
    Tree *tree = tree_init();
    if (tree == NULL) {
        printf("Ошибка выделения памяти");
        return 1;
    }
    int choice;
    int value;
    int result;
    
    while (1) {
        menu();
        
        while (input_value(&choice) != 0 || choice < 1 || choice > 5) {
            printf("Введите корректное значение (цифру от 1 до 5): ");
        }
        
        switch (choice) {
        case 1:
            printf("Введите целое число для добавления в дерево: ");
            while (input_value(&value) != 0) {
                printf("Введите ЦЕЛОЕ число: ");
            }
            result = insert_node(tree, value);
            if (result != 0) {
                printf("Ошибка: не удалось добавить узел\n");
            } else {
                printf("Значение %d успешно добавлено в дерево\n", value);
            }
            break;
            
        case 2:
            printf("Введите целое число для удаления из дерева: ");
            while (input_value(&value) != 0) {
                printf("Введите ЦЕЛОЕ число: ");
            }
            result = delete_node(tree, value);
            if (result != 0) {
                printf("Значение %d не найдено в дереве\n", value);
            } else {
                printf("Значение %d успешно удалено из дерева\n", value);
            }
            break;
            
        case 3:
            printf("Текущее дерево:\n");
            if (tree->root == NULL) {
                printf("Дерево пустое\n");
            } else {
                print_tree(tree->root, 0);
            }
            break;
            
        case 4:
            {
                size_t depth = 0;
                if (tree->root == NULL) {
                    printf("Дерево пустое\n");
                } else {
                    get_depth(tree->root, 0, &depth);
                    printf("Глубина дерева: %zu\n", depth);
                }
            }
            break;
            
        case 5:
            printf("Выход из программы.\n");
            destroy_tree(tree);
            return 0;
            
        default:
            printf("Ошибка: выберите режим от 1 до 5\n");
            break;
        }
        
        printf("\n");
    }
    
    return 0;
}