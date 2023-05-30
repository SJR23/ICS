#include "sorter.h"
#include <iostream>
#include <fstream>
using namespace std;
#include <algorithm>
#include <cmath>
#include "timer.h"

void Sorter::fill(int count, string file_name){
    vec.clear();
    ifstream file(file_name);
    if(file.is_open()){
        string note;
        for(int i = 0; i < count && file>>note; i++)
            vec.push_back(note);
        file.close();
    }
    else{
        error(file_name, "Not a valid file");
        return;
    }
}

void Sorter::print(ostream & out){
    for(const string & word : vec){
        out << word << " ";
    }
}

bool Sorter::verify_sorted(){
    for(int i = 0; i < vec.size()-1; ++i){
        if(vec[i] > vec[i+1]){
            return false;
        }
    }
    return true;
}

void InsertionSorter::insertionsort(vector<string> & vec, int low, int high){
    for(int i = low+1; i<=high; i++){
        string note = vec[i];
        int j = i-1;
        while(j >= low && vec[j] > note){
            vec[j+1] = vec[j];
            --j;
        }
        vec[j+1] = note;
    }
}

void InsertionSorter::sort(){
    insertionsort(vec, 0, vec.size()-1);
}

string QuickSorter::select_pivot(vector<string> & vec, int low, int high){
    int mid = (low + high)/2;
    if(vec[mid] < vec[low]){
        swap(vec[low], vec[mid]);}
    if(vec[high] < vec[low]){
        swap(vec[low], vec[high]);}
    if(vec[mid] < vec[high]){
        swap(vec[mid], vec[high]);}
    return vec[high];
}

int QuickSorter::partition(vector<string> & vec, int low, int high){
    string pivotvalue = select_pivot(vec, low, high);

    for(int j=low; j<high; j++){
        if(vec[j]<=pivotvalue){
            swap(vec[low],vec[j]);
            ++low;
        }
    }
    swap(vec[low],vec[high]);
    return low;
}

void QuickSorter::quicksort(vector<string> & vec, int low, int high){
    if (high - low < 11)     // constexpr int K = 11;
        InsertionSorter::insertionsort(vec, low, high);
    else
    {
        //string pivot = median_of_three( vec, low, high );
        int i = partition(vec, low, high);
        quicksort(vec, low, i - 1);
        quicksort(vec, i + 1, high);
    }
}


void QuickSorter::sort(){
    quicksort(vec, 0, vec.size()-1);
}

int l(int i){
    if(i==0)return 1;
    return 2*i+1;
}

int r(int i){
    if(i==0)return 2;
    return 2*i+2;
}

void HeapSorter::heapify(vector<string> & vec, int high, int root){
    int largest = root;
    int left = l(root);
    int right = r(root);
    if(left < high && vec[left] > vec[largest]){
        largest = left;
    }
    if(right < high && vec[right] > vec[largest]){
        largest = right;
    }
    if(largest != root){
        swap(vec[root], vec[largest]);
        heapify(vec, high, largest);
    }
}

void HeapSorter::heapsort(vector<string> & vec, int low, int high){
    int size = high-low+1;
    for(int root = size/2-1; root >= 0; root--){
        heapify(vec, size, root);
    }
    for(int end = size-1; end>=0; end--){
        swap(vec[low], vec[low+end]);
        heapify(vec, end, low);
    }
}

void HeapSorter::sort(){
    heapsort(vec, 0, vec.size()-1);
}

void introsort_util(vector<string>& arr, int low, int high, int depth_limit) {
    if (high - low < 11) {
        InsertionSorter::insertionsort(arr, low, high);
    }
    else if (depth_limit == 0) {
        HeapSorter::heapsort(arr, low, high);
    }
    else{
        int p = QuickSorter::partition(arr, low, high);
        introsort_util(arr, low, p - 1, depth_limit - 1);
        introsort_util(arr, p + 1, high, depth_limit - 1);
    }
}


void IntroSorter::introsort(vector<string>& vec, int low, int high) {
    int depth_limit = 2 * log(high-low);
    introsort_util(vec, low, high, depth_limit);
}

void IntroSorter::sort() {
    introsort(vec, 0, vec.size()-1);
}

void STLSorter::sort(){
    std::ranges::sort(vec);
}

void StableSorter::sort(){
    std::stable_sort(vec.begin(), vec.end());
}

void ShellSorter::gapInsertionSort(vector<string> & avector, int start, int gap){
    int sz = avector.size();
    for(int i = start + gap; i < sz; i += gap){
        string currentvalue = avector[i];
        int position = i;
        while(position >= gap && avector[position - gap] > currentvalue){
            avector[position] = avector[position - gap];
            position -= gap;
        }
        avector[position] = currentvalue;
    }
}

void ShellSorter::shellSort(vector<string> & avector){
    int subvectorcount = avector.size() / 2;
    while(subvectorcount > 0){
        for(int i = 0; i < subvectorcount; i++){
            gapInsertionSort(avector, i, subvectorcount);
            subvectorcount = subvectorcount / 2;
        }
    }
}

void ShellSorter::sort(){
    shellSort(vec);
}

ostream & operator << (ostream & out, Sorter & L){
    L.print(out);
    return out;
}

void error(string word, string msg){
    cerr << "Error: " << msg << " " << word << endl;
}

void measure_sorters(string input_file){
    vector<Sorter*> sorters{
        new InsertionSorter(),
        new QuickSorter(),
        new HeapSorter(),
        new IntroSorter(),
        new STLSorter(),
        new StableSorter(),
        new ShellSorter()
    };
    for(Sorter* sorter : sorters){
        measure_partitions(input_file, *sorter);
        delete sorter;
    }
}

void measure_partitions(string file_name, Sorter & L){
    cout << L.name << endl;
    cout << file_name << endl;
    for(int k = 1; k <= 10; ++k){
        cout << "\tK = " << k << " ";
        measure_partition(k, file_name, L);
    }
}

void measure_partition(int k, string file_name, Sorter & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS;
    L.fill(k, file_name);
    t.start();
    L.sort();
    t.elapsedUserTime(eTime);
    //t.stop();
    in.close();
    cout << "\tP = " << eTime << endl;
}