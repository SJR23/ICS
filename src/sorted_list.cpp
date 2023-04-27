#include <iostream>
#include "sorted_list.h"
#include "Timer.h"
#include <string>
#include <fstream>
using namespace std;

ostream & operator << (ostream & out, SortedList & L){
    L.print(out);
    return out;
}

void SortedArrayList::copy_down(int hole){
  for(int i = size - 1; i >= hole; i--){
    if (i + 1 < capacity){
      buf[i + 1] = buf[i];
    }
  }
}

void SortedArrayList::copy_up(int hole){
    for(int i = size; i > hole; i--){
        buf[i] = buf[i - 1];
    }
}

SortedArrayList::SortedArrayList(int cap) : SortedList("Sorted Array List"), capacity(cap), size(0){
    buf = new string[capacity];
}    

void SortedArrayList::insert(const string & word){
    int index = find_index(word);
    if(index <= -1)
        index = -(index + 1);
    copy_up(index);
    size++;
    buf[index] = word;
    return;
}

bool SortedArrayList::find(const string& word){
    int index = find_index(word);
    return (buf[index] == word && index >= 0 && index < size);
}

void SortedArrayList::remove(const string& word){
    int index = find_index(word);
    if(index < size && buf[index] == word){
        for(int i = index + 1; i < size; i++){
            buf[i - 1] = buf[i];
        }
        size--;
    }
}

bool SortedArrayList::is_empty(){
    return size == 0;
}

bool SortedArrayList::is_full(){
    return size == capacity;
}

void SortedArrayList::print(ostream & out){
    for(auto e : *this){
        out << e << ' ';
    }
}

SortedArrayList::~SortedArrayList(){
    delete[] buf;
}

int SortedArrayList::find_index(const string& word) {
    int first = 0;
    int last = size - 1;
    while(first <= last){
        int mid = (first + last)/2;
        if (buf[mid] == word) 
        {
            return mid;
        } 
        else if (buf[mid] < word) 
        {
            first = mid + 1;
        } else 
        {
            last = mid - 1;
        }
    }
    return -(first+1);
}

SortedLinkedList::SortedLinkedList() : SortedList("Sorted Linked List"){
    head = nullptr;
}

void ListNode::print(ostream & out, ListNode * L){
    while(L){
        out << L->data << " ";
        L = L->next;
    }
}

void ListNode::insert(const string & word, ListNode *&L){
    if(!L){
        L = new ListNode(word, nullptr);
    }
    else if(L->data > word){
        L = new ListNode(word, L);
    }
    else{
        ListNode * cur = L;
        for(; cur->next && word > cur->next->data; cur = cur->next){}
        cur->next = new ListNode(word, cur->next);
    }
}

ListNode * ListNode::find(const string & word, ListNode * L){
    ListNode * cur = L;
    while(cur && word!=cur->data){
        cur = cur->next;
    }
    return cur;
}

void ListNode::delete_list(ListNode * L){
    while(L){
        ListNode * note = L->next;
        delete L;
        L = note;
    }
}

void ListNode::remove(const string & word, ListNode *&L){
    ListNode * prev = L;
    ListNode * cur = L->next;
    if (L->data == word){
        ListNode * note = L;
        L = L->next;
        delete note;
        return;
    }
    while (cur->data < word){
        prev = cur;
        cur = cur->next;
    }
    if (cur->data == word){
        prev->next = cur->next;
        delete cur;
    }
}

SortedLinkedList::iterator SortedLinkedList::begin(){
    return iterator(head);
}

SortedLinkedList::iterator SortedLinkedList::end(){
    return iterator(nullptr);
}

void SortedLinkedList::insert(const string & word){
    ListNode::insert(word, head);
}

bool SortedLinkedList::find(const string & word){
    return ListNode::find(word, head);
}

bool SortedLinkedList::is_empty(){
    return head == nullptr;
}

void SortedLinkedList::remove(const string & word){
    ListNode::remove(word, head);
}

bool SortedLinkedList::is_full(){
    return false;
}

void SortedLinkedList::print(ostream & out){
    ListNode::print(out, head);
}

SortedLinkedList::~SortedLinkedList(){
    ListNode::delete_list(head);
}

void error(string word, string msg)
{
    cout << "ERROR: " << word << " " << msg << endl;
}

void insert_all_words(int k, string file_name, SortedList & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS / 10;
    t.start();
    for (string word; (in >> word) && limit > 0 ; --limit )
        L.insert(word);
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl;
}

void find_all_words(int k, string file_name, SortedList & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS / 10;
    t.start();
    for (string word; (in >> word) && limit > 0 ; --limit )
        L.find(word);
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tF = " << eTime << endl;
}


void remove_all_words(int k, string file_name, SortedList & L) {
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS / 10;
    t.start();
    for (string word; (in >> word) && limit > 0 ; --limit )
        L.remove(word);
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tR = " << eTime << endl;
}

void measure_SortedList_methods(string file_name, SortedList & L){
    cout << L.name << endl;
    for (int K=1 ; K <= 10 ; ++K)
        {
            cout << "K = " << K << endl;
            insert_all_words(K, file_name, L);
            find_all_words(K, file_name, L);
            remove_all_words(K, file_name, L);
            if ( !L.is_empty())
                error(L.name , "is not empty");
        }
}

void measure_lists(string input_file)
{
    SortedArrayList SAL;
    measure_SortedList_methods(input_file, SAL);
    SortedLinkedList SLL;
    measure_SortedList_methods(input_file, SLL);
}
