#pragma once
#include <vector>

inline void merge(int a[], int p, int mid, int q)
{
  int size = q - p + 1;
  std::vector<int> arrs;
  arrs.reserve(size);
  for(int i = p; i <= mid; ++i)
  {
    arrs.push_back(a[i]);
  }
  for(int i = q; i > mid; --i)
  {
    arrs.push_back(a[i]);
  }

  for(int i = 0, j = size - 1, k = p; k <= q; ++k)
  {
    if(arrs[i] < arrs[j])
    {
      a[k] = arrs[i++];
    }
    else
    {
      a[k] = arrs[j--];
    }
  }
}

// no vector used
inline void merge1(int a[], int l, int mid, int r)
{
  int arrs[r+1];
  for(int i = l; i <= mid; ++i)
    arrs[i] = a[i];
  for(int i = r, j = mid + 1; i > mid; --i)
    arrs[j++] = a[i];
  for(int i = l, j = r, k = l; k <= r; ++ k)
  {
    if(arrs[i] < arrs[j])
    {
      a[k] = arrs[i++];
    }
    else
      a[k] = arrs[j--];
  }
}

void mergesort(int a[], int p, int q)
{
  if(p >= q)
    return;
  int mid = p + q;
  mid >>= 1;
  mergesort(a, p, mid);
  mergesort(a, mid + 1, q);
  merge(a, p, mid, q);
}

inline void mergesort(int a[], int n) {
  mergesort(a, 0, n - 1);
}

