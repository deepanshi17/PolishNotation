// Interpreter A <main.cpp>
// EE 312 Project 8 submission by
// <Deepanshi Sharma>
// <ds52384>
// Slip days used: <2>
// Fall 2019

#include "stdio.h"
#include <string.h>

#include "stdlib.h"
#include <iostream>
#include "Parse.h"
#include "Project8.h"
#include "SymbolTable.h"
using namespace std;

void run() {
    read_next_token();
    char* command = next_token();
    while (next_token_type != END) {
        if (next_token_type == NAME) {
            if (strcmp(command, "text") == 0) {
                read_next_token();
                char* string = next_token();
                Print(string);
            }
            if (strcmp(command, "output") == 0) {
                Output();
            }
            if (strcmp(command, "var") == 0) {
                Var();
            }
            if (strcmp(command, "set") == 0) {
                Set();
            }
            command = next_token();
            if (strcmp(command, "//") == 0) {
                skip_line();
                read_next_token();
            }
        }
    }
}


int main(void){
    set_input("test_grader.blip");  run();
    run();
}

