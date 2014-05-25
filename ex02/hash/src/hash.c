/**
 *  Реализация квадратичного хешировния для строк.
 *
 *  @section ОПИСАНИЕ
 *
 *      Программа считывает со стандартного ввода операции и выполняет их.
 *          + <ключ> <значение> --- добавляет элемент в хеш таблицу.
 *                                  Если такой элемент уже есть, то сообщение
 *                                  об этом выводится на stderr.
 *          f <ключ>            --- ищет ключ по таблице и выводи значение
 *                                  на stdout. Если такого ключа нет,
 *                                  то сообщение об этом выводится на stderr.
 *          - <ключ>            --- удаляет ключ из таблицы. Если такого
 *                                  ключа нет, то сообщение об этом
 *                                  выводится на stderr.
 *          s                   --- выводит количество элементов в таблице.
 *          c                   --- выводит размер таблицы.
 *          p                   --- выводит содержимое таблицы в формате JSON.
 *          j                   --- выводит содержимое таблицы в формате JSON.
 *          x                   --- выводит содержимое таблицы в формате XML.
 *
 *      Если в какой-то момент таблица оказалась заполненной,
 *      то память для нее перевыделяется.
 *
 *  @section ПРИМЕР
 *
 *          $> gcc programme.c -Wall -pedantic -o programme
 *          $> ./programme
 *          + dog собака
 *          + cat кошка
 *          + rat крыска
 *          + bird птичка
 *          f dog
 *          собака
 *          p
 *          {
 *          "size" : 4,
 *          "data" : [
 *                  {
 *                      "hash"  : "0x0139",
 *                      "key"   : "cat",
 *                      "value" : "кошка"
 *                  },
 *                  {
 *                      "hash"  : "0x013b",
 *                      "key"   : "dog",
 *                      "value" : "собака"
 *                  },
 *                  {
 *                      "hash"  : "0x0148",
 *                      "key"   : "rat",
 *                      "value" : "крыска"
 *                  },
 *                  {
 *                      "hash"  : "0x01a5",
 *                      "key"   : "bird",
 *                      "value" : "птичка"
 *                  },
 *              ]
 *          }
 *          - bird
 *          p
 *          {
 *          "size" : 3,
 *          "data" : [
 *                  {
 *                      "hash"  : "0x0139",
 *                      "key"   : "cat",
 *                      "value" : "кошка"
 *                  },
 *                  {
 *                      "hash"  : "0x013b",
 *                      "key"   : "dog",
 *                      "value" : "собака"
 *                  },
 *                  {
 *                      "hash"  : "0x0148",
 *                      "key"   : "rat",
 *                      "value" : "крыска"
 *                  },
 *              ]
 *          }
 *
 *  @author Александ Балес, Даниил Губарев, Никитин И.К. 2014 год, МАИ ПМФ.
**/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * @fn  Считывает строку произвольного размера.
 *      Производит выделение памяти для строки.
 *      Строка считывается по блокам.
 *      В качестве параметров задаются входной поток и размер блока.
**/
char *afgets(FILE * stream, const size_t block_size);

#define NODE_BLOCKSIZE 16

/**
 * @typedef Тип хеш-чисел
 */
typedef size_t hash_t;


/**
 *  @typedef Тип для ячейки хеш-таблицы.
 */
typedef struct {

    char *key;          /** Ключ **/

    char *value;        /** Значение **/

    char *_buffer;      /** Внутренний буфер для удобства считывания **/
} node_t;


/**
 *  @fn Создает элемент хеш-таблицы.
 *      Инициализирует поля структуры.
 */
node_t *node_create();

/*
 * Опишем функции, которые будут инкапсулировать
 * в себя внутренне устройство node_t.
 * Это сделано для того, чтобы функции htab_ ничего не знали про элемент.
 * В случае, если мы захотим поменять node,
 * нам ничего не придется переделывать.
 */

char *node_get_key(node_t *);

char *node_get_value(node_t *);

void node_set_key(node_t *, char *);

void node_set_value(node_t *, char *);

/**
 *  @fn Считывает ключ и значение элемента таблицы со стандартного ввода.
 */
int node_fscan_all(FILE *, node_t *);

/**
 *  @fn Считывает ключ элемента таблицы со стандартного ввода.
 */
int node_fscan_key(FILE *, node_t *);

/**
 *  @fn Вычисляет хеш для ключ элемента таблицы.
 */
hash_t node_hashing(node_t * const, size_t table_size);

/**
 *  @fn Удаляет элемент хеш-таблицы.
 *      Освобождает память.
 */
void node_destroy(node_t * node);


