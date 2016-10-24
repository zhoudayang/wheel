#include <assert.h>
#include "binary_heap.h"


int main() {

    BinaryHeap<int> heap;
    vector<int> arr{1,-1,10,0,100,200,-100,300,1000};
    for(auto a:arr)
        heap.insert(a);
    int cur = 0;
    sort(arr.begin(),arr.end());
    while(!heap.isEmpty()){
        int a;
        heap.deleteMin(a);
        assert(a==arr[cur++]);
    }

}