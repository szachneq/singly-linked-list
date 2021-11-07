#include <iostream>
#include "sequence.h"

using namespace std;

int main(int, char**) {
    cout << "Hello, world!\n";
    Sequence<int, int> test;
    test.print();
    return 0;
}
