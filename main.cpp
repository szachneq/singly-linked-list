#include <iostream>
#include "sequence.h"

using namespace std;

int main(int, char**) {
    Sequence<int, int> *test = new Sequence<int, int>;
    test->push_front(1, 2);
    test->push_front(3, 4);
    test->print();

    Sequence<int, int> test2 = *test;
    test2.print();

    delete test;
    test2.print();
    cout << test2.size() << endl;

    return 0;
}
