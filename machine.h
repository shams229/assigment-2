#ifndef TASK3_MACHINE_H
#define TASK3_MACHINE_H


#include<bits/stdc++.h>
using namespace std;

#pragma once

class machine
{
private:
    //class variables
    bool halt;                  // if we will close the Program halt = 1, else halt = 0
    void Excute();              // excution function
    void Fetch();               // see if the instruction given is in the instructionSet vector
    int HextoDec (string hex);
    string DectoHex (int dec);
    void Run();
    //data structures
    int ProgramC;                     // Program Counter
    string IR;                  // Instruction Register
    deque <string> InstructionSet;         // instructions go from the file into this vector
    vector <string> MemoryRep;              // vector that represents memory
    vector<pair<string,int>>RegistersRep;   // vector that represents register as the index is the number of the register
    // and string is the hex representaion of the value stored in this register
    // and the int number indicates the type of the number if its
    // 1 - normal hex
    // 2 - 2's Complement


public:
    machine(string fileName);                         // constructor that takes file of the input as a parameter
    friend void Display(machine &m);
    void run();
    ~machine();
     void IsValid(string& IR);            // see if the instruction given is valid or not
    //void Is_valid(string &IR);
};

#endif //TASK3_MACHINE_H