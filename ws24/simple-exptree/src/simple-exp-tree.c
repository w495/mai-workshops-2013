/**
 *  @mainpage Простейшее построение дерева выражений из инфиксной записи.
 *
 *  @section ОПИСАНИЕ
 *
 *      По входной строке-выражению (из stdin) программа строит
 *      дерево выражений. Дерево выводится на стандартный поток вывода (stdout).
 *      На стандартные поток ошибок (stderr) выводится отладочная информация.
 *      Разбор строки происходит по следующей грамматике:
 *
 *          expr    ::= term op term
 *          term    ::= (expr) | alnum
 *          op      ::= <любые символы>
 *          alnum   ::= [a-z]|[0-9]
 *
 *      Важная деталь:
 *          На самом верхнем уровне выражения не может быть скобок.
 *          Такая возможность убрана для простоты программы.
 *
 *  @section ПРИМЕР
 *
 *          $> gcc ./programme.c -std=c99 -Wall -pedantic -o programme
 *          $>
 *          $> ./programme
 *          # 1      tree_build[47] start
 *          # 2          node_expr[62] start
 *          # 3              node_term[86] start
 *          # 4                  char_parse[122] start
 *          1 + 2
 *          # 4                  char_parse[140] end 3
 *          # 4                  node_make[148] start
 *          # 4                  node_make[155] end 3
 *          # 3              node_term[110] end 5
 *          # 3              char_parse[122] start
 *          # 3              char_parse[140] end 3
 *          # 3              node_term[86] start
 *          # 4                  char_parse[122] start
 *          # 4                  char_parse[140] end 3
 *          # 4                  node_make[148] start
 *          # 4                  node_make[155] end 3
 *          # 3              node_term[110] end 5
 *          # 3              node_make[148] start
 *          # 3              node_make[155] end 3
 *          # 2          node_expr[76] end
 *          # 1      tree_build[50] end
 *          # 1      tree_print[164] start
 *
 *              2
 *          +
 *              1
 *
 *          # 1      tree_print[171] end
 *          # 1      tree_del[194] start
 *          # 1      tree_del[197]: c    = '+'
 *          # 2          tree_del[194] start
 *          # 2          tree_del[197]: c    = '1'
 *          # 3              tree_del[194] start
 *          # 3              tree_del[203] end
 *          # 2          tree_del[203] end
 *          # 1      tree_del[197]: c    = '2'
 *          # 2          tree_del[194] start
 *          # 2          tree_del[203] end
 *          # 1      tree_del[203] end
 *          $>
 *          $> ./programme 2> /dev/null
 *          1 + 2
 *                  2
 *          +
 *                  1
 *          $>
 *          $> ./programme 2> /dev/null
 *          ( 1 + 2 ) * ( 2 + 3 )
 *                  3
 *              +
 *                  2
 *          *
 *                  2
 *              +
 *                  1
 *          $>
 *          $> ./programme 2> /dev/null
 *          (a v b) ^ ((x + y) / z)
 *                  z
 *              /
 *                      y
 *                  +
 *                      x
 *          ^
 *                  b
 *              v
 *                  a
 *          $>
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct _node_ node_t;

struct _node_ {
    char data;
    node_t *left;
    node_t *right;
};

typedef node_t* tree_t;


/* ОБЪЯВЛЕНИЯ ФУНКЦИЙ */

/**
 *  @fn Строит дерево выражения.
 */
tree_t tree_build(int depth);

/**
 *  @fn Печатает дерево. Внутри запускается рекурсивная процедура печати узлов.
 */
void tree_print(tree_t tree, int depth);

/**
 *  @fn Удаляет дерево. Используется рекурсивный спуск.
 */
void tree_del(tree_t tree, int depth);

/**
 * @fn Печатает поддерево. Рекурсивная процедура печати узлов.
 */
void node_print();

/**
 *  @fn Создает новый узел дерева выражений.
 */
tree_t node_make(char c, tree_t left, tree_t right, int depth);

/**
 *  @fn Создает и возвращает узел выражения.
 */
tree_t node_expr(int depth);

/**
 *  @fn Создает и возвращает узел терма.
 */
tree_t node_term(int depth);

/**
 * @fn  Считывает из стандартного ввода символы, пропуская пробелы.
 */
char char_parse(int depth);


int main() {
    /* построили дерево */
    tree_t exptree = tree_build(1);
    /* распечатали дерево */
    tree_print(exptree, 1);
    /* удалили дерево */
    tree_del(exptree, 1);
    return 0;
}

/*                  РЕАЛИЗАЦИЯ ФУНКЦИЙ              */

/**
 *  @fn Строит дерево выражения.
 *      Грамматика построения:
 *          expr    ::= term op term
 *          term    ::= (expr) | alnum
 *          op      ::= <любые символы>
 *          alnum   ::= [a-z]|[0-9]
 */
tree_t tree_build(int depth) {
    fprintf(stderr, "# %d %*s %s[%d] start\n", depth, depth * 4, " ", __FUNCTION__, __LINE__);
    tree_t tree = node_expr(depth + 1);

    fprintf(stderr, "# %d %*s %s[%d] end\n", depth, depth * 4, " ", __FUNCTION__, __LINE__);
    return tree;
}

/**
 *  @fn Возвращает узел выражения.
 *      Выражение состоит из термов и операции и имеет вид:
 *          <терм> <операция> <терм>.
 *      Само выражение скобки обрабатывать не умеет.
 *      Внутри этой функции вызываются функции конструирования термов.
 */
