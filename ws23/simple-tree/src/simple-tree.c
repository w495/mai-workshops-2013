#include<stdio.h>
#include<stdlib.h>

struct node;
typedef struct node Node;
typedef Node *Tree;
typedef float data_type;

Tree tree_create();
Tree node_maker(Tree son, Tree brother, data_type x);
Tree node_seach(Tree tree, data_type x);
void cur_data_print(Tree * p);
void subtree_print(Tree p, int depth);
void tree_add(Tree * tree, data_type x);
void tree_print(Tree tree);
void tree_delete(Tree * tree);
int leaves_counter(Tree tree);
void leaves_subtree_counter(Tree p, int *count);
int counter(Tree tree);
void subtree_counter(Tree p, int *count);

struct node {
    data_type data;
    struct node *son;
    struct node *brother;
};


int main() {
    Tree tree = tree_create();
    Tree *cur = NULL;
    int choice;
    enum { ROOT, ELSE } check;

    do {
        data_type data;

        printf("0 exit\t\t\t" "5 delete\n"
               "1 top (create)\t\t" "6 print \n"
               "2 youngest brother\t" "7 curent\n"
               "3 eldest son\t\t" "8 count\n"
               "4 add\t\t\t" "9 count leaves\n");
        if (scanf("%i", &choice) != 1)
            getchar();

        switch (choice) {
            case 0:
                break;
            case 1:
                cur = &tree;
                check = ROOT;
                break;
            case 2:
                if (!cur)
                    printf("ERR ADDRES!\n");
                else {
                    if (*cur && check != ROOT)
                        cur = &((*cur)->brother);
                    else
                        printf("ERR ADDRES\n");
                }
                break;
            case 3:
                if (!cur)
                    printf("ERR ADDRES!\n");
                else {
                    if (*cur) {
                        cur = &((*cur)->son);
                        check = ELSE;
                    }
                    else
                        printf("ERR ADDRES\n");
                }
                break;
            case 4:
                if (!cur)
                    printf("ERR ADDRES!\n");
                else {
                    scanf("%f", &data);
                    tree_add(cur, data);
                }
                break;
            case 5:
                if (!cur)
                    printf("ERR ADDRES!\n");
                else {
                    if (*cur)
                        tree_delete(cur);
                    else
                        printf("ERR ADDRES\n");
                }
                break;
            case 6:
                tree_print(tree);
                break;
            case 7:
                cur_data_print(cur);
                break;
            case 8:
                printf("%d\n", counter(tree));
                break;
            case 9:
                printf("%d\n", leaves_counter(tree));
                break;
            default:
                printf("COMMAND ERR\n");
                break;
        }
    } while (choice != 0);
    tree_delete(&tree);
    return 1;
}

Tree tree_create() {
    return NULL;
}

void tree_add(Tree * tree, data_type x) {
    if (*tree == NULL)
        *tree = node_maker(NULL, NULL, x);
    else
        printf("\nDENIAL\n");
}

Tree node_maker(Tree son, Tree brother, data_type x) {
    Tree p;

    p = (Tree) malloc(sizeof(Node));
    p->data = x;
    p->son = son;
    p->brother = brother;
    return p;
}

int leaves_counter(Tree tree) {
    int a = 0;
    int *count = &a;

    if (tree)
        leaves_subtree_counter(tree, count);
    else
        printf("ERR COUNT\n");
    return *count;
}

void leaves_subtree_counter(Tree p, int *count) {
    if (p->brother)
        leaves_subtree_counter(p->brother, count);
    if (p->son)
        leaves_subtree_counter(p->son, count);
    else
        (*count)++;
}

int counter(Tree tree) {
    int a = 0;
    int *count = &a;

    if (tree)
        subtree_counter(tree, count);
    else
        printf("ERR COUNT\n");
    return *count;
}

void subtree_counter(Tree p, int *count) {
    Tree son = p->son;

    (*count)++;
    while (son) {
        subtree_counter(son, count);
        son = son->brother;
    }
}

void tree_print(Tree tree) {
    printf("<<<TREE>>>\n\n");
    if (tree)
        subtree_print(tree, 0);
    else
        printf("NOTHING\n");
    printf("\n<<<TREE>>>\n");
}

void subtree_print(Tree p, int depth) {
    int i;
    Tree son = p->son;

    for (i = 0; i != depth; ++i)
        printf(" ");
    printf("%f\n", p->data);
    while (son) {
        subtree_print(son, 1 + depth);
        son = son->brother;
    }
}

void cur_data_print(Tree * p) {
    if (p && (*p) && (*p)->data)
        printf("\n%f\n\n", (*p)->data);
    else
        printf("<IS EMPTY>\n");
}

void tree_delete(Tree * tree) {
    if (*tree) {
        Tree *it = &(*tree)->son;

        while (*it) {
            Tree *tmp = &(*tree)->brother;

            tree_delete(it);
            it = tmp;
        }
        free(*tree);
        *tree = NULL;
    }
}
