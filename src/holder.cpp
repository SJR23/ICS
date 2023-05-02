#include <string>
#include <fstream>
#include <iostream>
#include "holder.h"
#include "Timer.h"
using namespace std;

ArrayStack::ArrayStack(int cap) : Stack("Array Stack"), capacity(cap), size(0), buf(new string[cap]){}

void ArrayStack::push(const string & word){
    if(!is_full()){
        buf[size] = word;
        size++;
    }
}

void ArrayStack::pop(){
    if(!is_empty()){
        size--;
    }
}

string ArrayStack::top(){
    if(!is_empty()){
        return buf[size-1];
    }
    return "";
}

bool ArrayStack::is_empty(){
    return size == 0;
}

bool ArrayStack::is_full(){
    return size == capacity;
}

void ArrayStack::print(ostream & out){
    for(int i = size-1; i >= 0; i--){
        out << buf[i] << " ";
    }
}

ArrayStack::~ArrayStack(){
    delete[] buf;
}

void ListNode::print(ostream & out, ListNode * L){
    while(L){
        out << L->data << " ";
        L = L->next;
    }
    //out << endl;
}

void ListNode::delete_list(ListNode * L){
    while(L){
        ListNode * note = L;
        L = L->next;
        delete note;
    }
}

LinkedStack::LinkedStack() : Stack("Linked Stack"), head(nullptr){}

void LinkedStack::push(const string & word){
    head = new ListNode(word, head);
}

void LinkedStack::pop(){
    if(!is_empty()){
        ListNode * note = head;
        head = head->next;
        delete note;
    }
}

string LinkedStack::top(){
    return head->data;
}

bool LinkedStack::is_empty(){
    return head == nullptr;
}

bool LinkedStack::is_full(){
    return false;
}

void LinkedStack::print(ostream & out){
    ListNode::print(out, head);
}

LinkedStack::~LinkedStack(){
    ListNode::delete_list(head);
}

ArrayQueue::ArrayQueue(int cap) : Queue("Array Queue"), capacity(cap+1), front(0), rear(0), buf(new string[cap+1]){}

void ArrayQueue::enq(const string & word){
    if(!is_full()){
        buf[rear] = word;
        rear = (rear + 1) % capacity;
    }
}

void ArrayQueue::deq(){
    if(!is_empty()){
        front = (front + 1) % capacity;
    }
}

string ArrayQueue::next(){
    return buf[front];
}

bool ArrayQueue::is_empty(){
    return front == rear;
}

bool ArrayQueue::is_full(){
    return (rear + 1) % capacity == front;
}

void ArrayQueue::print(ostream & out){
    for(int i = front; i != rear; i = (i+1)%capacity){
        out << buf[i] << " ";
    }
    //out << endl;
}

ArrayQueue::~ArrayQueue(){
    delete[] buf;
}

LinkedQueue::LinkedQueue() : Queue("Linked Queue"), head(nullptr), tail(nullptr){}

void LinkedQueue::enq(const string & word){
    ListNode * note = new ListNode(word, nullptr);
    if(tail){
        tail->next = note;
    }
    tail = note;
    if(!head){
        head = note;
    }
}

void LinkedQueue::deq(){
    if(!is_empty()){
        ListNode * note = head;
        head = head->next;
        if(!head){
            tail = nullptr;
        }
        delete note;
    }
}

string LinkedQueue::next(){
    if(!is_empty()){
        return head->data;
    }
    return "";
}

bool LinkedQueue::is_empty(){
    return head == nullptr;
}

bool LinkedQueue::is_full(){
    return false;
}

void LinkedQueue::print(ostream & out){
    ListNode::print(out, head);
}

LinkedQueue::~LinkedQueue() {
    ListNode::delete_list(head);
}

void error(string word, string msg){
    cout << "ERROR: " << word << " " << msg << endl;
}

ostream & operator << (ostream & out, Stack & L){
    L.print(out);
    return out;
}

void insert_all_words(int k, string file_name, Holder & L){
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

void remove_all_words(int k, string file_name, Holder & L) {
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS / 10;
    t.start();
    for (string word; (in >> word) && limit > 0 ; --limit )
        L.remove();
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tR = " << eTime << endl;
}

void measure_holder(string file_name, Holder & L) {
    cout << L.name << endl;
    for (int K=1 ; K <= 10 ; ++K)
        {
            cout << "K = " << K << endl;
            insert_all_words(K , file_name , L);
            remove_all_words(K , file_name , L);
            if ( !L.is_empty())
                error(L.name , "is not empty");
        }
}

void measure_holders(string input_file) {
    ArrayStack AS;
    measure_holder(input_file, AS);
    LinkedStack LS;
    measure_holder(input_file, LS);
    ArrayQueue AQ;
    measure_holder(input_file, AQ);
    LinkedQueue LQ;
    measure_holder(input_file, LQ);
}