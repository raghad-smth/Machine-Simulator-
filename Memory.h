#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class Memory {
private:
    std::vector<std::string> RAM;

public:
    Memory();
    Memory(std::vector<std::string> v);
    void loadProgram(std::string fileName);
    void setRam(int indx, std::string s);
    std::string& getRam(int indx);
};

#endif // MEMORY_H
