#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

//lower_bound算法要求在已经按照非递减顺序排序的数组中找到第一个大于等于给定值key的那个数，其基本实现原理是二分查找
int lower_bound(const vector<int> & arr,int key){
  int half;
  int mid;
  int len = arr.size();
  int first = 0 ;
  while(len>0) {
    half = len >> 1;
    mid = first + half;
    if(arr[mid] >= key){
      len = half;
    }
    else{
      first = mid +1;
      len = len - half - 1;
    }
  }
  return first;
}
//upper_bound函数要求在按照非递减顺序排好序的数组中找到第一个大于给定值key的那个数，其基本实现原理是二分查找
int upper_bound(const vector<int> & arr,int key){
  int first = 0;
  int mid;
  int len = arr.size();
  int half;
  while(len>0){
    half = len>>1;
    mid = first + half;
    if(arr[mid]<= key){
      first = mid +1;
      len = len-half -1;
    }
    else{
      len = half;
    }
  }
  return first;
}


int main() {
  vector<int> arr{-1,0,1,1,2};
  cout<<lower_bound(arr,1)<<endl;
  cout<<upper_bound(arr,1)<<endl;
  return 0;
}
