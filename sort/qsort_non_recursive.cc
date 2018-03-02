#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int partition(vector<int>& arr, int l, int r, int pivot)
{
  while(l < r)
  {
    while(arr[l] < pivot)
      ++ l;
    while(r > l && arr[r] >= pivot)
      -- r;
    swap(arr[l], arr[r]);
  }
  return l;
}

/// 要点，将参数保存到堆栈之中，利用堆栈模拟递归函数
void qsort(vector<int>& arr, int l, int r)
{
  stack<int> st;

  st.push(l);
  st.push(r);

  while(!st.empty())
  {
    int right = st.top();
    st.pop();
    int left = st.top();
    st.pop();
    // 跳过不符合规范的情况
    if(left >= right)
      continue;
    int pivot_index = (left + right) / 2;
    int pivot = arr[pivot_index];
    swap(arr[pivot_index], arr[right]);
    int pos = partition(arr, left, right, pivot);
    swap(arr[right], arr[pos]);
    st.push(left);
    st.push(pos - 1);
    st.push(pos + 1);
    st.push(right);
  }
}

int main()
{
  vector<int> arrs { -1, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 100 };
  qsort(arrs, 0, arrs.size() - 1);
  for(auto& val : arrs)
  {
    cout << val << endl;
  }
  return 0;
}
