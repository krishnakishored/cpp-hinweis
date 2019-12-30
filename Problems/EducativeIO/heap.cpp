#include <iostream>
#include <vector>
using namespace std;

/*
1. Convert MaxHeap to MinHeap
2. Find k smallest elements in a List
3. Find k largest elements in the Vector
*/


template <typename T>
class MaxHeap{
  private:
  vector<T> h;
  
  inline int parent(int i){
    return (i-1)/2;
  }
  inline int lchild(int i){
    return i*2 + 1;
  }
  inline int rchild(int i){
    return i*2 + 2;
  }
  
  //percolateUp()t is meant to restore the 
  //heap property going up from a node to the root.
  void percolateUp(int i){
    if(i <= 0)
      return;
    else if(h[parent(i)] < h[i]){
      swap(h[i], h[parent(i)]);
      percolateUp(parent(i));
    }
  }
  
  public:
  
  MaxHeap(){
    h.resize(0);
  }
  
  int size(){
    return h.size() - 1;
  }
  
  T getMax(){
    return h[0];
  }
  
  void insert (const T &key){
    h.push_back(key);
    int i = size();
    
    percolateUp(i);
  }
  
  void maxHeapify(int i){
    int lc = lchild(i);
    int rc = rchild(i);
    int imax = i;
    
    if(lc <= size()  &&  h[lc] > h[imax])
      imax = lc;
    if(rc <= size()  &&  h[rc] > h[imax])
      imax = rc;
    if(i != imax){
      swap(h[i], h[imax]);
      maxHeapify(imax);
    }
  }
  
  void removeMax(){
    if(size() > 0){
      swap(h[0], h[size()]);
      h.pop_back();
      maxHeapify(0);
    }
  }
  //Bonus function: printHeap()
  void printHeap(){
    for(int i = 1; i <= size(); i++){
      cout << h[i] << " ";
    }
    cout << endl;
  }
};

int main_MaxHeap() {
  MaxHeap<int> heap;
  heap.insert(2);
  heap.insert(8);
  heap.insert(15);
  heap.insert(5);
  heap.insert(1);
  heap.insert(20);
  //heap.printHeap();
  cout << heap.getMax() << endl;
  heap.removeMax();
  cout << heap.getMax() << endl;
  heap.removeMax();
  cout << heap.getMax() << endl;
  heap.insert(1000);
  cout << heap.getMax() << endl;
  
  return 0;
}


template <typename T>

class MinHeap{
  private:
  vector<T> h;
  
  inline int parent(int i){
    return (i-1)/2;
  }
  inline int lchild(int i){
    return i*2 + 1;
  }
  inline int rchild(int i){
    return i*2 + 2;
  }
  
  void minHeapify(int i){
    int lc = lchild(i);
    int rc = rchild(i);
    int imin = i;
    
    if(lc <= size()  &&  h[lc] < h[imin])
      imin = lc;
    if(rc <= size()  &&  h[rc] < h[imin])
      imin = rc;
    if(i != imin){
      swap(h[i], h[imin]);
      minHeapify(imin);
    }
  }
  
  //percolateUp(): It is meant to restore the 
  //heap property going up from a node to the root.
  void percolateUp(int i){
    if(i <= 0)
      return;
    else if(h[parent(i)] > h[i]){
      swap(h[i], h[parent(i)]);
      percolateUp(parent(i));
    }
  }
  
  public:
  
  MinHeap(){
    h.resize(0); 
  }
  
  int size(){
    return h.size() - 1;
  }
  
  T getMin(){
    return h[0];
  }
  
  void insert (const T &key){
    h.push_back(key);
    int i = size();
    
    percolateUp(i);
  }
  
  void removeMin(){
    if(size() > 0){
      swap(h[0], h[size()]);
      h.pop_back();
      minHeapify(0);
    }
  }
  
  //Bonus function: printHeap()
  void printHeap(){
    for(int i = 0; i <= size(); i++){
      cout << h[i] << " ";
    }
    cout << endl;
  }
};

int main_MinHeap() {
  MinHeap<int> heap;
  heap.insert(2);
  heap.insert(8);
  heap.insert(15);
  heap.insert(5);
  heap.insert(1);
  heap.insert(20);
  cout << heap.getMin() << endl;
  heap.removeMin();
  cout << heap.getMin() << endl;
  heap.removeMin();
  
  heap.insert(-10);
  cout << heap.getMin() << endl;
  
  return 0;
}


//-------------- Challenges ----------------

void minHeapify(vector<int> &h, int i){
  int lc = i*2 + 1;
  int rc = i*2 + 2;
  int imin = i;

  if(lc <= h.size()-1  &&  h[lc] < h[imin])
    imin = lc;
  if(rc <= h.size()-1  &&  h[rc] < h[imin])
    imin = rc;
  if(i != imin){
    swap(h[i], h[imin]);
    minHeapify(h, imin);
  }
}
        
vector<int> buildMinHeap(vector<int> heapList){
  for(int i = (heapList.size()-1)/2; i > -1; i--){
    minHeapify(heapList, i);
  }
  return heapList;
}

string convertMax(vector<int> maxHeap){
  string result = "";
  
  maxHeap = buildMinHeap(maxHeap);
  for(int i = 0; i < maxHeap.size(); i++){
    if (i == maxHeap.size() - 1)
      result += to_string(maxHeap[i]);
    else
      result += to_string(maxHeap[i]) + ",";
  }
  return result;
}

int main_ConvertMax(){
  vector<int> heapList = {9,4,7,1,-2,6,5};
  cout << convertMax(heapList);
  
  return 0;
}



vector<int> findKSmallest(vector<int> arr, int k){
  
  MinHeap<int> heap;
  
  for(int i = 0; i < arr.size(); i++){
    heap.insert(arr[i]);
  }
  
  vector<int> output;
  for(int i = 0; i < k; i++){
    output.push_back(heap.getMin());
    heap.removeMin();
  }

  return output;
}

int main_findKSmallest(){
  vector<int> input = {9, 4, 7, 1, -2, 6, 5};
  auto output = findKSmallest(input, 3);
  
  for(int i = 0; i < output.size(); i++){
    cout << output[i] << " "; 
  }
  
  return 0;
}

vector<int> findKLargest(vector<int> arr, int k){
  
  MaxHeap<int> heap;
  
  for(int i = 0; i < arr.size(); i++){
    heap.insert(arr[i]);
  }
  
  vector<int> output;
  for(int i = 0; i < k; i++){
    output.push_back(heap.getMax());
    heap.removeMax();
  }

  return output;
}

int main_findKLargest(){
  vector<int> input = {9, 4, 7, 1, -2, 6, 5};
  auto output = findKLargest(input, 2);
  
  for(int i = 0; i < output.size(); i++){
    cout << output[i] << " "; 
  }
  
  return 0;
}

int main()
{
    // main_MinHeap();
    // main_MaxHeap();

    // main_ConvertMax();
    // main_findKSmallest();
    main_findKLargest();
    return 0;
}




