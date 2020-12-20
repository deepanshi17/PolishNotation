// Interpreter A <Project8.h>
// EE 312 Project 8 submission by
// <Deepanshi Sharma>
// <ds52384>
// Slip days used: <2>
// Fall 2019

#ifndef PROJECT8_PROJECT8_H
#define PROJECT8_PROJECT8_H

#include <string>
#include "Parse.h"
#include "SymbolTable.h"
#include <vector>
#include <string.h>

using namespace std;

class Node{
public:
    bool isOperand;
    int operand;
    char* optr;
    Node* left;
    Node* right;
    Node(bool isOperand, int operand, char* optr) {
        left = nullptr;
        right = nullptr;
        this->isOperand = isOperand;
        this->operand = operand;
        this->optr = new char[2];
        strcpy(this->optr, optr);
    }
    ~Node(){
        delete [] optr;
    }
    void print() {
        if (isOperand) {
            cout << operand << endl;
        } else {
            cout << optr << endl;
        }
    }
};

class ExpressionTree{
private:
    const int spaces_per_level = 4;
    Node* overallRoot;
    Node* add(Node* root, vector<Node*>&);
    void printTree(Node*, int);
    void printSpaces(int);
    int parse(Node*);
    Node* copy(const Node* that);
    void destroy(Node*);
public:
    int parse();
    ExpressionTree(vector<Node*>& expr); // constructor
    void printTree();
    ExpressionTree(const ExpressionTree& that);
    ExpressionTree& operator=(const ExpressionTree& that);
    ~ExpressionTree();
};

void Print(char*);
void Output(void);
void Var();
void Set();


#endif //PROJECT8_PROJECT8_H
