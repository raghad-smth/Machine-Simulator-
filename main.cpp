// Showing how the program works

#include "Simulat.h"



int main() {
    // First thing you creat Memory object to load the program from the file into the RAM
    Memory m;
    m.loadProgram("programm.txt");

    // Creat a Cpu object to implement the fetching step from the RAM
    Cpu cc;
    // Pass the cpu object for decoding in the instruction class
    Instrections i(cc);
    // Now we keep fetching, decoding , executing till which get called inside "execute" till the program terminate
    i.execute(m,cc);
    // Finally creat a screen object and print the PC,IR, Registers and Ram
    screen r;
    cout << "---------------------------------------" << '\n';
    r.printPC(i);
    r.printIr(i);
    cout << "---------------------------------------" << '\n';
    r.printRegs(cc);
    cout << "---------------------------------------" << '\n';
    r.printRam(m);


    return 0;
}
