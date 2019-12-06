
/*
1. Implement a function string* findBin(int n) which will generate binary numbers from 1 to n in the form of a string using a queue.
    Solution:   //Start with Enqueuing 1.
        //Dequeue a number from queue and append 0 to it and enqueue it back to queue.
        //Perform step 2 but with appending 1 to the original number and enqueue back to queue.
        //Queue takes integer values so before enqueueing it make sure to convert string to integer.
        //Size of Queue should be 1 more than number because for a single number we're enqueuing two
        //variations of it , one with appended 0 while other with 1 being appended.


Challenge 2 : Implement Two Stacks using one Array

Challenge 3: Reversing First k Elements of Queue
    Solution: //1.Push first k elements in queue in a stack.
              //2.Pop Stack elements and enqueue them at the end of queue
              //3.Dequeue queue elements till "k" and append them at the end of queue  

Challenge 4 : Implement a Queue Using Stacks

Challenge 5 : Sort Values in a Stack


*/    

#include<iostream>
#include<string>
// #include<queue>

using std::string;
using std::endl;
using std::cout;
using std::to_string;
// using std::queue;

class myQueue {
private:
    int * queueArr;
    int capacity;
    int numElements;
    int front;
    int back;
public:
    myQueue(int size);
    bool isEmpty();
    int getFront();
    void enqueue(int value);
    int dequeue();
    int getSize();
};

myQueue::myQueue(int size) {
    capacity = size;
    queueArr = new int[size];
    numElements = 0;
    front=0;
    back=-1;

}

bool myQueue::isEmpty() {
    return (numElements==0);
}

int myQueue::getFront() {
    if (numElements == 0) {
        cout << "Queue Empty" << endl;
        return -1;
    } else
        return queueArr[front];
}

void myQueue::enqueue(int value) {
    if(numElements==capacity){
        cout << "Stack Full" <<endl;
        return;
    }

    if(back==capacity-1)
        back=-1;

    queueArr[++back]=value;
    numElements++;
}

int myQueue::dequeue() {
    if(numElements==0) {
        cout <<"Stack Empty"<<endl;
        return -1;
    }
    int tmp=queueArr[front++];

    if(front==capacity)
        front=0;
    numElements--;
    return tmp;

}
int myQueue::getSize() {
    return numElements;
}
void showqueue(myQueue s) {
    cout<< "The queue is: " << endl;
    while (!s.isEmpty()) {

        cout << '\t' << s.getFront();
        s.dequeue();
    }
    cout << '\n';
}

string* findBin(int n) {
    string *result=new string[n];
    // myQueue my_queue(n + 1);
    myQueue my_queue(n + 1);
    my_queue.enqueue(1);

    string s1,s2;
    for (int i = 0; i < n; i++) {
        result[i] = to_string(my_queue.dequeue());
        s1 = result[i] + "0";
        s2 = result[i] + "1";
        my_queue.enqueue(stoi(s1));
        my_queue.enqueue(stoi(s2));
    }

    return result;
}

int main_findBin()
{ 
  auto output=findBin(3);
  for(int i=0;i<3;i++)
    cout << output[i] <<" ";
    return 0;
}

//---------------//
//You can either divide array in two halves or start stacks at extreme ends.
//We'll use the second technique to solve this problem. 
//Top of Stack 1 start from extreme left of array i.e top1 = 0;
//Top of Stack 2 start from extreme right of array i.e top2 = size - 1;
class twoStacks {

private:
    int size;
    int *arr;
    int top1, top2;
    //Store top value indices of Stack 1 and Stack 2
public:
    twoStacks(int n) {
        size = n;
        arr = new int[size];
        top1 = -1;
        top2 = size;

    }
  //Insert Value in First Stack  
    void push1(int value) {
      //Check for empty space and insert value if there's an empty space.
        if (top1 < top2 - 1) {
            arr[++top1] = value;
        }
    }
 //Insert Value in Second Stack  
    void push2(int value) {
      //Check for empty space and insert value if there's an empty space.
        if (top1 < top2 - 1) {
            arr[--top2] = value;
        }
    }

    //Return and remove top Value from First Stack
    int pop1() {
      //Get value from top1 index and increment it.
        if (top1 >=0) {
            int val = arr[top1--];
            return val;
        }
        return - 1;
    }

    //Return and remove top Value from Second Stack
    int pop2() {
        //Get value from top2 index and increment it.
        if (top2 < size) {
            int val = arr[top2++];
            return val;
        }
        return - 1;
    }
};

int main_twoStacks_OneArray(){
  
   twoStacks tS(5);
    tS.push1(11);
    tS.push1(3);
    tS.push1(7);
    tS.push2(1);
    tS.push2(9);
  
  cout << tS.pop1() << endl;
  cout << tS.pop2() << endl;
  cout << tS.pop2() << endl;
  cout << tS.pop2() << endl;
  cout << tS.pop1() << endl;

  return 0; 
}

//-----//
#include<stack>
using std::stack;

void insert(stack<int> & myStack, int value){
  if(myStack.empty()|| value < myStack.top())
    myStack.push(value);
  else{
    int temp = myStack.top();
    myStack.pop();
    insert(myStack,value);
    myStack.push(temp);
  }
     
}

void sortStack(stack<int>& myStack) {
    if(!myStack.empty()){
    int value=myStack.top();
    myStack.pop();
    sortStack(myStack);
    insert(myStack,value);
    }
 
}



int main(){
    stack<int> myStack;
    myStack.push(2);
    myStack.push(97);
    myStack.push(4);
    myStack.push(42);
    myStack.push(12);
    myStack.push(60);
    myStack.push(23);
    sortStack(myStack);
    // showstack(myStack);
    cout<<myStack.top()<<endl;
}