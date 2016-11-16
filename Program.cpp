#include "Program.hpp"

Program::Program(unsigned short* opcodes, int numberOfProgramLines) : opcodes(opcodes), numberOfProgramLines(numberOfProgramLines){
}

Program::~Program(){
    delete[] opcodes;
}

unsigned short* Program::getOpcodes(){
    return opcodes;
}

int Program::getNumberOfProgramLines(){
    return numberOfProgramLines;
}
