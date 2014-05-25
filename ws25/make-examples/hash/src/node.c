#include "node.h"

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
