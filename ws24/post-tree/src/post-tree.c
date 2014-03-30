/**
 *  @mainpage Построение дерева выражений из постфиксной записи.
 *
 *  @section ОПИСАНИЕ
 *
 *      Из стандартного потока ввода (stdin) программа считывает строку
 *      с выражением в постфиксной записи. По этому выражению строится дерево.
 *      Выводит дерево на стандартный поток вывода. Кроме дерева
 *      на стандартный поток вывода печатается тоже самое выражение
 *      в префиксной, инфиксной, и постфиксной записях.
 *      Инфиксная запись выражение печатается со скобками.
 *
 *  @section ПРИМЕР
 *          $> gcc prog.c -std=c99 -Wall -pedantic -o prog
 *          $> ./prog
 *          Enter Postfix Expression : 1 2 + 3 / 4 *
 *              [4]
 *          [*]
 *                  [3]
 *              [/]
 *                      [2]
 *                  [+]
 *                      [1]
 *          Pre-Order Traversal :
 *          *  /  +  1  2  3  4
 *          In-Order Traversal :
 *          (( 1  +  2 ) /  3 ) *  4
 *          Post-Order Traversal :
 *          *  /  +  1  2  3  4
 *          $>
**/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * ОПИСАНИЕ ДЕРЕВА.
 * Совсем по хорошему его надо выносить в отдельный модуль.
 */

typedef struct _node_ node_t;

struct _node_ {
    char data;
    node_t *left;
    node_t *right;
};

typedef node_t* tree_t;

/**
 *  @typedef тип символа
 */
typedef enum {
    IS_OP       =  0,   /* оператор */
    IS_ALNUM    =  1,   /* операнд */
    IS_ERR      = -1    /* ни то ни другое */
} symbol_t;


/**
 *  @fn Проверяет является входной символ оператором или операндом.
 */
symbol_t symbol_check(char c);

/**
 *  @fn Строит дерево выражений на основе постфиксного выражения.
 *      Само выражение передается через buffer.
 */
tree_t tree_build(char *buffer);

/**
 *  @fn Выводит выражение в префиксной записи
 */
void preorder(tree_t tree);

/**
 *  @fn Выводит выражение в постфиксной записи
 */
void postorder(tree_t tree);

/**
 *  @fn Выводит выражение в инфиксной записи
 */
void inorder(tree_t tree);

/**
 *  @fn Выводит выражение в инфиксной записи.
 *      Вспомогательная функция для inorder.
 */
void inorder_depth(tree_t tree, int flag);

/**
 *  @fn Печатает дерево. Внутри запускается рекурсивная процедура печати узлов.
 */
void tree_print(tree_t tree);

/**
 * @fn Печатает поддерево. Рекурсивная процедура печати узлов.
 */
void node_print(tree_t tree, int tab);


/*
 * ОПИСАНИЕ СТЕКА.
 * Его тоже надо выносить в отдельный модуль.
 * Обратите внимание, что стек основан на динамическом массиве.
 */

typedef struct _stack_ stack_t;

struct _stack_ {
    int top;        /* Индекс верхнего элемента стека. */
    tree_t *data;   /* Содержимое стека. */
};


/**
 *  @fn Создает новый стек и возвращает указатель на него.
 */
stack_t *stack_new();

/**
 *  @fn Кладет поддерево в стек.
 */
void stack_push(stack_t * stack, tree_t tree);

/**
 *  @fn Возвращает содержимое верхушки стека.
 */
tree_t stack_pop(stack_t * stack);

/**
 *  @fn Возвращает дно стека (самый нижний элемент)
 */
tree_t stack_base(stack_t * self);

const size_t BUFFER_SIZE = 512;


int main() {
    /* Создаем динамический буфер большого размера */
    char *buffer = malloc(sizeof(buffer) * BUFFER_SIZE);

    /* Инициализируем буфер нулями. */
    memset(buffer, 0, BUFFER_SIZE);

    /* Считываем выражение в постфиксной форме */
    printf("Enter Postfix Expression : ");
    fgets(buffer, BUFFER_SIZE, stdin);

    /* Стоим по этому выражению дерево */
    tree_t tree = tree_build(buffer);

    /* Печатаем дерево */
    tree_print(tree);

    /* Показываем как выгляжит выражение в префиксной форме. */
    printf("\nPre-Order Traversal :  \n");
    preorder(tree);
    printf("\n");


    /* Показываем как выгляжит выражение в инфиксной форме. */
    printf("\nIn-Order Traversal :  \n");
    inorder(tree);
    printf("\n");

    /* Показываем как выгляжит выражение в постфиксной форме, для отладки. */
    printf("\nPost-Order Traversal :  \n");
    postorder(tree);
    printf("\n");

    return 0;

}

/*
 * РЕАЛИЗАЦИЯ ДЕРЕВА ВЫРАЖЕНИЙ.
 */


