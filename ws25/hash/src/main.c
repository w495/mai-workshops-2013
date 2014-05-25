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
 *          $> ./hash
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

#include "htab.h"

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
