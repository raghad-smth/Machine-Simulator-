#include "Memory.h"
#include "Cpu.h"
#include "Instructions.h"
#include "Screen.h"
#include <iostream>

int main() {
    // First, create a Memory object to load the program from the file into the RAM
    Memory m;
    m.loadProgram("programm.txt");

    // Create a Cpu object to implement the fetching step from the RAM
    Cpu cc;

    // Pass the cpu object for decoding in the instruction class
    Instructions i(cc);

    // Now we keep fetching, decoding, executing until the program terminates
    i.execute(m, cc);

    // Finally, create a Screen object and print the PC, IR, Registers, and RAM
    Screen r;
    std::cout << "---------------------------------------" << '\n';
    r.printPC(i);
    r.printIr(i);
    std::cout << "---------------------------------------" << '\n';
    r.printRegs(cc);
    std::cout << "---------------------------------------" << '\n';
    r.printRam(m);

    return 0;
}