#define HTAB_INIT_SIZE 16561

typedef struct {

    size_t size;        /** Количество элементов в таблице   **/

    node_t **data;      /** Массив указателей на ячейки      **/

    bool *_used;        /** Массив с флагами использования   **/

    size_t _idx;        /** Индекс рехеширования             **/

    size_t _cap;        /** Реальный размер таблицы          **/
} htab_t;


/**
 * @fn  Создает хеш-таблицу.
 *      Выделяет память. Инициализирует поля структуры.
 */
htab_t *htab_create();

/**
 *  @fn Возвращает количество элементов в таблице.
 */
size_t htab_get_size(htab_t * const);

/**
 *  @fn Возвращает размер таблицы.
 */
size_t htab_get_cap(htab_t * const);


/**
 *  @fn Добавляет в таблицу node.
 *      На этот момент Node уже должен быть создан.
 *      Функция возвращает 1 в случае успеха
 *      и -1 в случае неуспеха.
 */
int htab_addnode(htab_t *, node_t * const);

/**
 *  @fn Ищет node по таблице.
 *      На этот момент в Node должен быть заполнен ключ.
 *      Искомое значение возвращается в node->value.
 *      Сама функция возвращает 1 в случае успеха
 *      и -1 в случае неуспеха.
 */
int htab_findnode(htab_t * const, node_t *);

/**
 *  @fn Удаляет из таблицы элемент с ключом от node.
 *      На этот момент в Node должен быть заполнен ключ.
 *      Сама функция возвращает 1 в случае успеха
 *      и -1 в случае неуспеха.
 */
int htab_delnode(htab_t *, node_t *);

/**
 *  @fn Ищет node по таблице.
 *      На этот момент в Node должен быть заполнен ключ.
 *      Возвращает hash для ключа node
 */
hash_t htab_findhash(htab_t * const, node_t *);

/**
 *  @fn Выводит хеш-таблицу в файловый поток stream в формате JSON.
 */
int htab_tojson(FILE *, htab_t *);

/**
 *  @fn Выводит хеш-таблицу в файловый поток stream в формате XML.
 */
int htab_toxml(FILE *, htab_t *);

/**
 *  @fn Удаляет хеш-таблицу. Освобождает память.
 */
void htab_destroy(htab_t *);

/**
 *  @fn Производит рехеширование.
 *      Реализовано квадратичное рехеширование.
 */
hash_t rehash(hash_t, size_t f_id, size_t table_size);

int main() {
    htab_t *table = htab_create();
    char c;

    while (scanf("%c", &c) != EOF) {
        switch (c) {
                /* Добавить элемент. */
            case '+':{
                node_t *node = node_create();
                int err;

                err = node_fscan_all(stdin, node);
                err = htab_addnode(table, node);
                if (err == -1)
                    fprintf(stderr, "Exist\n");

                break;
            }
                /* Найти элемент. */
            case 'f':{
                node_t *tmp_node = node_create();
                int err;

                err = node_fscan_key(stdin, tmp_node);
                err = htab_findnode(table, tmp_node);
                if (err == -1)
                    fprintf(stderr, "Not found\n");
                else {
                    fprintf(stdout, "%s\n", tmp_node->value);
                }
                node_destroy(tmp_node);
                break;
            }
                /* Удалить элемент. */
            case '-':{
                node_t *tmp_node = node_create();

                int err;

                err = node_fscan_key(stdin, tmp_node);
                err = htab_delnode(table, tmp_node);
                if (err == -1)
                    fprintf(stderr, "Not found\n");
                node_destroy(tmp_node);
                break;
            }
                /* Распечатать количество элементов */
            case 's':{
                size_t size = htab_get_size(table);

                fprintf(stdout, "%ld\n", size);
                break;
            }
                /* Распечатать размер таблицы */
            case 'c':{
                size_t size = htab_get_cap(table);

                fprintf(stdout, "%ld\n", size);
                break;
            }
                /* Распечатать хеш-таблицу в JSON */
            case 'p':{
                htab_tojson(stdout, table);
                break;
            }
                /* Распечатать хеш-таблицу в JSON */
            case 'j':{
                htab_tojson(stdout, table);
                break;
            }
                /* Распечатать хеш-таблицу в XML */
            case 'x':{
                htab_toxml(stdout, table);
                break;
            }
                /* Остановить программу */
            case 'q':{
                htab_destroy(table);
                return 0;
            }
        }
    }
    htab_destroy(table);
    return 0;
}

/**
 * @fn  Создает хеш-таблицу.
 *      Выделяет память. Инициализирует поля структуры.
 */
