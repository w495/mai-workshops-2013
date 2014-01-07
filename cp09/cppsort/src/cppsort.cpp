
/**
 *      $> ./cppsort 
 *      5
 *      1 9
 *      9 1
 *      3 5
 *      5 4
 *      4 0
 *      
 *      1|9
 *      3|5
 *      4|0
 *      5|4
 *      9|1
 *
 *      1
 *      1 9
 *      9
 *      9 1
 * 
**/

#include<iostream>
#include<math.h>                // for pow
#include<vector>

using namespace std;

const int SIZE_OF_KEY = 4;
const int SIZE_OF_TYPE = 100;

int size_of_map = static_cast < int >(pow(2, SIZE_OF_KEY));

typedef int index;
typedef char data;
typedef data type[SIZE_OF_TYPE];

int number = 1;

struct OVER {
    OVER() {
        number = 0;
        std::clog << "OUT OF RANGE" << ends;
}};
struct arr {
    arr() {
        number = 0;
        std::clog << "ERROR SIZE" << ends;
}};

template < class IN, class TY > struct elem {
    IN in;
    TY item;
      elem() {
        in = 0;
}};


typedef elem < index, type > elem_type;

ostream & operator <<(ostream & out, elem_type a) {
    out << a.in << ' ' << a.item << ends;
    return out;
}

istream & operator >>(istream & in, elem_type & a) {
    in >> a.in;
    in >> a.item;
    return in;
}




void input(std::vector < elem_type > &t, int sio) {
    for (int i = 0; i != sio; i++) {
        std::cin >> t[i].in;
        std::cin >> t[i].item;
    }
    std::cout << '\n';
}

void liner_printf(std::vector < elem_type > &t, int sio) {
    for (int i = 0; i != sio; i++) {
        std::cout << t[i].in << ends << '|' << ends;
        std::cout << t[i].item << endl;
    }
}

void CountPrinting
    (std::vector < elem_type > &t, std::vector < int >&count, int sio) {
    for (int i = 0; i != sio; i++)
        for (int j = 0; j != sio; j++)
            if (count[j] == i) {
                std::cout << t[j] << endl;
            }
}

void CountConvert(std::vector < elem_type > &t,
                  std::vector < int >&count,
                  std::vector < elem_type > &out, int sio) {
    for (int i = 0; i != sio; i++)
        for (int j = 0; j != sio; j++)
            if (count[j] == i)
                out[i] = t[j];

}



// There are different tools 
// that may be usefull in debugig
// and explor the main algorith.
// It you can see at the end
// of NAMESPACE

void CountSelection
    (std::vector < elem_type > &t, std::vector < int >&count, int sio) {
    for (int i = 0; i != sio; i++)
        count[i] = 0;

    for (int i = 0; i != sio - 1; i++) {
        for (int j = i + 1; j != sio; j++) {
            if (t[i].in < t[j].in)
                count[j]++;
            else
                count[i]++;
        }
    }
}


elem_type & bin_search(std::vector < elem_type > &t, index what, int sio) {
    index left = 0;
    index right = static_cast < index > (sio);
    index middle = 0;
    bool found_flag = false;

    while (left <= right && !found_flag) {
        middle = (left + right) / 2;
        if (t[middle].in == what) {
            found_flag = true;
        }
        else if (t[middle].in < what)
            left = middle + 1;
        else
            right = middle;
    }
    return t[middle];
}

bool is(index a, std::vector < elem_type > &t, int sio) {
    for (int i = 0; i != sio; i++)
        if (a == t[i].in)
            return true;

    return false;
}

int main() {
    std::vector < elem_type > table(size_of_map);
    std::vector < elem_type > sorted_table(size_of_map);

    int size_of_input;

    std::cin >> size_of_input;

    if (size_of_input <= 0)
        throw arr();
    std::vector < int >count_sorter(size_of_input);

    input(table, size_of_input);

    CountSelection(table, count_sorter, size_of_input);
    CountConvert(table, count_sorter, sorted_table, size_of_input);
    liner_printf(sorted_table, size_of_input);

    for (;;) {
        int key = 0;

        std::cin >> key;
        if (key) {
            if (!is(key, sorted_table, size_of_input))
                OVER();
            else
                std::cout << bin_search(sorted_table, key, size_of_input);
        }
        else
            break;
    }

    std::cout << endl;


    return 1;
}
