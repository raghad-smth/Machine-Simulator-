#ifndef CPU_H
#define CPU_H

#include <vector>
#include "Memory.h"

class Cpu {
private:
    std::vector<std::string> registers;
    int PC;
    std::string IR;

public:
    Cpu();
    std::string fetch(Memory m);
    std::string getIR();
    int getPC();
    std::vector<std::string> getRegs();
    void setReg(int indx, std::string str);
};

#endif // CPU_H
