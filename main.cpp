#include <iostream>
#include <string>
#include "sequence.h"

using namespace std;

int sum_int(const int &a, const int &b) {
    return a + b;
}

int main(int, char**) {
    Sequence<string, int> przepis1;
    przepis1.push_front(string("lyzki cukru"), 3);
    przepis1.push_front(string("jajka"), 2);
    przepis1.push_front(string("szklanki mleka"), 2);
    przepis1.push_front(string("lyzki cukru"), 1);
    przepis1.print();

    Sequence<string, int> przepis2;
    przepis2.push_front(string("szklanki mleka"), 3);
    przepis2.push_front(string("lyzki cukru"), 2);
    przepis2.push_front(string("banany"), 2);
    przepis2.push_front(string("szklanki wody"), 2);
    przepis2.print();

    int (*fun_pointer)(const int&, const int&) = &sum_int;
    Sequence<string, int> output = join(przepis1, przepis2, fun_pointer);
    output.print();
    return 0;
}
