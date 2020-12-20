// Interpreter A <SymbolTable.cpp>
// EE 312 Project 8 submission by
// <Deepanshi Sharma>
// <ds52384>
// Slip days used: <2>
// Fall 2019

#include "SymbolTable.h"
#include <string>
#include <string.h>

using namespace std;

Variable* SymbolTree::find_max(Variable *&t){
    if (t->leftChild == nullptr)
        return t;
    return find_max(t->leftChild);
}

void SymbolTree::insert(Variable* &t, Variable* &node){
    if (t == nullptr) {
        t = std::move(node);
        return;
    }
    if(strcmp(t->key, node->key) == 0) {
        if(t->val != node->val){
            t->val = node->val;
        }
        return;
    }

    if(strcmp(node->key, t->key) > 0)
        insert(t->leftChild, node);
    else
        insert(t->rightChild, node);
}

Variable* SymbolTree::search(Variable* &t, Variable* &node){
    Variable* cur = t;
    while(cur) {
        if(strcmp(node->key, cur->key) == 0){
            return cur;
        }
        else if (strcmp(node->key, cur->key) < 0) {
            cur = cur->leftChild;
            search(cur, node);
        }
        else {
            cur = cur->rightChild;
            search(cur, node);
        }
    }
    return nullptr;
}

void SymbolTree::remove(Variable* &t, char* key){
    if (t == nullptr)
        return;

    if (strcmp(key, t->key) > 0)
        remove(t->leftChild, key);
    else if (strcmp(key, t->key) < 0)
        remove(t->rightChild, key);
    else if (t->leftChild && t->rightChild) {
        Variable* temp = find_max(t->rightChild);
        t->val    = temp->val;
        strcpy(t->key, temp->key);
        remove(t->rightChild, key);
    }
    else {
        if (t->leftChild)
            t = std::move(t->leftChild);
        else
            t = std::move(t->rightChild);
    }
}

void SymbolTree::set(char* key, double value){
    Variable* temp = new Variable(key, value);
    insert(root, temp);
}

double SymbolTree::get(char* key)
{
    Variable* temp = new Variable(key);
    Variable* result = search(root, temp);
    if(result == nullptr){
        return -1;
    }
    return result->val;
}

void SymbolTree::remove(char* key)
{
    remove(root, key);
}
