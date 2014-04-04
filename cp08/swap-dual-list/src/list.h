#ifndef __LIST_H__
#define __LIST_H__
// Автор: Александр Балес

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct Item {
    struct Item *prev;
    struct Item *next;
    int data;
};

typedef struct {
    struct Item *head;
    int size;
} List;

typedef struct {
    struct Item *node;
} Iterator;

typedef struct Item _Item_;

void helper();
bool list_Create(const List * l);
void Create(List * l);
Iterator First(const List * l);
Iterator Last(const List * l);
bool Empty(const List * l);
int Size(const List * l);
void Insert(List * l, Iterator * i, const int t);
void Delete(List * l, Iterator * i);
void Destroy(List * l);
void print_List(List * l);
bool Equal(const Iterator * lhs, const Iterator * rhs);
int length_of_List(List * l);
bool find_Items_Index(List * l, Iterator * i, const int val);
bool find_Items_Data(List * l, Iterator * i, const int val);
void my_swap(List * l, Iterator * i);
void my_getint(int *Val, bool * flag);

#endif
