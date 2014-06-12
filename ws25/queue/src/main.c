#include "queue.h"

int main() {
    int i = 0;
    char c;

    queue_t* firstQueue = queue_create();
    queue_t* secondQueue = queue_create();

    while (1) {
        scanf("%c", &c);
        if (c == '+') {
            scanf("%c", &c);

            if (c == '1') {
                firstQueue = queue_add(firstQueue);
            }
            if (c == '2') {
                secondQueue = queue_add(secondQueue);
            }
        }
        if (c == '-') {
            scanf("%c", &c);

            if (c == '1') {
                firstQueue = queue_del(firstQueue);
            }
            if (c == '2') {
                secondQueue = queue_del(secondQueue);
            }
        }
        if (c == 'c') {
            firstQueue = queue_concat(firstQueue, secondQueue);

            /** WARNING: ????
             * Возможно тут имелось ввиду освобождение памяти?
             */
            secondQueue = NULL;
            secondQueue = queue_create();
        }
        if (c == 's') {
            scanf("%c", &c);

            if (c == '1') {
                firstQueue = queue_sort(firstQueue);
            }
            if (c == '2') {
                secondQueue = queue_sort(secondQueue);
            }
        }
        if (c == 'q') {
            printf("Bye\n");
            break;
        }
        if (c == 'p') {
            scanf("%c", &c);
            if (c == '1')
                queue_print(firstQueue);
            if (c == '2')
                queue_print(secondQueue);
        }
    }

    return 0;
}
