// Автор: Александр Балес

#include "list.h"

void my_getint(int *Val, bool * flag) {
    int c;

    c = getchar();
    *flag = false;
    bool bit = false;
    bool point_minuse = false;

    if (c == '\n' || c == EOF) {
        printf("Error, incorrect input!\n");
        return;
    }
    if (c == '-') {
        point_minuse = true;
    }
    else {
        *Val = c - '0';
        bit = true;
        *flag = true;
    }
    while ((c = getchar()) != EOF && c != '\n' && c != ' ') {
        if (!('0' <= c && c <= '9')) {
            printf("Error, WTF!!!\n");
            *flag = false;
            break;
        }
        if (bit == false) {
            bit = true;
            *flag = true;
            *Val = c - '0';
        }
        else {
            *Val = (*Val) * 10 + c - '0';
            *flag = true;
        }

    }
    if (point_minuse)
        (*Val) *= -1;
}

// Функция Create выделяет память под терминатор, создает пустой кольцевой список

void Create(List * l) {
    l->head = malloc(sizeof(_Item_));
    l->head->next = l->head->prev = l->head;
    l->size = 0;
}

// Создание итератора из ссылочной компоненты next терминатора списка

Iterator First(const List * l) {
    Iterator res = { l->head->next };
    return res;
}

// Функция Last создает итератор из указателя на терминатор списка

Iterator Last(const List * l) {
    Iterator res = { l->head };
    return res;
}


bool list_Create(const List * l) {
    return (l->head);
}

// Вызов меню

void helper() {
    printf("\tc --- create list;\n\
    e --- check of empty;\n\
    i --- insert to list before some element, also if you wanting insert to tail of list then write --- i 0 <value>;\n\
    p --- print list;\n\
    d --- delete element from list;\n\
    l --- length of list;\n\
    s --- swap two elemts;\n\
    0 --- destroyed list;\n\
    x --- exit.\n");
}

// Список пуст, если итераторы начала и конца совпадают
bool Empty(const List * l) {
    Iterator fst = First(l);
    Iterator lst = Last(l);

    return Equal(&fst, &lst);
}

// Фукнция Size возвращает хранимый размер списка

int Size(const List * l) {
    return l->size;
}

// Функция Insert вставляет элемент в список перед заданным.

void Insert(List * l, Iterator * i, const int t) {
    Iterator res = { malloc(sizeof(_Item_)) };
    if (!res.node)
        return;
    res.node->data = t;
    res.node->next = i->node;
    res.node->prev = i->node->prev;
    res.node->prev->next = res.node;
    i->node->prev = res.node;
    l->size++;
}

// функция Delete удаляет элемент, на который указывает итератор, возвращая
// в качестве результата итератор, ссылающийся на следующий за удаленным элемент

void Delete(List * l, Iterator * i) {
    Iterator res = Last(l);

    if (Equal(i, &res))
        return;
    res.node = i->node->next;
    res.node->prev = i->node->prev;
    i->node->prev->next = res.node;
    l->size--;
    free(i->node);
    i->node = 0;
}

// Функция Destroy уничтожает список, перебирая его элементы и удаляя их

void Destroy(List * l) {
    struct Item *i = l->head->next;

    while (i != l->head) {
        struct Item *pi = i;

        i = i->next;
        free(pi);
    }
    free(l->head);
    l->head = NULL;
    l->size = 0;
}

// Выводим наш список на экран

void print_List(List * l) {
    if (Empty(l)) {
        printf("Error: List is empty!");
        return;
    }

    Iterator res = { malloc(sizeof(_Item_)) };
    res = First(l);
    Iterator last = Last(l);

    while (!Equal(&res, &last)) {
        printf("%d ", res.node->data);
        res.node = res.node->next;
    }
    printf("\n");
}

// Функция сравнения конца и начала списка

bool Equal(const Iterator * lhs, const Iterator * rhs) {
    return lhs->node == rhs->node;
}

// Вычисляем длину нашего списка

int length_of_List(List * l) {
    if (Empty(l)) {
        printf("List is empty!\n");
        return -1;
    }

    int counter = 0;
    Iterator res = { malloc(sizeof(_Item_)) };
    res = First(l);
    Iterator last = Last(l);

    while (!Equal(&res, &last)) {
        res.node = res.node->next;
        counter++;
    }
    return counter;
}

// Ищем в списке нужный индекс

bool find_Items_Index(List * l, Iterator * i, const int index) {
    int counter = 1;

    if (index == 0) {
        *i = Last(l);
        return true;
    }
    if (Empty(l))
        return false;

    Iterator last = Last(l);

    *i = First(l);
    while (!Equal(i, &last)) {
        if (counter == index)
            return true;
        i->node = i->node->next;
        counter++;
    }
    return false;
}

// Ищем в списке нужное нам значение (первое попавшееся)

bool find_Items_Data(List * l, Iterator * i, const int val) {
    int counter = 1;

    if (Empty(l))
        return false;

    Iterator last = Last(l);

    *i = First(l);
    while (!Equal(i, &last)) {
        if (i->node->data == val)
            return true;
        i->node = i->node->next;
        counter++;
    }
    return false;
}

// Меняем местами (k-1) и (k+1) элементы

void my_swap(List * l, Iterator * i) {
    int tmp;

    if (length_of_List(l) == 1)
        return;
    if (l->head == i->node->prev) {
        tmp = i->node->prev->prev->data;
        i->node->prev->prev->data = i->node->next->data;
        i->node->next->data = tmp;
        return;
    }
    if (l->head == i->node->next) {
        tmp = i->node->next->next->data;
        i->node->next->next->data = i->node->prev->data;
        i->node->prev->data = tmp;
        return;
    }
    tmp = i->node->prev->data;
    i->node->prev->data = i->node->next->data;
    i->node->next->data = tmp;
}
