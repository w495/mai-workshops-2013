#include "htab.h"

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
    return 0;
}

