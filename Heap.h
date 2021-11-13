#ifndef HEAP_H
#define HEAP_H
#include <string>
#include <fstream>
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

template <typename T>

class Heap{
    private:
        int size = 0;
        
        bool isMaxHeap = 0; // indicator of heap type. min = 0. max = 1 
        // helper function
        void bblUpMax(int idx);
        void bblUpMin(int idx);
        void bblDown(int idx);
        void exchange(int idx1, int idx2);
        void extreValue();
        T max;
        T min;      

    public:

        vector<T> heap;

        Heap(); // default to be minheap
        Heap(int indicator); // if indicator > 0 max heap, else minheap

        //  public function
        int insert(T number); //return 1 when success, 0 when fail
        int remove(T number); //return 1 when success, 0 when fail
        T get_root();
        T extract_root(); //return the root value 
        T get_min(); //return the min value
        T get_max(); //return the max value
        int get_size();//return the size
        bool search(T number); //return true if found, false if not found

};

#endif



//constructors
template <typename T>
Heap<T>::Heap(){
    // do nothing
    // min heap by default
    cout<<"[Heap]: default construct"<<endl;
}
template <typename T>
Heap<T>::Heap(int indicator){
    // distinguish heap type
    // if indicator > 0 max heap, else minheap
    if(indicator > 0){
        this->isMaxHeap = 1;
    }else{
        this->isMaxHeap = 0;
    }
    //cout<<"[Heap]: isMaxHeap:  "<< this->isMaxHeap << endl;
} 

// helper function
template <typename T>
void Heap<T>::bblUpMax(int idx){
    // if root: return<T>
    if(idx == 0) return;
    //max heap: parent > child
    // 1. locate the new child by index
    T childValue = heap[idx];
    // 2. find its parent
    int parentIndex = floor(((idx - 1) / 2));
    T parentValue = heap[parentIndex];
    // 3. compare 
    if(childValue > parentValue){
        // cout<<"[bblUpMax]: "<< idx << endl;
        // 3.1  if child larger than parent, switch,
        // 3.1  call bblUpMax with new parent idx
        exchange(idx, parentIndex);
        bblUpMax(parentIndex);
    }
    // 3.2 if sorted, return

}
template <typename T>
void Heap<T>::bblUpMin(int idx){
    
    // if root: return
    if(idx == 0) return;
    //max heap: parent > child
    // 1. locate the new child by index
    T childValue = heap[idx];
    // 2. find its parent
    int parentIndex = floor(((idx - 1) / 2));
    T parentValue = heap[parentIndex];
    // 3. compare 
    if(childValue < parentValue){
        //cout<<"[bblUpMin]: "<< idx << endl;
        // 3.1  if child larger than parent, switch,
        // 3.1  call bblUpMax with new parent idx
        exchange(idx, parentIndex);
        bblUpMin(parentIndex);
    }
    // 3.2 if sorted, return
}
template <typename T>
void Heap<T>::exchange(int idx1, int idx2){
    T temp = heap[idx1];
    heap[idx1] = heap[idx2];
    heap[idx2] = temp;
}
template <typename T>
void Heap<T>::bblDown(int idx){
    // find value of the idx
    T idxValue = heap[idx];
    // find the length of vector = size -1
    int idxBound = size - 1;
    // find indexes of two children 
    int lcIndex = (idx * 2 + 1);
    int rcIndex = (idx * 2 + 2);
    // check if index valid
    bool lcValid = lcIndex <= idxBound;
    bool rcValid = rcIndex <= idxBound;

    // for min heap
    if(!isMaxHeap){
        // if both valid, compare, value of idx = smaller one, call bbdDown for child index
        if(lcValid && rcValid){
            if(heap[lcIndex] < heap[rcIndex]){
                if(idxValue > heap[lcIndex]){
                    exchange(lcIndex, idx);
                    bblDown(lcIndex);
                } 
            }else{
                if(idxValue > heap[rcIndex]){
                    exchange(rcIndex, idx);
                    bblDown(rcIndex);
                } 
            }
        }else if(lcValid && !rcValid){  
            // if left valid, value of idx = child,  call bbdDown for child index
            // not possible for left child invalid, right child valid
            if(idxValue > heap[lcIndex]){
                exchange(lcIndex, idx);
                bblDown(lcIndex);
            } 
        }else{// if no valid, return
            return;
        }
    }else{ //for max heap
        // if both valid, compare, value of idx = larger one, call bbdDown for child index
        if(lcValid && rcValid){
            if(heap[lcIndex] > heap[rcIndex]){
                if(idxValue < heap[lcIndex]){
                    exchange(lcIndex, idx);
                    bblDown(lcIndex);
                } 
            }else{
                if(idxValue < heap[rcIndex]){
                    exchange(rcIndex, idx);
                    bblDown(rcIndex);
                } 
            }
        }else if(lcValid && !rcValid){  
            // if left valid, value of idx = child,  call bbdDown for child index
            // not possible for left child invalid, right child valid
            if(idxValue < heap[lcIndex]){
                exchange(lcIndex, idx);
                bblDown(lcIndex);
            } 
        }else{// if no valid, return
            return;
        }
    }
}
template <typename T>
void Heap<T>::extreValue(){
    max = heap[0];
    min = heap[0];
    for(int i = 0; i < size; i++){
        if(heap[i] > max) max = heap[i];
        if(heap[i] < min) min = heap[i];
        //cout<< "heap[i] = " << heap[i]<< " min = " <<  min << " max = "<< max<<endl;
    }
    
}