/**
 *  @fn Строит дерево выражений на основе постфиксного выражения.
 *      Само выражение передается через buffer.
 */
tree_t tree_build(char *buffer) {

    tree_t new_tree;
    tree_t tree_lhs;
    tree_t tree_rhs;
    symbol_t flag;

    /* Заводим стек. */
    stack_t *stack = stack_new();

    /* Читаем первый символ из buffer */
    char symbol = buffer[0];
    for (int i = 1; symbol != 0; ++i) {
        /* является входной символ оператором или операндом? */
        flag = symbol_check(symbol);
        /* символ является операндом */
        if (IS_ALNUM == flag) {
            /* Создаем поддерево и кладем его в стек */
            new_tree = malloc(sizeof(node_t));
            new_tree->data = symbol;
            new_tree->left = NULL;
            new_tree->right = NULL;
            stack_push(stack, new_tree);
        }
        else if (IS_OP == flag) {
            /*
             * Достаем из стека два предыдущих операнда.
             * И создаем узел дерева, так, что эти два операнда,
             * становятся его дочерними узлами.
             */
            tree_rhs = stack_pop(stack);
            tree_lhs = stack_pop(stack);
            new_tree = malloc(sizeof(node_t));
            new_tree->data = symbol;
            new_tree->left = tree_lhs;
            new_tree->right = tree_rhs;
            stack_push(stack, new_tree);
        }
        symbol = buffer[i];
    }

    return stack_base(stack);
}


/**
 *  @fn Выводит выражение в префиксной записи
 */
void preorder(tree_t tree) {
    if (tree) {
        printf(" %c ", tree->data);
        preorder(tree->left);
        preorder(tree->right);
    }
}

/**
 *  @fn Выводит выражение в постфиксной записи
 */
void postorder(tree_t tree) {
    if (tree) {
        printf(" %c ", tree->data);
        postorder(tree->left);
        postorder(tree->right);
    }
}

/**
 *  @fn Выводит выражение в инфиксной записи.
 *      Вспомогательная функция для inorder.
 *      Нужна для правильной обработки скобок.
 */
void inorder_depth(tree_t tree, int flag) {
    if (tree) {
        if (tree->left && tree->right && flag){
            printf("(");
        }
        inorder_depth(tree->left, 1);
        printf(" %c ", tree->data);
        inorder_depth(tree->right, 1);
        if (tree->left && tree->right && flag){
            printf(")");
        }
    }
}

/**
 *  @fn Выводит выражение в инфиксной записи.
 */
void inorder(tree_t tree) {
    inorder_depth(tree, 0);
}

/**
 *  @fn Печатает поддерево. Рекурсивная процедура печати узлов.
 *      Сначала печатает левое поддерево.
 *      Потом печатает текущий узел с соответствующим отступом.
 *      Потом печатает правое поддерево.
 */
void node_print(tree_t tree, int tab) {
    if (tree->right) {
        node_print(tree->right, tab + 1);
    }
    printf("%*s [%c]\n", tab * 4, " ", tree->data);
    if (tree->left) {
        node_print(tree->left, tab + 1);
    }
}

/**
 *  @fn Печатает дерево.
 *      Внутри запускается рекурсивная процедура печати узлов.
 */
void tree_print(tree_t tree) {
    if (tree) {
        node_print(tree, 0);
    }
}

/**
 *  @fn Проверяет является входной символ оператором или операндом.
 */
symbol_t symbol_check(char c) {
    if ('+' == c || '-' == c || '*' == c || '/' == c) {
        return IS_OP;
    }
    else if (   ('0' <= c && c <= '9')
            ||  ('a' <= c && c <= 'z')
            ||  ('A' <= c && c <= 'Z')) {
        return IS_ALNUM;
    }
    else {
        return IS_ERR;
    }
}

/*
 * РЕАЛИЗАЦИЯ СТЕКА.
 */


/**
 *  @fn Создает новый стек и возвращает указатель на него.
 *      Обратите внимание, что стек основа на динамическом массиве.
 */
stack_t *stack_new() {
    stack_t *self = malloc(sizeof(stack_t));

    self->top = -1;
    self->data = malloc(sizeof(tree_t));
    return self;
}

/**
 *  @fn Возвращает дно стека (самый нижний элемент)
 */
tree_t stack_base(stack_t * self) {
    return self->data[0];
}


/**
 *  @fn Кладет поддерево в стек.
 */
void stack_push(stack_t * self, tree_t tree) {
    self->top = self->top + 1;
    self->data = realloc(self->data, sizeof(tree_t));
    self->data[self->top] = tree;
}


/**
 *  @fn Возвращает содержимое верхушки стека.
 */
tree_t stack_pop(stack_t * self) {
    self->top = self->top - 1;
    if (self->top > -2) {
        tree_t tree = self->data[self->top + 1];
        return tree;
    }
    return NULL;
}


