//
// Created by zhouyang on 16-10-13.
//

#include "basic_sort.h"
#include "shellsort.h"
#include "heapsort.h"
#include "mergesort.h"
#include "qsort.h"

#include <iostream>

using namespace std;

int main() {
    int a[10] = {9, 21, 123, 234, -1, -29, 100, 87, 99, -10};
    inssort(a, 10);
    for (auto val:a)
        cout << val << " ";
    cout << endl;

    int b[10] = {9, 21, 123, 234, -1, -29, 100, 87, 99, -10};
    bubsort(b, 10);
    for (auto val:b)
        cout << val << " ";
    cout << endl;

    int c[10] = {9, 21, 123, 234, -1, -29, 100, 87, 99, -10};
    selectsort(c, 10);
    for (auto val:c)
        cout << val << " ";
    cout << endl;

    int d[10] = {9, 21, 123, 234, -1, -29, 100, 87, 99, -10};
    shellsort(d, 10);
    for (auto val:d)
        cout << val << " ";
    cout << endl;

    int e[10] = {9, 21, 123, 234, -1, -29, 100, 87, 99, -10};
    heapsort(e, 10);
    for (auto val:e)
        cout << val << " ";
    cout << endl;

    int f[10] = {9, 21, 123, 234, -1, -29, 100, 87, 99, -10};
    mergesort(f, 10);
    for (auto val:f)
        cout << val << " ";
    cout << endl;

    int g[10] = {9, 21, 123, 234, -1, -29, 100, 87, 99, -10};
    qsort(g, 10);
    for (auto val:g)
        cout << val << " ";
    cout << endl;

    return 0;
}