htab_t *htab_create() {
    htab_t *this;

    this = malloc(sizeof(htab_t));
    this->_cap = HTAB_INIT_SIZE;
    this->data = malloc(sizeof(node_t *) * this->_cap);
    this->_used = malloc(sizeof(bool) * this->_cap);
    memset(this->data, 0, sizeof(node_t *) * this->_cap);
    memset(this->_used, 0, sizeof(bool) * this->_cap);
    this->_idx = 0;
    this->size = 0;
    return this;
}

/**
 *  @fn Возвращает количество элементов в таблице.
 */
size_t htab_get_size(htab_t * const this) {
    return this->size;
}

/**
 *  @fn Возвращает размер таблицы.
 */
size_t htab_get_cap(htab_t * const this) {
    return this->_cap;
}

/**
 *  @fn Удаляет хеш-таблицу. Освобождает память.
 */
void htab_destroy(htab_t * this) {
    size_t i;

    if (!this)
        return;
    for (i = 0; i != this->_cap; ++i) {
        node_destroy(this->data[i]);
    }
    if (this->data) {
        free(this->data);
        this->data = NULL;
    }
    if (this->_used) {
        free(this->_used);
        this->data = NULL;
    }

    free(this);
    this = NULL;
}

/**
 *  @fn Выводит хеш-таблицу в файловый поток stream в формате JSON.
 */
int htab_tojson(FILE * stream, htab_t * this) {
    hash_t hash;

    fprintf(stream, "{\n");
    fprintf(stream, "   \"size\" : %ld,\n", this->size);
    fprintf(stream, "   \"data\" : [\n");
    for (hash = 0; hash != this->_cap; ++hash) {
        if (this->_used[hash]) {
            node_t *node = this->data[hash];

            fprintf(stream,
                    "        {\n"
                    "            \"hash\"  : \"0x%04lx\", \n"
                    "            \"key\"   : \"%s\",\n"
                    "            \"value\" : \"%s\"\n"
                    "        },\n",
                    hash, node_get_key(node), node_get_value(node)
                );
        }
    }
    fprintf(stream, "    ]\n");
    fprintf(stream, "}\n");
    return 1;
}

/**
 *  @fn Выводит хеш-таблицу в файловый поток stream в формате XML.
 */
int htab_toxml(FILE * stream, htab_t * this) {
    hash_t hash;

    fprintf(stream, "<result>\n");
    fprintf(stream, "    <size>%ld</size>\n", this->size);
    fprintf(stream, "    <data>\n");
    for (hash = 0; hash != this->_cap; ++hash) {
        if (this->_used[hash]) {
            node_t *node = this->data[hash];

            fprintf(stream,
                    "        <item hash=\"0x%04lx\">\n"
                    "            <key>%s</key>\n"
                    "            <value>%s</value>\n"
                    "        </item>\n",
                    hash, node_get_key(node), node_get_value(node)
                );
        }
    }
    fprintf(stream, "    </data>\n");
    fprintf(stream, "</result>\n");
    return 1;
}

/**
 *  @fn Производит рехеширование.
 *      Реализовано квадратичное рехеширование.
 */
hash_t rehash(hash_t hash, size_t idx, size_t table_size) {
    return (hash + idx * idx) % table_size;
}

/**
 *  @fn Добавляет в таблицу node.
 *      На этот момент Node уже должен быть создан.
 *      Функция возвращает 1 в случае успеха
 *      и -1 в случае неуспеха.
 */
int htab_addnode(htab_t * this, node_t * const node) {
    hash_t hash;

    hash = node_hashing(node, this->_cap);
    while (this->_used[hash]) {
        if (!strcmp(node_get_key(this->data[hash]), node_get_key(node))) {
            return -1;
        }
        else {
            hash = rehash(hash, this->_idx, this->_cap);
            ++(this->_idx);
        }
    }
    this->data[hash] = node;
    this->_used[hash] = true;
    ++(this->size);
    if (this->size + 1 == this->_cap) {
        size_t newcap = this->_cap * 2;

        this->data = realloc(this->data, sizeof(node_t *) * newcap);
        this->_used = realloc(this->_used, sizeof(bool) * newcap);
        memset(this->data + this->_cap, 0, sizeof(node_t *) * this->_cap);
        memset(this->_used + this->_cap, 0, sizeof(bool) * this->_cap);
        this->_cap = newcap;
    }
    return 0;
}

/**
 *  @fn Ищет node по таблице.
 *      На этот момент в Node должен быть заполнен ключ.
 *      Возвращает hash для ключа node
 */