//  public function
template <typename T>
int Heap<T>::insert(T number){
    //first node 
    if(size == 0){
        heap.push_back(number);// push back
        size++;
        max = number;
        min = number;
        //cout<<"[insert] number: "<< number << " Heaptype: " << isMaxHeap <<" heap size: " << size <<endl; 
        return 1;
    }
    //more nodes
    //1.push back
    heap.push_back(number);// push back
    if(number > max) max = number;
    if(number < min) min = number;
    //2.bubble up until sorted
    if(isMaxHeap){
        bblUpMax(size);
    }else{
        bblUpMin(size);
    }
    size++;
    //cout<<"[insert] number: "<< number << " Heaptype: " << isMaxHeap <<" heap size: " << size <<endl; 
    return 1;
} //return 1 when success, -1 when fail
template <typename T>
int Heap<T>::remove(T number){
    //look for the number
    int idx = -1;
    for(int i = 0; i < size; i++){
        if(heap[i] == number) idx = i;
    }
    
    if(idx == -1) return 0; // not found
    size--;
    // switch the node with the last leaf
    exchange(idx,size);
    // pop the last leaf
    heap.pop_back();
    // bubble down the node of idx
    if(isMaxHeap){
        bblUpMax(idx);
        bblDown(idx);
    }else{
        bblUpMin(idx);
        bblDown(idx);
    }
    
    //cout<< "[remove]: " << number << " heap type: " << isMaxHeap << " idx : " << idx << " size: "<< size  <<endl;
    //cout<< "=====   min: "<< min << " max : "<< max<<endl;
    
    // renew min and max values
    if(number == min || number == max){
        extreValue();
    } 
    //cout<< "=====   min: "<< min << " max : "<< max<<endl;
    return 1;
} //return 1 when success, -1 when fail
template <typename T>
T Heap<T>::get_root(){
    return heap[0];
}
template <typename T>
T Heap<T>::extract_root(){
    T temp = heap[0];
    size--;
    // exchange root with left most leaf
    exchange(0,size);
    // delete the last leaf
    heap.pop_back();
    // call bblDown at root
    bblDown(0);
    return temp;
} //return the root value when success, -1 when fail
template <typename T>
T Heap<T>::get_min(){
    return min;
} //return the min value
template <typename T>
T Heap<T>::get_max(){
    return max;
} //return the max value
template <typename T>
int Heap<T>::get_size(){
    return size;
}//return the size
template <typename T>
bool Heap<T>::search(T number){
    for(int i = 0; i < size; i++){
        if(heap[i] == number) return true;
    }
    return false;
} //return true if found, false if not found