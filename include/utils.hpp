
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;
using namespace std::chrono;
using std::cout;
using std::ifstream;
using std::string;
using std::vector;


struct interval {
  double left;
  double right;
};

vector<interval> read_file(string filename,int size_) {
    ifstream infile;
    vector<interval> data;
    int num = 0;
    infile.open(filename);
    if (infile.fail()) {
        cout << "error" << '\n';
        return {};
    }
    while (!infile.eof() && num < size_) {
        interval x;
        infile >> x.left >> x.right;
        data.push_back(x);
        ++num;
    }
    infile.close();
    return data;
    }

void swap(vector<interval>& A, int i, int j) {
  auto temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}



void print_data(vector<interval>& A){
    for(auto i:A){
        cout<< i.left <<" "<< i.right <<'\n';
    }
    cout<<"\n";

}

interval get_intersection(vector<interval>&A,int p,int r){
    int randNum = rand()%(r-p + 1) + p;
    swap(A,randNum,r);
    auto intersection = A[r];
    for (int i{p}; i <r ;i++){
        if (A[i].left <= intersection.right && A[i].right >= intersection.left){
            if(intersection.left < A[i].left ){
                intersection.left = A[i].left;
            }
            if(intersection.right > A[i].right ){
                intersection.right = A[i].right;
            }

        }
    }
    return intersection;
}

/**
 * @brief  
 * 
 * @param A 
 * @param left_val 
 * @param p 
 * @param r 
 * @return int 
 */
int partition_right(vector<interval>&A,int left_val,int p,int r){
    int i = p-1;
    for (int j{p};j<r;j++){
        if (A[j].left <= left_val){
            i++;
            swap(A,i,j);
        }
    }
    swap(A,i+1,r);
    return i+1;
}

int partition_left(vector<interval>&A,int right_val,int p,int r){
    int i = p-1;
    for (int j{p};j<r;j++){
        if (A[j].right < right_val){
            i++;
            swap(A,i,j);
        }
    }
    swap(A,i+1,r);
    return i+1;
}

void fuzzy_sort(vector<interval>& A, int p, int r) {  
  
  if (p < r) {
    auto intersection = get_intersection(A,p,r);
    auto a = partition_right(A,intersection.left,p,r);
    auto b = partition_left(A,intersection.right,p,r);
    fuzzy_sort(A,p,b-1);
    fuzzy_sort(A,a+1,r);
  }
}



