// Interpreter A <Project8.cpp>
// EE 312 Project 8 submission by
// <Deepanshi Sharma>
// <ds52384>
// Slip days used: <2>
// Fall 2019

#include <stdio.h>
#include <string>
#include <iostream>
#include "Parse.h"
#include "Project8.h"
#include <string.h>

#include "SymbolTable.h"
using namespace std;

SymbolTree SymTree;

ExpressionTree::ExpressionTree(vector<Node*>& expr){
    overallRoot = add(overallRoot, expr);
}

Node* ExpressionTree::add(Node* root, vector<Node*>& expr) {
    Node* first = expr[0];
    expr.erase(expr.begin());
    root = first;
    if(!(first->isOperand)){
        if((strcmp(first->optr, "~") == 0) || (strcmp(root->optr, "!") == 0)){
            root->left = add(root->left, expr);
        } else {
            root->left = add(root->left, expr);
            root->right = add(root->right, expr);
        }
    }
    return root;
}

void ExpressionTree::printTree() {
    printTree(overallRoot, 0);
}

void ExpressionTree::printSpaces(int level) {
    for(int i = 0; i<level*4; i++){
        cout << ' ';
    }
}

void ExpressionTree::printTree(Node* root, int level){
    if(root == nullptr){
        return;
    }
    printTree(root->right, level+1);
    printSpaces(level);
    root->print();
    printTree(root->right, level+1);
}

int ExpressionTree::parse() {
    return parse(overallRoot);
}

int ExpressionTree::parse(Node* root) {
    if(root->optr != nullptr) {
        if ((strcmp(root->optr, "~") == 0) || (strcmp(root->optr, "!") == 0)) {
            if (root->isOperand) {
                return root->operand;
            }
            int arg1 = parse(root->left);
            if(strcmp(root->optr, "~") == 0) {
                return -1*arg1;
            }else{
                return !arg1;
            }
        }
    }

    if (root->isOperand) {
            return root->operand;
        }
        int arg1 = parse(root->left);
        int arg2 = parse(root->right);

        if ((strcmp(root->optr, "+") == 0)) return arg1 + arg2;
        else if ((strcmp(root->optr, "-") == 0)) return arg1 - arg2;
        else if ((strcmp(root->optr, "*") == 0)) return arg1 * arg2;
        else if ((strcmp(root->optr, "/") == 0)) return arg1 / arg2;
        else if ((strcmp(root->optr, "%") == 0)) return arg1 % arg2;
        else if ((strcmp(root->optr, "&&") == 0)) return (arg1 != 0 && arg2 != 0) ? true : false;
        else if ((strcmp(root->optr, "||") == 0)) return (arg1 != 0 || arg2 != 0) ? true : false;
        else if ((strcmp(root->optr, "<") == 0)) return (arg1 < arg2) ? true : false;
        else if ((strcmp(root->optr, ">") == 0)) return (arg1 > arg2) ? true : false;
        else if ((strcmp(root->optr, "==") == 0)) return (arg1 == arg2) ? true : false;
        else if ((strcmp(root->optr, "!=") == 0)) return (arg1 != arg2) ? true : false;
        else if ((strcmp(root->optr, "<=") == 0)) return (arg1 <= arg2) ? true : false;
        else if ((strcmp(root->optr, ">=") == 0)) return (arg1 >= arg2) ? true : false;
        else{
            cout << "Invalid operator" << endl;
            return -1;
        }
}

Node* ExpressionTree::copy(const Node* that){
    Node* n = new Node(that->isOperand, that->operand, that->optr);
    if(that->left != nullptr){
        n->left = copy(that->left);
    }
    if(that->right != nullptr){
        n->right = copy(that->right);
    }
    return n;
}

ExpressionTree::ExpressionTree(const ExpressionTree &that) {
    overallRoot = copy(that.overallRoot);
}

ExpressionTree& ExpressionTree::operator=(const ExpressionTree& that) {
    if(this != &that){
        destroy(overallRoot);
        overallRoot = copy(that.overallRoot);
    }
    return *this;
}

ExpressionTree::~ExpressionTree(){
    destroy(overallRoot);
}

void ExpressionTree::destroy(Node* n) {
    if(n == nullptr) {
        return;
    }
    destroy(n->left);
    destroy(n->right);
    delete n;
    n = nullptr;
}



void Print(char*){
    char* s = next_token();
    while(*s){
        cout << *s;
        s++;
    }
    read_next_token();
}


