#ifndef MERGESORT_H
#define MERGESORT_H

void mergesort(int a[], int l, int r) {
    //if l >= r, return at once, this is the minimum problem, cannot split again
    if (l >= r)
        return;
    //divide problem by half
    int middle = (l + r) >> 1;
    //sort left half
    mergesort(a, l, middle);
    //sort right half
    mergesort(a, middle + 1, r);
    //init temporary array
    int *temp = new int[r + 1];
    //copy left half of the array directly
    for (int i = 0; i <= middle; ++i)
        temp[i] = a[i];
    int cur = middle + 1;
    //copy right half of the array from end to begin
    for (int i = r; i > middle; --i)
        temp[cur++] = a[i];
    //merge two array
    for (int i = l, j = r, k = l; k <= r; ++k)
    {
        if (temp[i] < temp[j])
            a[k] = temp[i++];
        else
            a[k] = temp[j--];
    }
}

void mergesort(int a[], int n) {
    mergesort(a, 0, n - 1);
}


#endif