#include "Memory.h"

Memory::Memory() {
    RAM.resize(256, "00");
}

Memory::Memory(std::vector<std::string> v) {
    for (std::string s : v) {
        RAM.push_back(s.substr(0, 2));
        RAM.push_back(s.substr(2, 2));
    }
    while (RAM.size() < 256) {
        RAM.push_back("00");
    }
}

void Memory::loadProgram(std::string fileName) {
    std::ifstream ifs(fileName);
    if (!ifs.is_open()) {
        std::cout << "Can't open file !! " << '\n';
        return;
    }
    std::string instruction;
    while (ifs >> instruction) {
        RAM.push_back(instruction.substr(0, 2));
        RAM.push_back(instruction.substr(2, 2));
    }
    while (RAM.size() < 256) {
        RAM.push_back("00");
    }
}

void Memory::setRam(int indx, std::string s) {
    RAM[indx] = s;
}

std::string& Memory::getRam(int indx) {
    return RAM[indx];
}
