#ifndef MINMEDIANMAXSKETCH_H
#define MINMEDIANMAXSKETCH_H

#include "Heap.h"
#include <string>
#include <fstream>


class MinMedianMaxSketch{
    private:
        Heap<int>* maxHeap;
        Heap<int>* minHeap;
        int median;
        int ttlSize = 0;
        void rebalance(bool flag); // flag = true ==>  min to max | false ==> max to min
        void reloadMedian();

    public:
        MinMedianMaxSketch();
        
        //public functions
        int insert(int number); // insert, return 1 if done, -1 if error
        int remove(int number); 
        int get_median();
        int get_minimum();
        int get_maximum();
        int get_size();
        bool search(int number);
        //helper functiom
        int load_data(string filename);
        int remove_data(string filename);
        void report();
};





#endif













//constructor
MinMedianMaxSketch::MinMedianMaxSketch(){
    Heap<int>* h = new Heap<int>(1);
    maxHeap = h;
    h = new Heap<int>(-1);
    minHeap = h;
    cout<<"[MinMedianMaxSketch]: initialized"<<endl;
}

//public functions
int MinMedianMaxSketch::load_data(string filename){

    cout<<"[MinMedianMaxSketch] start load file: "<< filename << endl;
    //load the file
    ifstream inputFile(filename.c_str());
    string line;
    //while line
    while(getline(inputFile, line)){
        //read each value
        int number = atoi(line.c_str());
        //insert the value into the heap
        this->insert(number);
    }

    //cout<<"[MinMedianMaxSketch]: finish load file"<<endl;
    //done
    return 0;
}
int MinMedianMaxSketch::remove_data(string filename){

    cout<<"[remove_data] start load file: "<< filename << endl;
    //load the file
    ifstream inputFile(filename.c_str());
    string line;
    //while line
    while(getline(inputFile, line)){
        //read each value
        int number = atoi(line.c_str());
        //insert the value into the heap
        this->remove(number);
        //cout<<"[remove data]: " << number << " median: " << median << endl;
        reloadMedian();
        //report();
    }
    //cout<<"[remove_data]: data removed"<<endl;
    
    //done
    return 0;
}
int MinMedianMaxSketch::insert(int number){
    // first node
    if(ttlSize == 0){
        // insert into max heap
        maxHeap->insert(number);
        // size + 1
        ttlSize++;
        // median = current number
        median = number;
        cout<<"[load data]: " << number << " median: " << median << endl;
        //done
        return 1;
    }
    // more nodes
    // size + 1
    ttlSize++;
    // 1. compare number with median: 
    if(number > median){
        minHeap->insert(number);// num > median ==> insert to min heap
    }else{
        maxHeap->insert(number);// num < median ==> insert to max heap
    }
    // 2. check balance, assign new median
    int minSize = minHeap->get_size();
    int maxSize = maxHeap->get_size();
    int diff = abs(minSize - maxSize);
    // if minheap size > maxheap size
    if(minSize > maxSize){
        // if diff >= 2 ==> min to max rebalance, median = root of maxheap
        if(diff >= 2){
            rebalance(1);
            median = maxHeap->get_root();
        }else{
            // if diff < 2 ==> median = root of minheap
            median = minHeap->get_root();
        }
    }else if(minSize < maxSize){ // if minheap size < maxheap size
        // if diff >= 2 ==> max to min rebalance, median = root of maxheap
        if(diff >= 2){
            rebalance(0);
            median = maxHeap->get_root();
        }else{
            // if diff < 2 ==> median = root of maxheap
            median = maxHeap->get_root();
        }
    }else{ // if same, median = root of maxheap  
        median = maxHeap->get_root();
    }
    reloadMedian();
    //cout<<"[load data]: " << number << " median: " << median << endl;
    //report();
    return 1;
} 
int MinMedianMaxSketch::remove(int number){
    int flag = 0;
    flag = minHeap->remove(number);
    if(flag) return 1;
    flag = maxHeap->remove(number);
    if(flag) return 1;
    report();
    return 0;
} 
int MinMedianMaxSketch::get_median(){
    reloadMedian();
    return median;
}
int MinMedianMaxSketch::get_minimum(){
    return maxHeap->get_min();
}
int MinMedianMaxSketch::get_maximum(){
    return minHeap->get_max();
}
int MinMedianMaxSketch::get_size(){
    return minHeap->get_size() + maxHeap->get_size();
}
bool MinMedianMaxSketch::search(int number){
    int flag = 0;
    flag = minHeap->search(number);
    if(flag) return 1;
    flag = maxHeap->search(number);
    if(flag) return 1;
    return 0;
}
void MinMedianMaxSketch::report(){
    // cout<<" ===== min ====="<<endl;
    // for(int i = 0; i < minHeap->get_size();i++){
    //     cout<< "i = "<< i << " value = "<< minHeap->heap[i]<<endl;
    // }

    // cout<<" ===== max ====="<<endl;
    // for(int i = 0; i < maxHeap->get_size();i++){
    //     cout<< "i = "<< i << " value = "<< maxHeap->heap[i]<<endl;
    // }


    cout<<"MinMedianMaxSketch:"<<endl;
    cout<<"Size = "<<get_size()<<endl;
    cout<<"Min = "<< get_minimum()<<endl;
    cout<<"Max = "<<get_maximum()<<endl;
    cout<<"Median = "<<median<<endl;
}

// helper functions
void MinMedianMaxSketch::reloadMedian(){
    int minSize = minHeap->get_size();
    int maxSize = maxHeap->get_size();
    if(minSize> maxSize){
        median = minHeap->get_root();
    }else{
        median = maxHeap->get_root();
    }
    //cout<<"[reloadMedian]: " << median << endl;
}
void MinMedianMaxSketch::rebalance(bool flag){ // flag = true ==>  min to max | false ==> max to min 
    if(flag){
        // min to max
        // 1. extract root from min, store it.
        //cout << "[rebalance]: min to max" << endl;
        int temp = minHeap->extract_root();
        // 2. insert to max
        maxHeap->insert(temp);
    }else{
        // max to min
        // 1. extract root from max, store it.
        //cout << "[rebalance]: max to min" << endl;
        int temp = maxHeap->extract_root();
        // 2. insert to min
        minHeap->insert(temp);
    }
}


