#include "bst.h"
#include "timer.h"
#include <iostream>
#include <fstream>
#include <string>
#include "bstree.h"
#include "avltree.h"
using namespace std;

void BST::pre_order_print(ostream & out, Node * t){
    if(t){
        out << t->key << " ";
        pre_order_print(out, t->left);
        pre_order_print(out, t->right);
    }
}

void BST::in_order_print(ostream & out, Node * t){
    if(t){
        in_order_print(out, t->left);
        out << t->key << " ";
        in_order_print(out, t->right);
    }
}

void BST::post_order_print(ostream & out, Node * t){
    if(t){
        post_order_print(out, t->left);
        post_order_print(out, t->right);
        out << t->key << " ";
    }
}

void delete_t(Node * t){
    if(!t){return;}
    delete_t(t->left);
    delete_t(t->right);
    delete t;
}

BST::~BST(){
    delete_t(root);
}

ostream & operator << (ostream & out, BST & L){
    L.print(out);
    return out;
}

void error(string word, string msg){
    cerr << "Error: " << word << " " << msg;
}

void insert_all_words(int k, string file_name, BST & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k* NWORDS / 10;
    t.start();
    for(string word; (in >> word) && limit > 0; --limit)
        L.insert(word);
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl;
}

void find_all_words(int k, string file_name, BST & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k* NWORDS / 10;
    t.start();
    for(string word; (in >> word) && limit > 0; --limit)
        L.find(word);
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tF = " << eTime << endl;
}
    
void remove_all_words(int k, string file_name, BST & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k* NWORDS / 10;
    t.start();
    for(string word; (in >> word) && limit > 0; --limit)
        L.remove(word);
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tR = " << eTime << endl;
}

void measure_BST(string file_name, BST & L){
    cout << L.name << endl;
    insert_all_words(L.count, file_name, L);
    find_all_words(L.count, file_name, L);
    remove_all_words(L.count, file_name, L);
    if(!L.is_empty())
        error(L.name, "not empty");
}

void measure_BSTs(string input_file){
    AVLTree avtree;
    measure_BST(input_file, avtree);
    BSTree bstree;
    measure_BST(input_file, bstree);
}
