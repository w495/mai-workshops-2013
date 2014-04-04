// Автор: Александр Балес

#include "list.h"


int main() {
    Iterator my_iter;
    List my_list;

    my_list.head = NULL;

    int c, val = 0, pos, k, ans;

    bool flag = false;

    helper();

    while ((c = getchar()) != EOF) {
        flag = false;
        switch (c) {
            case 'c':
                if (list_Create(&my_list)) {
                    printf("List is already created \n");
                    break;
                }
                Create(&my_list);
                break;
            case 'e':
                if (!list_Create(&my_list)) {
                    printf("List isn't created \n");
                    break;
                }
                if (Empty(&my_list) == 1) {
                    printf("List is empty\n");
                    break;
                }
                printf("List isn`t empty\n");
                break;
            case 'h':
                helper();
                break;
            case 'i':
                getchar();
                my_getint(&pos, &flag);
                if (!flag) {
                    printf("You havn`t entered index. Try again.\n");
                    break;
                }
                my_getint(&val, &flag);
                if (!flag) {
                    printf("You havn`t entered value. Try again.\n");
                    break;
                }
                if (!list_Create(&my_list)) {
                    printf("List isn't created \n");
                    break;
                }
                if (!find_Items_Index(&my_list, &my_iter, pos)) {
                    printf("Error. Not found items index: %d\n", pos);
                    break;
                }
                Insert(&my_list, &my_iter, val);
                break;
            case 's':
                getchar();
                if (Empty(&my_list) == 1) {
                    printf("Error: List is empty!\n");
                    break;
                }
                my_getint(&k, &flag);
                if (!flag) {
                    printf("You havn`t entered index. Try again.\n");
                    break;
                }

                if (k < 0) {
                    k = k % Size(&my_list);
                    k = Size(&my_list) + k % Size(&my_list) + 1;
                }
                if (k > Size(&my_list))
                    k = k % Size(&my_list);
                if (!list_Create(&my_list)) {
                    printf("List isn't created \n");
                    break;
                }
                find_Items_Index(&my_list, &my_iter, k);
                my_swap(&my_list, &my_iter);
                break;
            case 'p':
                if (!list_Create(&my_list)) {
                    printf("List isn't created \n");
                    break;
                }
                print_List(&my_list);
                break;
            case 'd':
                getchar();
                my_getint(&val, &flag);
                if (!flag) {
                    printf("You havn`t entered value. Try again.\n");
                    break;
                }
                if (!list_Create(&my_list)) {
                    printf("List isn't created \n");
                    break;
                }
                if (!find_Items_Data(&my_list, &my_iter, val)) {
                    printf("Error. Not found items data: %d\n", pos);
                    break;
                }
                Delete(&my_list, &my_iter);
                break;
            case 'l':
                if (!list_Create(&my_list)) {
                    printf("List isn't created \n");
                    break;
                }
                ans = length_of_List(&my_list);
                if (ans != -1)
                    printf("Length list: %d \n", ans);
                break;
            case '0':
                if (list_Create(&my_list))
                    Destroy(&my_list);
                break;
            case 'x':
                if (list_Create(&my_list))
                    Destroy(&my_list);
                break;
        }
    }
}
