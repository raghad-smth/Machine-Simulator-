#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "Memory.h"
#include "Cpu.h"

class Instructions {
private:
    std::string IR;
    char opCode;
    std::string operand;
    int PC;

public:
    Instructions();
    Instructions(Cpu c);
    void decode();
    void execute(Memory &mm, Cpu &cc);
    std::string getIR();
    int getPC() { return PC; }
};

#endif // INSTRUCTIONS_H
