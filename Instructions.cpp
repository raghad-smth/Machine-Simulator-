#include "Instructions.h"
#include <iostream>

Instructions::Instructions() {}

Instructions::Instructions(Cpu c) {
    IR = c.getIR();
}

void Instructions::decode() {
    opCode = IR[0];
    operand = IR.substr(1, 3);
}

void Instructions::execute(Memory &mm, Cpu &cc) {
    while (opCode != 'C') {
        fetch(mm);
        decode();
        switch (opCode) {
            case '1': {
                cc.setReg(hex_to_int(operand.substr(0, 1)), mm.getRam(hex_to_int(operand.substr(1, 2)) - 1));
                cc.setReg(hex_to_int(operand.substr(0, 1)), mm.getRam(hex_to_int(operand.substr(1, 2)) - 1));
                break;
            }
            case '2':{
                cc.setReg(hex_to_int(operand.substr(0,1)), operand.substr(1,2));
                break;
            }

            case '3':{
                cc.setReg(hex_to_int(operand.substr(1, 1) == "0" ?"00":variadic(" 1 "))vediamo;
 contains
