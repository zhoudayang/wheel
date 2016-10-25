//
// Created by zhouyang on 2016/10/25.
//

#ifndef SORT_HEAPSORT_H
#define SORT_HEAPSORT_H

#include <algorithm>

using std::swap;

void siftdown(int a[], int pos, int n) {
    //here l represent left child and r represent right child
    int l, r;
    while ((l = 2 * pos + 1) < n)
    {
        r = l + 1;
        //get bigger child
        if (r < n and a[r] > a[l])
            ++l;
        //if parent node is smaller than child node, swap them
        if (a[pos] < a[l])
        {
            swap(a[pos], a[l]);
            pos = l;
        }
            //else break
        else
            break;
    }
}

void heapsort(int a[], int n) {
    //build heap
    for (int i = n / 2 - 1; i >= 0; --i)
        siftdown(a, i, n);
    //swap heap front and it's back in each loop
    for (int j = n - 1; j > 0; --j)
    {
        swap(a[0], a[j]);
        siftdown(a, 0, j);
    }
}

#endif //SORT_HEAPSORT_H
