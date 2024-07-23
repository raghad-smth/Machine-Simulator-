#include "Cpu.h"

Cpu::Cpu() {
    registers.resize(16, "00");
    PC = 0;
    IR = "";
}

std::string Cpu::fetch(Memory m) {
    IR = m.getRam(PC) + m.getRam(PC + 1);
    return IR;
}

std::string Cpu::getIR() {
    return IR;
}

int Cpu::getPC() {
    return PC;
}

std::vector<std::string> Cpu::getRegs() {
    return registers;
}

void Cpu::setReg(int indx, std::string str) {
    registers[indx] = str;
}
