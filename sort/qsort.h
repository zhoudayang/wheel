//
// Created by zhouyang on 2016/10/25.
//

#ifndef SORT_QSORT_H
#define SORT_QSORT_H

#include <algorithm>

using std::swap;

int partition(int a[], int l, int r, int &pivot) {
    while (l < r)
    {
        while (a[l] < pivot)//找到a[l]>=pivot
            l++;
        while (r > l && a[r] >= pivot)//找到a[r]<piovt
            r--;
        swap(a[l], a[r]);//交换a[l],a[r]
    }//l和r相遇的位置就是划分点最后该待在的位置
    return l;
}

//快速排序
void qsort(int a[], int i, int j) {
    if (i >= j)
        return;
    //取哪个位置作为划分点
    int pivotindex = (i + j) / 2;
    //将划分点元素移到数目末尾
    swap(a[pivotindex], a[j]);
    //调用partition函数，保证k左边的元素比a[j]小，右边的元素比a[j]大(或者等于)
    int k = partition(a, i, j, a[j]);
    //将pivot移动到合适的位置
    swap(a[k], a[j]);
    //递归对pivot左右半边数组调用qsort函数
    qsort(a, i, k - 1);
    qsort(a, k + 1, j);
}

void qsort(int a[], int n) {
    qsort(a, 0, n - 1);
}



#endif //SORT_QSORT_H
