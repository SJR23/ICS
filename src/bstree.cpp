#include "bstree.h"
#include <iostream>
using namespace std;

Node * BSTree::insert_node(Node * t, string key){
    if(!t){return new Node(key);}
    if(key < t->key){
        t->left = insert_node(t->left, key);
    }
    if(key > t->key){
        t->right = insert_node(t->right, key);
    }
    return t;
}

Node * BSTree::find_node(Node * t, string key){
    if(!t){return nullptr;}
    if(key == t->key){return t;}
    if(key < t->key){
        return find_node(t->left, key);
    }
    return find_node(t->right, key);
}

Node * BSTree::left_most(Node * t){
    while(t->left){
        t = t->left;
    }
    return t;
}

Node * BSTree::delete_node(Node * t, string key){
    if(!t){return nullptr;}
    if(key < t->key){
        t->left = delete_node(t->left, key);
    }
    else if(key > t->key){
        t->right = delete_node(t->right, key);
    }
    else{
        Node * note_left = t->left;
        Node * note_right = t->right;
        if(!note_left && !note_right){
            delete t;
            return nullptr;
        }
        else if(!note_left){;
            delete t;
            return note_right;
        }
        else if(!note_right){
            delete t;
            return note_left;
        }
        else{
            Node * note = left_most(t->right);
            t->key = note->key;
            t->right = delete_node(t->right, note->key);
        }
    }
    return t;
}

int BSTree::compute_height(Node * t){
    if(!t){return 0;}
    return 1 + max(compute_height(t->right), compute_height(t->left));
}

BSTree::BSTree() : BST("Binary Search Tree") {}

void BSTree::insert(const string & key){
    root = insert_node(root, key);
    count++;
}

bool BSTree::find(const string & key) const{
    Node * note = find_node(root, key);
    return note;
}

void BSTree::remove(const string & key){
    if(!find(key)){return;}
    root = delete_node(root, key);
    count--;
}

bool BSTree::is_empty() const{
    return !root;
}

int BSTree::get_height() const{
    return compute_height(root);
}


/*BSTree::~BSTree(){
    delete_node(root, root->key);
}*/