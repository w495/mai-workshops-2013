#include<iostream>

template < class T > class list {
    list < T > *next;
    list < T > *prev;
  public:
    struct elem {
        elem(T x = 0) {
            data = x;
        } elem *next;
        elem *prev;
        T data;
    };
    list() {
        next = prev = this;
    }

    elem *find(T x, elem * tmp = 0);
    int push_back(T x);
    int insert(T s, T x);
    int erase(T x);
    int erase(elem * hs);
    int erase(T x, T y);
    int size();
    void show();
};

template < class T > int list < T >::push_back(T x) {
    elem *hs = new elem(x);

    if (!hs)
        return 0;
    prev->next = (list < T > *)hs;
    hs->prev = (elem *) (prev);
    hs->next = (elem *) (this);
    prev = (list < T > *)(hs);
    return 1;
}

template < class T >
typename list < T >::elem * list < T >::find(T x, elem * tmp) {
    elem *hs;

    if (tmp == 0) {
        hs = (elem *) (this->next);
    }
    else {
        hs = tmp->next;
    }

    while (hs->data != x && hs != (elem *) (this)) {
        hs = hs->next;
    }
    if (hs != (elem *) (this)) {
        return hs;
    }
    return 0;
}

template < class T > int list < T >::insert(T s, T x) {
    elem *rhs = find(s);

    if (rhs == 0)
        return 0;
    elem *hs = new elem(x);

    if (!hs)
        return 0;
    rhs->prev->elem::next = hs;
    hs->prev = (elem *) (rhs->prev);
    hs->next = rhs;
    rhs->prev = hs;
    return 1;
}

template < class T > int list < T >::erase(elem * hs) {
    if (!hs)
        return 0;
    hs->next->prev = (elem *) (hs->prev);
    hs->prev->next = (elem *) (hs->next);
    delete hs;

    return 1;
}

template < class T > int list < T >::erase(T x) {
    if (erase(find(x)))
        return 1;
    return 0;
}

template < class T > int list < T >::erase(T x, T y) {
    elem *lhs = find(x);

    if (!lhs)
        return 0;
    elem *rhs = find(y);

    if (rhs == 0)
        rhs = (elem *) (this);
    elem *tmp = lhs->next;

    for (elem * hs = lhs; hs != rhs && hs != (elem *) (this); tmp = tmp->next) {
        erase(hs);
        hs = tmp;
    }
    return 1;
}

template < class T > void list < T >::show() {
    elem *hs = (elem *) (next);

    while (hs != (elem *) (this)) {
        std::cout << hs->data << '\n';
        hs = hs->next;
    }
}

template < class T > int list < T >::size() {
    elem *hs = (elem *) (next);
    int size = 0;

    while (hs != (elem *) (this)) {
        hs = hs->next;
        size++;
    }
    return size;
}

int main() {
    list < int > ls;
    int i, d, m, tmp, b, v;

    std::cout << "Enter number of items:\n";
    std::cin >> m;
    std::cout << "Enter " << m << " items to list\n";
    for (i = 0; i < m; i++) {
        std::cout << "Enter item #: " << i + 1 << '\n';
        std::cin >> d;
        ls.push_back(d);
    }
    std::cout << "list:\n";
    ls.show();
    std::cout << "size:\n";
    std::cout << ls.size() << '\n';
    for (;;) {
        std::cout <<
            "Enter 1 for insert or 2 for erase or 3 for show "
            "of list or 4 for erase of range or other for exit:\n";
        std::cin >> tmp;
        if (tmp == 1) {
            if (ls.size() != 0) {
                std::cout <<
                    "Enter enter prev item, before which you wanna insert "
                    "a new item, and then enter this item.\n";
                std::cin >> b >> v;
                ls.insert(b, v);
            }
            else {
                std::cout << "Enter item:\n";
                std::cin >> v;
                ls.push_back(v);
            }
        }
        else if (tmp == 2) {
            std::cout << "Enter item for delete:\n";
            std::cin >> v;
            if (!ls.erase(v)) {
                std::cout << "No such items\n";
                continue;
            }
        }
        else if (tmp == 3) {
            std::cout << "list:\n";
            ls.show();
            std::cout << "size:\n";
            std::cout << ls.size() << '\n';
        }
        else if (tmp == 4) {
            std::cout << "Enter top and down:\n";
            std::cin >> b >> v;
            if (!ls.erase(b, v)) {
                std::cout << "No down\n";
            }
        }
        else
            break;
    }
    return 0;
}
