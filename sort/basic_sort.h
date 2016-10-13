//
// Created by zhouyang on 16-10-13.
//

#ifndef BASIC_SORT_H
#define BASIC_SORT_H

#include <algorithm>

using std::swap;

//思路：从后往前插入，不停的交换，直至到达其正确的位置
void inssort(int a[], int n)
{
    for (int i = 1; i<n; ++i)
    {
        for (int j = i; j>0 && (a[j]<a[j-1]); --j)
        {
            swap(a[j], a[j-1]);
        }
    }
}

//冒泡排序
void bubsort(int a[], int n)
{
    for (int i = 0; i<n; i++)
    {
        for (int j = n-1; j>i; j--)
        {
            if (a[j]<a[j-1])
                swap(a[j], a[j-1]);
        }
    }
}

//选择排序，每次循环找到第i小的元素
void selectsort(int a[], int n)
{
    for (int i = 0; i<n-1; i++)
    {
        int min_index = i;
        for (int j = i+1; j<n; j++)
        {
            min_index = a[j]<a[min_index] ? j : min_index;
        }
        swap(a[i], a[min_index]);
    }
}

#endif
