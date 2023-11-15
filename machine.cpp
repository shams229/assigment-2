#include "machine.h"
#include <bits/stdc++.h>
#include <fstream>
using namespace std;
machine::machine(string fileName)
{
    ProgramC = 0;halt = false;
    if (fileName.size() < 5 ||fileName.substr(fileName.size() - 4) != ".txt")
    {
        // if the file's name does not have .txt extension we add it
        fileName += ".txt";
    }
    fstream InputFile(fileName);
    if(InputFile.is_open()){
        string line;
        while(getline(InputFile,line))
        {
            InstructionSet.push_back(line);
        }
        InputFile.close();
    }
    RegistersRep.resize(16,{"00",1}); // intialize the size of the registers to be 16 from 0 --> F
    MemoryRep.resize(256,"00"); // intialize the size of the memory to be 256
}
void machine :: IsValid(string& IR)
{
    if(IR[0] != '1' || IR[0] != '2' || IR[0] != '3' || IR[0] != '4' || IR[0] != '5' || IR[0] == 'B' || IR[0] == 'C')
    {
        if (IR[1] == '0' || IR[1] == '1' || IR[1] == '2' || IR[1] == '3' || IR[1] == '4' || IR[1] == '5' || IR[1] == '6' || IR[1] == '7'
            || IR[1] == '8' || IR[1] == '9' || IR[1] == 'A' || IR[1] == 'B' || IR[1] == 'C' || IR[1] == 'D' || IR[1] == 'E' || IR[1] == 'F')
        {
            if (IR[2] == '0' || IR[2] == '1' || IR[2] == '2' || IR[2] == '3' || IR[2] == '4' || IR[2] == '5' || IR[2] == '6' || IR[2] == '7'
                || IR[2] == '8' || IR[2] == '9' || IR[2] == 'A' || IR[2] == 'B' || IR[2] == 'C' || IR[2] == 'D' || IR[2] == 'E' || IR[2] == 'F')
            {
                if (IR[3] == '0' || IR[3] == '1' || IR[3] == '2' || IR[3] == '3' || IR[3] == '4' || IR[3] == '5' || IR[3] == '6' || IR[3] == '7'
                    || IR[3] == '8' || IR[3] == '9' || IR[3] == 'A' || IR[3] == 'B' || IR[3] == 'C' || IR[3] == 'D' || IR[3] == 'E' || IR[3] == 'F')
                {
                    IR = IR;
                }
                else
                {
                    InstructionSet.pop_front();
                    InstructionSet.pop_front();
                }
            }
            else
            {
                InstructionSet.pop_front();
                InstructionSet.pop_front();
            }
        }
        else
        {
            InstructionSet.pop_front();
            InstructionSet.pop_front();
        }
    }
    else
    {
        InstructionSet.pop_front();
        InstructionSet.pop_front();
    }
}
void machine :: Fetch()
{
    if(InstructionSet.size()<=ProgramC)
    {
        halt = true;
    }
    else
    {
        IR = InstructionSet[ProgramC].substr(10,2) + InstructionSet[ProgramC+1].substr(10,2); // saving the latest instruction in IR if the ProgramC < number of instructions
        ProgramC += 2; // counter incrementer
    }
}
int machine :: HextoDec(string hex)
{
    int hexdigit;
    int decnumber = 0;
    int j = 0;
    for (int i = hex.size() - 1 ; i >= 0 ; i--)
    {
        if(isdigit(hex[i]))
        {
            hexdigit = hex[i] - '0';
        }
        else
        {
            hexdigit = toupper(hex[i]) - 'A' + 10;
        }
        decnumber += hexdigit * pow(16 , j);
        j++;
    }
    return decnumber;
}
string machine :: DectoHex(int dec)
{
    int reminder ;
    string hex = "";
    while(dec > 0)
    {
        reminder = dec % 16;
        if (reminder < 10)
        {
            hex += to_string(remainder);
        }
        else
        {
            hex += char(remainder + 55);
        }
        dec /= 16;
    }
    reverse(hex.begin() , hex.end);
    return hex;
}
void machine :: Excute()
{
    if (IR[0] == '1')
    {
        string mem = IR.substr(2);
        RegistersRep[HextoDec(IR.substr(1,1))].first = MemoryRep[HextoDec(mem)];
    }
    else if (IR[0] == '2')
    {
        RegistersRep[HextoDec(IR.substr(1,1))].first = IR.substr(2);
    }
    else if (IR[0] == '3')
    {
        MemoryRep[HextoDec(IR.substr(2,2))] = RegistersRep[HextoDec(IR.substr(1,1))].first;
    }
    else if (IR[0] == '4')
    {
        RegistersRep[HextoDec(IR.substr(3))].first =  RegistersRep[HextoDec(IR.substr(2,1))].first;
        }
        else if (IR[0] == '5')
        {
            int sIndex = (address >> 4) & 0xF;
            int tIndex = address & 0xF;
            addRegistersTwoComplement(regIndex, sIndex, tIndex, registers);
            }
        }
    else if (IR[0] == 'B')
    {
        string test = IR;
        if(RegistersRep[HextoDec(0)].first == RegistersRep[HextoDec(IR.substr(1,1))].first)
        {

            while(RegistersRep[HextoDec(IR.substr(1,1))].first != test.substr(2,2))
            {
                Fetch();
            }
        }
    }
    else if (IR[0] == 'C')
    {
        halt = true;
    }
}
void machine :: Run()
{
    for (int i = 0 ; i < InstructionSet.size()/2 ; i++)
    {
        Fetch();
        Excute();
        if (halt)
        {
            break;
        }

    }
}
void machine ::run()
{
    Run();
}
void Display(machine& m)
{
    cout << "     ";
    int ptr = 0;
    for (int i = 0 ; i < 16 ; i++)
    {
        if (i == 10)
        {
            cout << "A" << "    ";
        }
        else if (i == 11)
        {
            cout << "B" << "   ";
        }
        else if (i == 12)
        {
            cout << "C" << "    ";
        }
        else if (i == 13)
        {
            cout << "D" << "    ";
        }
        else if (i == 14)
        {
            cout << "E" << "     ";
        }
        else if (i == 15)
        {
            cout << "F" << "     ";
        }
        else
        {
            cout << i << "    ";
        }
    }
    cout << endl;
    for (int i = 0 ; i < 16 ; i++)
    {
        if (i == 10)
        {
            cout << "A" << "   ";
        }
        else if (i == 11)
        {
            cout << "B" << "   ";
        }
        else if (i == 12)
        {
            cout << "C" << "   ";
        }
        else if (i == 13)
        {
            cout << "D" << "   ";
        }
        else if (i == 14)
        {
            cout << "E" << "   ";
        }
        else if (i == 15)
        {
            cout << "F" << "   ";
        }
        else
        {
            cout << i << "   ";
        }
        for (int j = 0 ; j < 16 ; j++)
        {
            cout << m.MemoryRep[ptr] << "   ";
            ptr++;
        }
        cout << endl;
    }
    int cnt = 0;
    for (int i = 0 ; i < 16 ; i++)
    {
        cout << "R";
        if (cnt == 10)
        {
            cout << "A" << ":" << m.RegistersRep[i].first << "   ";
        }
        else if (cnt == 11)
        {
            cout << "B" << ":" << m.RegistersRep[i].first << "   ";
        }
        else if (cnt == 12)
        {
            cout << "C" << ":" << m.RegistersRep[i].first << "   ";
        }
        else if (cnt == 13)
        {
            cout << "D" << ":" << m.RegistersRep[i].first << "   ";
        }
        else if (cnt == 14)
        {
            cout << "E" << ":" << m.RegistersRep[i].first << "   ";
        }
        else if (cnt == 15)
        {
            cout << "F" << ":" << m.RegistersRep[i].first << "   ";
        }
        else
        {
            cout << cnt << ":" << m.RegistersRep[i].first << "   ";
        }
        cnt++;
    }
    cout << endl;
    cout << "IR: " << m.IR << endl;
    cout << "PC: " << m.ProgramC << endl;
    cout << "The program is halted" ;
}
machine::~machine()
{
}
void addRegistersTwoComplement(int rIndex, int sIndex, int tIndex, RegistersRep *registers)
{
    int sValue = registers[sIndex].value;
    int tValue = registers[tIndex].value;
    int sum = sValue + tValue;
    registers[rIndex].value = sum;
}