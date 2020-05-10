// Interpreter A <SymbolTable.h>
// EE 312 Project 8 submission by
// <Deepanshi Sharma>
// <ds52384>
// Slip days used: <2>
// Fall 2019

#ifndef PROJECT8_SYMBOLTABLE_H
#define PROJECT8_SYMBOLTABLE_H
#include <stdio.h>
#include <string.h>

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Variable {
public:
    Variable* leftChild;
    Variable* rightChild;
    char* key;
    double val;

    Variable(char* k, double v){
        leftChild = nullptr;
        rightChild = nullptr;
        key = new char[100];
        strcpy(this->key, k);
        this->val = v;
    }

    Variable(char* k){
        key = new char[100];
        strcpy(key, k);
    }

    ~Variable(){
        delete [] key;
    }
};

class SymbolTree{
    Variable* root;
    void insert(Variable* &t, Variable* &node);
    void remove(Variable* &t, char* key);
    Variable* find_max(Variable* &t);
public:
    double get(char* key);
    void set(char* key, double val);
    void remove(char* key);
    Variable* search(Variable* &t, Variable* &node);
};

#endif //PROJECT8_SYMBOLTABLE_H
