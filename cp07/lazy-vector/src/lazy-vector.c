#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <string.h> // для memset и memcmp

const size_t CAPACITY_COEF = 2;

typedef int T;

typedef struct {
    T* data;
    // Используем size_t, это встроенный тип,
    // обычно синоним к unsigned long int.
    size_t size;
    size_t capacity;
} Vector;

///
/// @fn Заполняет вектор нулями.
///     Внутренняя функция.
///     Делает это вручную --- последовательно.
///
void __Fill(Vector* this, size_t start, size_t stop) {
    for (size_t i = start; i != stop; ++i)
        this->data[i] = 0;
}

///
/// @fn Заполняет вектор нулями через `memset`.
///     Внутренняя функция.
///     Делает это быстро, с помощью библиотечной функции.
///
void __FillFast(Vector* this, size_t start, size_t stop) {
    size_t size = stop - start;
    memset(this->data + start, 0, sizeof(T) * size);
}

///
/// @fn Создает вектор.
///     И заполняет вектор нулями.
///
Vector* Create(size_t sz) {
    Vector* this = malloc(sizeof(Vector));
    this->size = sz;
    this->capacity = CAPACITY_COEF * this->size;
    //
    // Хорошо бы проверять что мы вообще можем выполнить malloc.
    // В некоторых случаях это не получится.
    //
    this->data = malloc(sizeof(T) * this->capacity);
    __FillFast(this, 0, this->size);
    return this;
}

///
/// @fn Бодро перераспределяет память под вектор.
///     Делает это бодро.
///     Новая часть вектора заполняется нулями.
///
void Resize(Vector* this, int sz) {
    this->data = realloc(this->data, sizeof(T) * sz);
    __Fill(this, this->size, sz);
    this->size = sz;
}

///
/// @fn Лениво перераспределяет память под вектор.
///     Ленивыми бывают не только программисты, но и вычисления.
///     Новая часть вектора заполняется нулями.
///
void LazyResize(Vector* this, size_t sz) {

    //
    //  Если текущего значения capacity нам достаточно,
    //  то выделения памяти не происходит.
    //
    if(this->capacity > sz) {
        // Ничего не делаем
    }
    //
    //  Если capacity нам мало, то выделяем память
    //  в несколько раз больше.
    //  Мы это делаем, чтобы выделять память как можно реже,
    //  потому, что это очень дорогая операция.
    //
    else {
        this->capacity = CAPACITY_COEF * this->capacity;
        //
        //  Хорошо бы проверять что мы вообще можем выполнить realloc.
        //  В некоторых случаях это не получится.
        //
        this->data = realloc(this->data, sizeof(T) * this->capacity);

    }
    __Fill(this, this->size, sz);
    this->size = sz;
}

///
/// @fn Возвращает i-ую ячейку из вектора.
///     В случае, выхода за диапазон вектора прерывает программу.
///
T Load(Vector* this, size_t i) {
    if ((i >= 0) && (i < this->size))
        return this->data[i];
    fprintf(stderr, "Out of range! Aborting...\n");
    exit(EXIT_FAILURE);
}

///
/// @fn Записывает значение t в ячейку i вектора .
///     В случае, выхода за диапазон ничего не делает.
///     На самом деле тут можно возвращать true или false,
///     в зависимости записали мы что-то или нет.
///     Или например довыделять память (лениво, т.е. по-умному),
///     если i больше
///
void Save(Vector* this, size_t i, T t) {
    if ((i >= 0) && (i < this->size))
        this->data[i] = t;
}

///
/// @fn Проверяет векто на пустоту.
///
bool IsEmpty(Vector* this) {
    return this->size == 0;
}

///
/// @fn Возвращает размер вектора.
///
size_t GetSize(Vector* this) {
    return this->size;
}

///
/// @fn Возвращает размер, который вектор реально занимает в памяти.
///
size_t GetCapacity(Vector* this) {
    return this->capacity;
}


///
/// @fn Сравнивает 2 вектора.
///
bool IsEqual(Vector* l, Vector* r) {
    if (l->size != r->size)
        return false;
    for (size_t i = 0; i < l->size; ++i)
        if (l->data[i] != r->data[i])
            return false;
    return true;
}

///
/// @fn Сравнивает 2 вектора через `memcmp`.
///
bool IsEqualFast(Vector* l, Vector* r) {
    if (l->size != r->size)
        return false;
    if(memcmp(l->data, r->data, l->size * sizeof(T)))
        return false;
    return true;
}

///
/// @fn Уничтожает вектор.
///
void Destroy(Vector* this) {
    this->size = 0;
    free(this->data);
    this->data = NULL;
}

int main() {
    size_t size_v;
    printf("Input size of vector, please: ");
    scanf("%lu", &size_v);

    Vector *my_vector = Create(size_v);

    printf("1)  Size     :%lu\n", GetSize(my_vector));
    printf("    Capacity :%lu\n", GetCapacity(my_vector));

    printf("If you are weary enter values, then enter: 100500\n");
    printf("So, start!!!\n");
    size_t i = 0;
    for (;;) {
        int value;
        scanf("%d", &value);
        if (value == 100500)
            break;

        printf("2)  Size     :%lu\n", GetSize(my_vector));
        printf("    Capacity :%lu\n", GetCapacity(my_vector));
        printf("    i        :%lu\n", i);

        if (GetSize(my_vector) == i) {
            LazyResize(my_vector, i+1);
            printf("!!! Resize \n");
        }

        printf("3)  Size     :%lu\n", GetSize(my_vector));
        printf("    Capacity :%lu\n", GetCapacity(my_vector));
        printf("    i        :%lu\n", i);

        Save(my_vector, i, value);
        ++i;
        getchar();
    }
    for (size_t i = 0; i < GetSize(my_vector); ++i)
        printf("%d ", Load(my_vector, i));
    printf("\n");
    Destroy(my_vector);
}
