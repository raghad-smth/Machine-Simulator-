#include "Simulat.h"

// function to turn hexadecimal string into int hence the instruction are given in hexadecimal base
int hex_to_int(const std::string& hex) {
    return std::stoi(hex, nullptr, 16);
}

//------------------------------------------ Class Memory --------------------------------------------

Memory :: Memory (){

}

// Constructor to set the RAM from a vector
Memory :: Memory(vector <string> v){
    for (string s : v){
            RAM.push_back(s.substr(0,2));
            RAM.push_back(s.substr(2,2));
    }
    //filling the rest of the RAM with 00 s
    for (int i=v.size(); i<256 ; i++){
        RAM.push_back("00");
    }

}

//Function to load the program from a file
void Memory :: loadProgram(string fileName){
    //open the file that has the program
    ifstream iff;
    iff.open(fileName);
   if (!iff.is_open()){
       cout << "Can't open file !! " << '\n';
   }
   string instrection;
   // take each instruction from the file and store it in two memory cells cause the cell takes only one byte ,
   // hence these are hexadecimal it takes 2 bytes to represent four numbers
   while (iff >> instrection){
       RAM.push_back(instrection.substr(0,2));
       RAM.push_back(instrection.substr(2,2));
   }
   // fill the rest of the RAM with zeros
   for (int i=RAM.size(); i<256 ; i++){
       RAM.push_back("00");
   }

}

// Setter to set that takes the index which represents the address and what you want to set that cell to which is a string
void Memory ::setRam(int indx, std::string s) {
    RAM[indx] = s;
}

// Getter to get the value at a given address from the RAM
string& Memory ::getRam(int indx) {
   return RAM[indx];
}


//------------------------------------------ Class Cpu --------------------------------------------
int ppcc;
string final;
//Default constructor to set all the registers to 00 and program counter to 0
Cpu :: Cpu(){
    for (int i=0; i<16; i++) {
        registers.push_back("00");
    }
   PC = 0;
   IR = "";
}

// Fetch is the function that gets the values that the PC points at  their address from the RAM
string Cpu :: fetch(Memory m){
    // To take the full instruction we need to take from where the PC at and the address after it (stores one byte per cell)
        IR = m.getRam(PC) + m.getRam(PC+1);
        return IR;
}

// Getter to get the instruction register
string Cpu ::getIR() {
    return IR;
}
int Cpu ::getPC() {
    return PC;
}

// Getter to get the vector of the registers
vector <string> Cpu ::getRegs(){
    return registers;
}

// Setter that set the register at a given index to the given string
void Cpu :: setReg(int indx, string str){
    registers[indx] = str;
}

//------------------------------------------ Class Insteruction--------------------------------------------

Instrections ::Instrections() {
}

//Constructor to get the instruction register from the Cpu
Instrections ::Instrections(Cpu c) {
    IR = c.getIR();
}

//decode is a function to saprate the op code from the operand
void Instrections :: decode(){
    opCode = IR[0];
    operand = IR.substr(1,3);
}

//Execute is where the instructions get implemented, it takes an object from Memory to have access to the RAM,
// and object from the Cpu to access the registers while sharing the Program counter
void Instrections :: execute(Memory &mm, Cpu &cc) {
    // While loop represents  the Fetch Decode Execute loop that the computers follow to implement instructions
    // Keep the loop  as loong as the instruction is not the Halt instruction "C000"
    while (opCode != 'C') {
        fetch(mm);
        decode();
        switch (opCode) {
            // 1RXY : load what in memory address XY in register R
            case '1': {
               cc.setReg(hex_to_int(operand.substr(0, 1)),mm.getRam(hex_to_int(operand.substr(1, 2)) - 1) );
                PC += 2;
                break;
            }
            //2RXY : Load the register R with the bit pattern XY
            case '2':{
                cc.setReg(hex_to_int(operand.substr(0,1)), operand.substr(1,2));
                PC+= 2;
                break;
            }

            case '3':{
                //3R00 : print the content of register R
                if(operand.substr(1,1)=="0" &&operand.substr(2,1) =="0")
                {
                    cout << cc.getRegs()[hex_to_int(operand.substr(0,1))] << '\n';
                    PC+=2;
                }
                //3RXY : Store the content of R in the memory address XY    3134
                else {

                    mm.setRam(hex_to_int((operand.substr(1, 2))) - 1, cc.getRegs()[hex_to_int(operand.substr(0, 1))]);
                    PC += 2;
                }
                break;

            }
            // 40RS :  Move what in register R to register S
            case '4': {
                cc.setReg(hex_to_int(operand.substr(2, 1)) ,  cc.getRegs()[hex_to_int(operand.substr(1,1) )]);
                PC += 2;
                break;
            }
            //5RST : adds whats in register R to whats in register T and store in reg R
            case '5':{
                int s = stoi(cc.getRegs()[hex_to_int(operand.substr(1,1))]);
                int t = stoi(cc.getRegs()[hex_to_int(operand.substr(2,1))]);
                int sum=s+t;
                cc.setReg(hex_to_int(operand.substr(0,1)), to_string(sum));
                PC+=2;
                break;
            }
            //BRXY : JUMP to the instruction located in the memory cell at address XY
            //if the bit pattern in register R is equal to the bit pattern in register number 0.
            case 'B': {
                // get what is Reg 0 then compare it with what in Reg index R
                if ( cc.getRegs()[0] == cc.getRegs()[hex_to_int(operand.substr(0,1))]) {
                    // setting the pc to the memory given address cause registers are equal
                    PC = hex_to_int(operand.substr(1,2)) +1;
                } else {
                    // if registers are not equal  just move on to the next instruction
                    PC+=2;
                }
                  break;
            }
        }
         ppcc  = PC;
         final = IR;

    }
}

//------------------------------------------ Class Screen --------------------------------------------


// This class handel the output
screen :: screen (){
}
// Printing all the content of the RAM
void screen :: printRam(Memory &r) {
    cout << "Content of RAM : " << '\n';
    for (int i=0; i<256 ; i++){
        cout << r.getRam(i) << '\n';
    }
}

// Printing all the content of the registers
void screen ::printRegs(Cpu &c) {
    cout << "Content of Registers : " << '\n';
    for (string s: c.getRegs()){
        cout << s << endl;
    }
}

// Printing the final address that the program counter pointed at by taking an object from the instrection class henc it has the execute function
void screen :: printPC(Instrections &inc){
    cout << "Program Counter: "<< inc.getPC()<< '\n';
}


// Printing the final instruction the IR holds
void screen :: printIr(Instrections &inc){
    cout << "Instruction Register: "<< inc.getIR() << '\n';
};
















