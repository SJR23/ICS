#include "avltree.h"
#include "bst.h"
#include "bstree.h"
#include <iostream>
using namespace std;

int AVLTree::get_height(Node *node){
    if(!node){return -1;}
    return node->height;
}

int AVLTree::get_balance(Node *node){
    if(!node){return 0;}
    return get_height(node->left) - get_height(node->right);
}

void AVLTree::set_height(Node *node){
    //int l = get_height(node->left);
    //int r = get_height(node->right);
    node->height = 1 + max(get_height(node->right), get_height(node->left));
}

Node * AVLTree::right_rotate(Node * y){
    Node * a = y->left;
    Node * b = a->right;
    a->right = y;
    y->left = b;
    set_height(y);
    set_height(a);
    return a;
}

Node * AVLTree::left_rotate(Node * x){
    Node * a = x->right;
    Node * b = a->left;
    a->left = x;
    x->right = b;
    set_height(x);
    set_height(a);
    return a;
}

Node * AVLTree::rebalance(Node * t){
    set_height(t);
    int b = get_balance(t);
    if(b > 1){
        if(get_balance(t->left) < 0){
            t->left = left_rotate(t->left);
        }
        return right_rotate(t);
    }
    else if(b < -1){
        if(get_balance(t->right) > 0){
            t->right = right_rotate(t->right);
        }
        return left_rotate(t);
    }
    else{
        return t;
    }
}

Node * AVLTree::insert_node(Node * t, string key){
    if(!t){
        return new Node(key);
    }
    if(key < t->key){
        t->left = insert_node(t->left, key);
    }
    else if(key > t->key){
        t->right = insert_node(t->right, key);
    }
    else{return t;}
    return rebalance(t);
}

Node * AVLTree::find_node(Node * t, string key){
    if(!t){return nullptr;}
    if(key > t->key){
        return find_node(t->right, key);
    }
    else if(key < t->key){
        return find_node(t->left, key);
    }
    else{return t;}
}

Node * AVLTree::delete_node(Node * t, string key){
    if(!t){return nullptr;}
    if(key < t->key){
        t->left = delete_node(t->left, key);
    }
    else if(key > t->key){
        t->right = delete_node(t->right, key);
    }
    else{
        Node * l = t->left;
        Node * r = t->right;
        delete t;
        if(!l && !r){
            return nullptr;
        }
        else if(!l){
            return r;
        }
        else if(!r){
            return l;
        }
        else{
            Node * note = r;
            while(note->left){
                note = note->left;
            }
            t->key = note->key;
            t->right = delete_node(t->right,note->key);
        }
    }       
    return rebalance(t);
}

AVLTree::AVLTree() : BST("AVLTree"){}

void AVLTree::insert(const string & key){
    root = insert_node(root, key);
    count++;
}

bool AVLTree::find(const string & key) const{
    return find_node(root, key);
}

void AVLTree::remove(const string & key){
    if(!find(key)){return;}
    root = delete_node(root, key);
    count--;
}

bool AVLTree::is_empty() const{
    return !root;
}

int AVLTree::get_height() const{
    return get_height(root);
}

/*AVLTree::~AVLTree(){
    delete_node(root, root->key);
}*/