void Output(){
    read_next_token();
    if(next_token_type == NUMBER){
        int val = token_number_value;
        cout << val;
        read_next_token();
    }
    else {
        char *s = next_token();
        vector<Node *> expr;
        int i = 0;
        Node* nodes[1000];
        while ((next_token_type != END) && (strcmp(next_token(), "//") != 0) &&(strcmp(next_token(), "output") != 0) && (strcmp(next_token(), "var") != 0) && (strcmp(next_token(), "text") != 0)) {
            if (next_token_type == SYMBOL) {
                nodes[i] = new Node(false, 0, s);
                expr.push_back(nodes[i]);
                i++;
                read_next_token();
            } else if (next_token_type == NUMBER) {
                int number = token_number_value;
                nodes[i] = new Node(true, number, (char*)"null");
                expr.push_back(nodes[i]);
                i++;
                read_next_token();
            } else if (next_token_type == NAME) {
                if ((strcmp(next_token(), "output") != 0) && (strcmp(next_token(), "var") != 0) && (strcmp(next_token(), "text") != 0) &&
                    (strcmp(next_token(), "set") != 0)) {
                    char *name = new char[100];
                    strcpy(name, next_token());
                    double number = SymTree.get(name);
                    nodes[i] = new Node(true, number, (char*)"null");
                    expr.push_back(nodes[i]);
                    i++;
                    read_next_token();
                }

            }
        }
        ExpressionTree Tree(expr);
        cout << Tree.parse();
    }
}

void Var(){
    read_next_token();
    char* name = new char[100];
    strcpy(name, next_token());
    if(SymTree.get(name) != -1){
        cout << "variable" <<  name << "incorrectly re-initialized" << endl;
    }
    read_next_token();
    double val;
    if(next_token_type == NUMBER){
        val = token_number_value;
        read_next_token();
    }
    else if(next_token_type == NAME){
        char* name = new char[100];
        strcpy(name, next_token());
        val = SymTree.get(name);
        read_next_token();
    }
    else if(next_token_type == SYMBOL){
        char* s = new char[100];
        strcpy(s, next_token());
        vector<Node*> expr;
        Node* nodes[10000];
        int i = 0;
        while(next_token_type != END && (strcmp(next_token(), "//") != 0)&& (strcmp(next_token(), "//") != 0) &&(strcmp(next_token(), "output") != 0) && (strcmp(next_token(), "var") != 0) && (strcmp(s, "text") != 0)){
            if(next_token_type == SYMBOL){
                nodes[i] = new Node(false, 0, s);
                expr.push_back(nodes[i]);
                i++;
                read_next_token();
            }
            else if(next_token_type == NUMBER){
                double number = token_number_value;
                nodes[i] = new Node(true, number, (char*)"null");
                expr.push_back(nodes[i]);
                i++;
                read_next_token();
            }
            else if(next_token_type == NAME){
                if((strcmp(next_token(), "output") != 0) && (strcmp(next_token(), "var") != 0) && (strcmp(next_token(), "text") != 0) && (strcmp(next_token(), "set") != 0)){
                    char* name = new char[100];
                    strcpy(name, next_token());
                    double number = SymTree.get(name);
                    nodes[i] = new Node(true, number,(char*)"null");
                    expr.push_back(nodes[i]);
                    i++;
                    read_next_token();
                }
            }
        }
        ExpressionTree Tree(expr);
        val = Tree.parse();
    }
    SymTree.set(name, val);
}

void Set(){
    read_next_token();
    char* name = new char[100];
    strcpy(name, next_token());
    if(SymTree.get(name) == -1){
        cout << "variable" <<  name << "not declared" << endl;
    }
    read_next_token();
    double val;
    if(next_token_type == NUMBER){
        val = token_number_value;
        read_next_token();
    }
    else if(next_token_type == NAME){
        char* name = new char[100];
        strcpy(name, next_token());
        val = SymTree.get(name);
        read_next_token();
    }
    else if(next_token_type == SYMBOL){
        char* s = new char[100];
        strcpy(s, next_token());
        vector<Node*> expr;
        Node* nodes[10000];
        int i = 0;
        while(next_token_type!= END && (strcmp(next_token(), "//") != 0)&& (strcmp(next_token(), "//") != 0) &&(strcmp(next_token(), "output") != 0) && (strcmp(next_token(), "var") != 0) && (strcmp(next_token(), "text") != 0)){
            if(next_token_type == SYMBOL){
                nodes[i] = new Node(false, 0, s);
                expr.push_back(nodes[i]);
                i++;
                read_next_token();
            }
            else if(next_token_type == NUMBER){
                double number = token_number_value;
                nodes[i] = new Node(true, number, (char*)"null");
                expr.push_back(nodes[i]);
                i++;
                read_next_token();
            }
            else if(next_token_type == NAME){
                if((strcmp(next_token(), "output") != 0) && (strcmp(next_token(), "var") != 0) && (strcmp(next_token(), "text") != 0) && (strcmp(next_token(), "set") != 0)){
                    char* name = new char[100];
                    strcpy(name, next_token());
                    double number = SymTree.get(name);
                    nodes[i] = new Node(true, number,(char*)"null");
                    expr.push_back(nodes[i]);
                    i++;
                    read_next_token();
                }
            }
        }
        ExpressionTree Tree(expr);
        val = Tree.parse();
    }
    SymTree.set(name, val);
}

