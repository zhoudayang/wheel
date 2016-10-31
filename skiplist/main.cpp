#include "SkipList.h"
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>


using std::vector;
using std::cout;
using namespace zy;


int main(){

  int  len = 100000;
  cout<<"test begin, no assert error for okay!"<<std::endl;
  srand(time(nullptr));
  vector<int> arrs;

  for(int i=0;i<len;i++){
    arrs.push_back(rand());
  }

  SkipList<int> list1(20,0.5);

  //test insert
  for(auto value:arrs){
    list1.insert(value);
  }

  //test search
  for(auto value:arrs){
    assert(list1.search(value)!=nullptr);
  }

  //test order of element in skip list
  std::sort(arrs.begin(),arrs.end());
  int cur = 0;
  for(auto it = list1.begin();it!=list1.end();++it){
    assert((*it)==arrs[cur++]);
  }

  //test remove and search
  int mid = len>>1;

  for(int i=0;i<mid;++i){
    assert(list1.remove(arrs[i]));
  }

  for(int i=mid;i<len;++i){
    assert(list1.search(arrs[i])!=nullptr);
    assert(list1.remove(arrs[i]));
  }

  for(auto value:arrs){
    assert(!list1.search(value));
  }








}

