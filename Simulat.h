#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Memory{
    vector <string> RAM;
public:
    Memory();
    Memory(vector <string> RAM);
    void setRam(int indx, string s);
    string& getRam(int indx);
    void loadProgram(string fileName);
};
class Cpu : public Memory{
protected:
   vector <string> registers;
   int PC;
   string IR;
public :
    Cpu();
    string fetch(Memory m);
    string getIR();
    int getPC();
    vector <string> getRegs();
    void setReg (int indx, string str);
};
class Instrections : public Cpu{
protected:
   char opCode;
   string operand;
public :
    Instrections();
    Instrections(Cpu c);
    void decode();
    void execute(Memory &mm, Cpu &cc);
};
class screen: public Instrections{
public:
    screen();
    void printRegs(Cpu &c);
    void printPC(Instrections &inc);
    void printIr(Instrections &inc);
    void printRam(Memory &r);

};

