#include "hashtable.h"
#include "hasher.h"
#include "stats.h"
#include "Timer.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

ListNode * ListNode::find(string key, ListNode * L){
    while(L && L->data != key){
        L = L->next;
    }
    return L;
}

ListNode * ListNode::insert(string key, ListNode * L){
    if(!find(key, L)){
        ListNode * note = new ListNode(key, L);
        return note;
    }
    return L;
}

ListNode * ListNode::remove(string key, ListNode * L){
    ListNode * one = nullptr;
    ListNode * two = L;
    while(two && two->data != key){
        one = two;
        two = two->next;
    }
    if(!two){return L;}
    if(!one){L = two->next;}
    else{one->next = two->next;}
    delete two;
    return L;
}

void ListNode::print(ostream & out, ListNode * L){
    while(L){
        out << L->data << " ";
        L = L->next;
    }
}

int ListNode::length(ListNode * L){
    int len = 0;
    while(L){
        len++;
        L = L->next;
    }
    return len;
}

void ListNode::delete_list(ListNode * L){
    ListNode * one = L;
    while(L){
        ListNode * note = one->next;
        delete one;
        one = note;
    }
}

void HashTable::insert(const string & word){
    size_t i = hasher.hash(word, capacity);
    buf[i] = ListNode::insert(word, buf[i]);
}

bool HashTable::find(const string & word){
    size_t i = hasher.hash(word, capacity);
    return ListNode::find(word, buf[i]);
}

void HashTable::remove(const string & word){
    size_t i = hasher.hash(word, capacity);
    buf[i] = ListNode::remove(word, buf[i]);
}

bool HashTable::is_empty(){
    for(size_t i = 0; i < capacity; ++i){
        if(buf[i]){return false;}
    }
    return true;
}

bool HashTable::is_full(){
    size_t note = 0;
    for(size_t i = 0; i < capacity; ++i){
        note += ListNode::length(buf[i]);
    }
    return note >= capacity;
}

void HashTable::print(ostream & out){
    for(size_t i = 0; i < capacity; ++i){
        ListNode::print(out, buf[i]);
    }
}

size_t HashTable::number_of_entries(){
    size_t n = 0;
    for(size_t i = 0; i < capacity; ++i){
        n += ListNode::length(buf[i]);
    }
    return n;
}

size_t HashTable::number_of_chains(){
    return capacity;
}

void HashTable::get_chain_lengths(vector<int> & v){
    for(size_t i = 0; i < capacity; ++i)
        v.push_back(ListNode::length(buf[i]));
}

HashTable::~HashTable(){
    for(size_t i = 0; i < capacity; ++i){
        ListNode::delete_list(buf[i]);
    }
    delete[] buf;
}

void error(string word, string msg) {
    cout << "Error: " << msg << " " << word << endl;
}

void insert_all_words(string file_name, HashTable & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = NWORDS;
    t.start();
    for (string word; (in >> word) && limit > 0 ; --limit )
        L.insert(word);
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl;
}

void find_all_words(string file_name, HashTable & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = NWORDS;
    t.start();
    for (string word; (in >> word) && limit > 0 ; --limit )
        L.find(word);
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tF = " << eTime << endl;    
}

void remove_all_words(string file_name, HashTable & L) {
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = NWORDS;
    t.start();
    for (string word; (in >> word) && limit > 0 ; --limit ) {
        L.remove(word);
    }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tR = " << eTime << endl;
}

void measure_hashtable(string file_name, HashTable & L){
    cout << L.get_name() << endl;
    insert_all_words(file_name , L);
    vector<int> chain_lengths;
    L.get_chain_lengths(chain_lengths);
    Stats stats(L.get_name(),chain_lengths);
    stats.print(cout);
    find_all_words(file_name,L);
    remove_all_words(file_name,L);
    if ( !L.is_empty())
        error(L.get_name() , "is not empty");
}


void measure_hashtables(string input_file) {
    Hasher * H[] = {
        new MyHasher{},
        new MultHasher{}
    };
    int S[] = {
        100
    };
    for (auto size : S){
        for (auto h : H)
        {
            HashTable ht(*h, size);
            measure_hashtable(input_file, ht);
        }
    }
}