hash_t htab_findhash(htab_t * this, node_t * node) {
    hash_t hash;
    size_t f_id = 1;

    hash = node_hashing(node, this->_cap);
    while (strcmp(node_get_key(this->data[hash]), node_get_key(node)) != 0
           && f_id < this->_cap) {
        hash = rehash(hash, f_id, this->_cap);
        ++f_id;
    }
    return hash;
}

/**
 *  @fn Ищет node по таблице.
 *      На этот момент в Node должен быть заполнен ключ.
 *      Искомое значение возвращается в node->value.
 *      Сама функция возвращает 1 в случае успеха
 *      и -1 в случае неуспеха.
 */
int htab_findnode(htab_t * this, node_t * node) {
    hash_t hash = htab_findhash(this, node);

    if (!this->_used[hash])
        return -1;
    node->value = this->data[hash]->value;
    return 0;
}

/**
 *  @fn Удаляет из таблицы элемент с ключом от node.
 *      На этот момент в Node должен быть заполнен ключ.
 *      Сама функция возвращает 1 в случае успеха
 *      и -1 в случае неуспеха.
 */
int htab_delnode(htab_t * this, node_t * node) {
    hash_t hash = htab_findhash(this, node);

    if (!this->_used[hash])
        return -1;
    this->_used[hash] = false;
    node_destroy(this->data[hash]);
    this->data[hash] = NULL;
    --(this->size);
    return 0;
}

/**
 *  @fn Создает элемент хеш-таблицы.
 *      Инициализирует поля структуры.
 */
node_t *node_create() {
    node_t *node = malloc(sizeof(node_t));

    node->key = NULL;
    node->value = NULL;
    node->_buffer = NULL;
    return node;
}

/*
 * Функции, скрывают внутренне устройство node_t.
 * Это сделано для того, чтобы функции htab_ ничего не знали про элемент.
 * В случае, если мы захотим поменять node,
 * нам ничего не придется переделывать.
 */

char *node_get_key(node_t * node) {
    return node->key;
}

char *node_get_value(node_t * node) {
    return node->value;
}

void node_set_key(node_t * node, char *key) {
    node->key = key;
}

void node_set_value(node_t * node, char *value) {
    node->value = value;
}

/**
 *  @fn Считывает ключ и значение элемента таблицы со стандартного ввода.
 */
int node_fscan_all(FILE * stream, node_t * node) {
    int result = 0;

    if (node->_buffer) {
        free(node->_buffer);
    }
    node->_buffer = afgets(stream, NODE_BLOCKSIZE);
    if (!node->_buffer) {
        result = -1;
    }
    else {
        node->key = strtok(node->_buffer, " :");
        node->value = strtok(NULL, " :\n");
    }
    return result;
}

/**
 *  @fn Считывает ключ элемента таблицы со стандартного ввода.
 */
int node_fscan_key(FILE * stream, node_t * node) {
    int result = 0;

    if (node->_buffer) {
        free(node->_buffer);
    }
    node->_buffer = afgets(stream, NODE_BLOCKSIZE);
    if (!node->_buffer) {
        result = -1;
    }
    else {
        node->key = strtok(node->_buffer, " :\n");
    }
    return result;
}

/**
 *  @fn Вычисляет хеш для ключ элемента таблицы.
 */
hash_t node_hashing(node_t * const node, size_t table_size) {
    hash_t hash;
    size_t i;

    hash = 1;
    for (i = 0; i < strlen(node_get_key(node)); i++) {
        hash += node_get_key(node)[i] * sizeof(char);
    }
    return hash % table_size;
}

/**
 *  @fn Удаляет элемент хеш-таблицы.
 *      Освобождает память.
 */
void node_destroy(node_t * node) {
    if (!node)
        return;
    free(node->_buffer);
    node->_buffer = NULL;
    free(node);
    node = NULL;
}

/**
 * @fn  Считывает строку произвольного размера.
 *      Производит выделение памяти для строки.
 *      Строка считывается по блокам.
 *      В качестве параметров задаются входной поток и размер блока.
**/
char *afgets(FILE * stream, const size_t block_size) {
    char *result, *block, *temp;
    size_t size = block_size;
    size_t n = 0;

    result = block = (char *) malloc(size);
    if (!result)
        return NULL;
    *result = '\0';
    for (;;) {
        if (fgets(block, block_size, stream) == NULL)
            break;
        n += strlen(block);
        if (result[n - 1] == '\n')
            break;
        size += block_size;
        temp = (char *) realloc(result, size);
        if (temp == NULL)
            break;
        result = temp;
        block = result + n;
    }
    if (result[0] == '\0') {
        free(result);
        result = NULL;
    }
    return result;
}
