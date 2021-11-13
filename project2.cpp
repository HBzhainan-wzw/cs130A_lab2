#include <iostream>
#include <string>
#include <cstring>
#include "MinMedianMaxSketch.h"
int main(int argc, char* argv[]){
    string flag = argv[1];
    string inputFilename = argv[2];
    string removeFilename = argv[3];
    if(flag == "heap"){
        Heap<int> maxHeap(1);
        Heap<int> minHeap(0);
        ifstream inputFile(inputFilename.c_str());
        string line;
        //while line
        while(getline(inputFile, line)){
            //read each value
            int number = atoi(line.c_str());
            //insert the value into the heap
            maxHeap.insert(number);
            minHeap.insert(number);
        }
        ifstream removeFile(removeFilename.c_str());
        //while line
        while(getline(removeFile, line)){
            //read each value
            int number = atoi(line.c_str());
            //insert the value into the heap
            maxHeap.remove(number);
            minHeap.remove(number);
        }
        cout<<"Min Heap:"<<endl;
        cout<<"Size = "<< minHeap.get_size() <<endl;;
        cout<<"Min = "<< minHeap.get_min() << endl;
        cout<<"Max = "<< minHeap.get_max()<<endl;
        cout<<"Max Heap:"<<endl;
        cout<<"Size = "<< maxHeap.get_size()<<endl;
        cout<<"Min = "<< maxHeap.get_min()<<endl;
        cout<<"Max = "<< maxHeap.get_max()<<endl;
    }
    if(flag == "MinMedianMaxSketch"){
    MinMedianMaxSketch m;
        m.load_data(inputFilename);
        //m.report();
        m.remove_data(removeFilename);
        m.report();
    }



}