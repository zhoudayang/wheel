#ifndef SHELL_SORT
#define SHELL_SORT

#include <algorithm>

using std::swap;

void shellsort(int a[], int n) {
    //gap from n/2 to 1
    for (int gap = n / 2; gap > 0; gap >>= 1)
    {
        //i from gap to n
        for (int i = gap; i < n; i += 1)
        {
            //j from i to gap descrease by gap, if the element back gap pos is smaller, swap these two element
            for (int j = i; j >= gap && a[j] < a[j - gap]; j -= gap)
            {
                swap(a[j], a[j - gap]);
            }
        }
    }
}

#endif