tree_t node_expr(int depth) {
    fprintf(stderr, "# %d %*s %s[%d] start\n", depth, depth * 4, " ", __FUNCTION__, __LINE__);

    /* левое поддерево */
    tree_t lhs = node_term(depth + 1);

    /* операция (корень этого поддерева) */
    char op  = char_parse(depth + 1);

    /* правое поддерево */
    tree_t rhs = node_term(depth + 1);

    /* само текущее поддерево */
    tree_t hs  = node_make(op, lhs, rhs, depth + 1);

    fprintf(stderr, "# %d %*s %s[%d] end\n", depth, depth * 4, " ", __FUNCTION__, __LINE__);
    return hs;
}

/**
 *  @fn Возвращает узел терма.
 *      Терм имеет может представлять из себя выражение в скобках,
 *      либо буквы или цифру.
 */
tree_t node_term(int depth) {
    fprintf(stderr, "# %d %*s %s[%d] start\n", depth, depth * 4, " ", __FUNCTION__, __LINE__);

    int c;
    if(!(c= char_parse(depth + 1))){
        fprintf(stderr, "# %d %*s %s[%d] end 1\n", depth, depth * 4, " ", __FUNCTION__, __LINE__);
        return 0;
    }

    if ('(' == c) {
        tree_t tree = node_expr(depth + 1);
        if(!(c= char_parse(depth + 1))){

            fprintf(stderr, "# %d %*s %s[%d] end 2\n", depth, depth * 4, " ", __FUNCTION__, __LINE__);
            return 0;
        }
        if (')' != c){
            fprintf(stderr, "# %d %*s %s[%d] end 3\n", depth, depth * 4, " ", __FUNCTION__, __LINE__);
            return tree;
        }
        fprintf(stderr, "# %d %*s %s[%d] end 4\n", depth, depth * 4, " ", __FUNCTION__, __LINE__);
        return tree;
    }
    else {
        tree_t tree = node_make(c, NULL, NULL, depth + 1);
        fprintf(stderr, "# %d %*s %s[%d] end 5\n", depth, depth * 4, " ", __FUNCTION__, __LINE__);
        return tree;
    }
}

/**
 * @fn  Считывает из стандартного ввода символы, пропуская пробелы.
 *      Если встречаются символы \n или EOF, возвращает нуль.
 *      В данном случае нуль нужно рассматривать как символ конца строки.
 *
 */
char char_parse(int depth){
    fprintf(stderr, "# %d %*s %s[%d] start\n", depth, depth * 4, " ", __FUNCTION__, __LINE__);

    char c;
    while(1){
        c = getchar();
        if(' ' != c)
            break;
    }

    if('\n' == c){
        fprintf(stderr, "# %d %*s %s[%d] end 1\n", depth, depth * 4, " ", __FUNCTION__, __LINE__);
        return 0;

    }
    else if(EOF == c){
        fprintf(stderr, "# %d %*s %s[%d] end 2\n", depth, depth * 4, " ", __FUNCTION__, __LINE__);
        return 0;
    }
    fprintf(stderr, "# %d %*s %s[%d] end 3\n", depth, depth * 4, " ", __FUNCTION__, __LINE__);
    return c;
}

/**
 *  @fn Создает новый узел дерева выражений.
 */
tree_t node_make(char data, tree_t left, tree_t right, int depth) {
    fprintf(stderr, "# %d %*s %s[%d] start\n", depth, depth * 4, " ", __FUNCTION__, __LINE__);

    tree_t tree = malloc(sizeof(tree_t));
    tree->data = data;
    tree->left = left;
    tree->right = right;

    fprintf(stderr, "# %d %*s %s[%d] end 3\n", depth, depth * 4, " ", __FUNCTION__, __LINE__);
    return tree;
}

/**
 *  @fn Печатает дерево.
 *      Внутри запускается рекурсивная процедура печати узлов.
 */
void tree_print(tree_t tree, int depth) {
    fprintf(stderr, "# %d %*s %s[%d] start\n", depth, depth * 4, " ", __FUNCTION__, __LINE__);

    if (tree){
        fprintf(stderr, "\n");
        node_print(tree, 0);
        fprintf(stderr, "\n");
    }
    fprintf(stderr, "# %d %*s %s[%d] end\n", depth, depth * 4, " ", __FUNCTION__, __LINE__);
}

/**
 *  @fn Печатает поддерево. Рекурсивная процедура печати узлов.
 *      Сначала печатает левое поддерево.
 *      Потом печатает текущий узел с соответствующим отступом.
 *      Потом печатает правое поддерево.
 */
void node_print(tree_t tree, int tab) {
    if (tree->right){
        node_print(tree->right, tab + 1);
    }
    printf("%*s %c\n", tab * 4, " ", tree->data);
    if (tree->left){
        node_print(tree->left, tab + 1);
    }
}

/**
 *  @fn Удаляет дерево. Используется рекурсивный спуск.
 */
void tree_del(tree_t tree, int depth) {
    fprintf(stderr, "# %d %*s %s[%d] start\n", depth, depth * 4, " ", __FUNCTION__, __LINE__);
    tree_t p;
    while (tree != NULL) {
        fprintf(stderr, "# %d %*s %s[%d]: c    = '%c' \n", depth, depth * 4, " ", __FUNCTION__, __LINE__, tree->data);
        tree_del(tree->left, depth + 1);
        p = tree;
        tree = tree->right;
        free(p);
    }
    fprintf(stderr, "# %d %*s %s[%d] end\n", depth, depth * 4, " ", __FUNCTION__, __LINE__);
}
