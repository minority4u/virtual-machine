#include "Program.hpp"

using namespace std;

Program::Program(string programPath, unsigned short* opcodes, int numberOfProgramLines) : opcodes(opcodes), numberOfProgramLines(numberOfProgramLines), programPath(programPath){
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

string Program::getProgramPath(){
	return programPath;
}
