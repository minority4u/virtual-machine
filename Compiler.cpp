#include "Compiler.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <algorithm>

using namespace std;

enum opcodes {
	NOP = 0b0000,
	LOAD = 0b0001,
	MOV = 0b0010,
	ADD = 0b0011,
	SUB = 0b0100,
	MUL = 0b0101,
	DIV = 0b0110,
	PUSH = 0b0111,
	POP = 0b1000,
	JMP = 0b1001,
	JIZ = 0b1010,
	JIH = 0b1011,
	JSR = 0b1100,
	RTS = 0b1101
};

Compiler::Compiler(string fileURL) : fileURL(fileURL){
}

Compiler::~Compiler(){
}

Program* Compiler::compile(){
    fstream file(fileURL, ios::in);
    int fileLines = countFileLines();
    string line = "";

    unsigned short* program = new unsigned short[fileLines];
    
    for(int i = 0; getline(file, line, '\n'); i++){
        program[i] = compileLineToOpcode(line);
    }

    file.close();

    return new Program(fileURL, program, fileLines);
}

int Compiler::countFileLines(){
    fstream file(fileURL, ios::in);
    int numberOfLines = 0;
    string line = "";

    for(int i = 0; getline(file, line, '\n'); i++){
        numberOfLines++;
    }

    return numberOfLines;
}

int Compiler::countCharInString(string str, char ch){
	int charCounter = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str.at(i) == ch) {
			charCounter++;
		}
	}
	return charCounter;
}


unsigned short Compiler::compileLineToOpcode(string line) {

	int value = 0;
	int toMem, fromMem;
	size_t xStart, yStart;
	unsigned short opcode = 0;
	string delimiter = " ";
	string comand = "";
	string rX = "";
	string rY = "";

	comand = line.substr(0, line.find(delimiter));

	if (comand == "NOP") {
		opcode = NOP;
	}
	if (comand == "LOAD") {
		value = stoi(line.substr(line.find(delimiter)));
		opcode = LOAD + (value << 4);
	}
	if (comand == "MOV") {
		fromMem = countCharInString(line.substr(line.find(",")), '(') == 1 ? 1 : 0;
		toMem = countCharInString(line.substr(0, line.find(",")), '(') == 1 ? 1 : 0;

		// from mem to mem
		if (fromMem && toMem) {
			xStart = line.find_first_of("R") + 1;
			yStart = line.find_last_of("R") + 1;
			rX = line.substr(xStart, line.find_first_of(")") - xStart);
			rY = line.substr(yStart, (line.size() - 1) - yStart);
		}

		// from register to register
		if (!fromMem && !toMem) {
			xStart = line.find_first_of("R") + 1;
			rX = line.substr(xStart, line.find_first_of(",") - xStart);
			rY = line.substr(line.find_last_of("R") + 1);
		}

		//from reg to mem
		if (!fromMem && toMem)
		{
			xStart = line.find_first_of("R") + 1;
			rX = line.substr(xStart, line.find_first_of(")") - xStart);
			rY = line.substr(line.find_last_of("R") + 1);
		}

		//from mem to reg
		if (fromMem && !toMem) {
			xStart = line.find_first_of("R") + 1;
			yStart = line.find_last_of("R") + 1;
			rX = line.substr(xStart, line.find_first_of(",") - xStart);
			rY = line.substr(yStart, (line.size() - 1) - yStart);
		}

		opcode = MOV + (stoi(rX) << 4) + (stoi(rY) << 8) + (fromMem << 12) + (toMem << 13);
	}
	if (comand == "ADD") {
		xStart = line.find_first_of("R") + 1;
		rX = line.substr(xStart, line.find_first_of(",") - xStart);
		rY = line.substr(line.find_last_of("R") + 1);

		opcode = ADD + (stoi(rX) << 4) + (stoi(rY) << 8);
	}
	if (comand == "SUB") {
		xStart = line.find_first_of("R") + 1;
		rX = line.substr(xStart, line.find_first_of(",") - xStart);
		rY = line.substr(line.find_last_of("R") + 1);

		opcode = SUB + (stoi(rX) << 4) + (stoi(rY) << 8);
	}
	if (comand == "MUL") {
		xStart = line.find_first_of("R") + 1;
		rX = line.substr(xStart, line.find_first_of(",") - xStart);
		rY = line.substr(line.find_last_of("R") + 1);

		opcode = MUL + (stoi(rX) << 4) + (stoi(rY) << 8);
	}
	if (comand == "DIV") {
		xStart = line.find_first_of("R") + 1;
		rX = line.substr(xStart, line.find_first_of(",") - xStart);
		rY = line.substr(line.find_last_of("R") + 1);

		opcode = DIV + (stoi(rX) << 4) + (stoi(rY) << 8);
	}
	if (comand == "PUSH") {
		xStart = line.find_first_of("R") + 1;
		rX = line.substr(xStart);
		opcode = PUSH + (stoi(rX) << 4);
	}
	if (comand == "POP") {
		xStart = line.find_first_of("R") + 1;
		rX = line.substr(xStart);
		opcode = POP + (stoi(rX) << 4);

	}
	if (comand == "JMP") {
		value = stoi(line.substr(line.find(delimiter)));
		opcode = JMP + (value << 4);

	}
	if (comand == "JIZ") {
		value = stoi(line.substr(line.find(delimiter)));
		opcode = JIZ + (value << 4);
	}
	if (comand == "JIH") {
		value = stoi(line.substr(line.find(delimiter)));
		opcode = JIH + (value << 4);
	}
	if (comand == "JSR") {
		value = stoi(line.substr(line.find(delimiter)));
		opcode = JSR + (value << 4);
	}
	if (comand == "RTS") {
		opcode = RTS;
	}

	cout << "RX: " << rX << " RY: " << rY << endl;
	cout << "opCode: " << bitset<16>(opcode).to_string() << endl;
	cout << "--------------------------" << endl;
	return opcode;
}


