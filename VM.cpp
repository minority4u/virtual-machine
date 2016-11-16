#include <iostream>
#include <string>
#include <algorithm>
#include "VM.hpp"

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

VM::VM(Program* compiledProgram)
	: programSegmentEnd(2048), programEnd(0), progCounter(0), stackPointer(0), subroutineStackPointer(0),
	  vmMemorySize(4096), vmRegisterSize(16), vmStackSize(128), vmSubroutineStackSize(128)
{
	vmMemory = new unsigned short[vmMemorySize];
	programEnd = compiledProgram->getNumberOfProgramLines();
	vmRegister = new unsigned short[vmRegisterSize];
	vmStack = new unsigned short[vmStackSize];
	vmSubroutineStack = new int[vmSubroutineStackSize];
	vmProfiler = new Profiler(compiledProgram->getProgramPath());

	// copy opCode from compiled program into vmMemory
		for (int i = 0; i < programEnd; ++i){
		vmMemory[i]= compiledProgram->getOpcodes()[i];
	}
}

unsigned short VM::readNextFromMemory() {
	return vmMemory[progCounter];
}

void VM::run() {
	//progCounter = 0;
	unsigned short opCode, cmd, fromMem, toMem, idX, idY;

	while (progCounter < programEnd && progCounter >= 0) {

		// reads opCode from memory at programCounter position
		opCode = readNextFromMemory();

		vmProfiler->incrementExecutionCounter(progCounter);

		// extract comand from opcode
		cmd = opCode & 15;
		// extract idX and idY from opcode
		idX = ((opCode >> 4) & 15);
		idY = ((opCode >> 8) & 15);

		switch (cmd) {
		case NOP:
			cout << "NOP" << endl;
			progCounter++;
			break;

		case LOAD:
			cout << "Load value: " << (opCode >> 4) << " to Register[0]" << endl;
			vmRegister[0] = (opCode >> 4);
			progCounter++;
			break;

		case MOV:
			// extract toMem and fromMem bits from opcode
			toMem = ((opCode >> 13) & 1);
			fromMem = ((opCode >> 12) & 1);

			// move a value from register to register
			if (toMem == 0 && fromMem == 0) {
				vmRegister[idX] = vmRegister[idY];
				cout << "Move value: " << vmRegister[idY] << " from Register[" << idY
				     << "] to Register[" << idX << "]" << endl;
				// move a value from register to mem
			} else if (toMem == 1 && fromMem == 0) {
				vmMemory[vmRegister[idX] & 4095] = vmRegister[idY];
				cout << "Move value: " <<  vmRegister[idY]
				     << " from Register[" << idY
				     << "] to Memory[" << (vmRegister[idX] & 4095) << "]" << endl;
				// move a value from mem to register
			} else if (toMem == 0 && fromMem == 1) {
				vmRegister[idX] = vmMemory[vmRegister[idY]];
				cout << "Move value: " << vmMemory[vmRegister[idY]]
				     << " from Memory[" << vmRegister[idY]
				     << "] to Register[" << idX << "]" << endl;
				// from memory to memory
			} else if (toMem == 1 && fromMem == 1) {
				vmMemory[vmRegister[idX] & 4095] = vmMemory[vmRegister[idY]];
				cout << "Move value: " << vmMemory[vmRegister[idY]]
				     << " from Memory[" << vmRegister[idY]
				     << "] to Memory[" << (vmRegister[idX] & 4095) << "]" << endl;
			}
			progCounter++;
			break;
		case ADD:
			cout << "Add value: " << vmRegister[idY] << " from Register[" << idY
			     << "] to value: " << vmRegister[idX] << " from Register[" << idX << "]" << endl;
			vmRegister[idX] = vmRegister[idX] + vmRegister[idY];
			progCounter++;
			break;
		case SUB:
			cout << "Substract value: " << vmRegister[idY] << " from Register[" << idY
			     << "] from value: " << vmRegister[idX] << " of Register[" << idX << "]" << endl;
			vmRegister[idX] = vmRegister[idX] - vmRegister[idY];
			progCounter++;
			break;
		case MUL:
			cout << "Multiply value: " << vmRegister[idY] << " from Register[" << idY
			     << "] by value: " << vmRegister[idX] << " from Register[" << idX << "]" << endl;
			vmRegister[idX] = vmRegister[idX] * vmRegister[idY];
			progCounter++;
			break;
		case DIV:
			cout << "Divide value: " << vmRegister[idY] << " from Register[" << idY
			     << "] by value: " << vmRegister[idX] << " from Register[" << idX << "]" << endl;
			vmRegister[idX] = vmRegister[idX] / vmRegister[idY];
			progCounter++;
			break;
		case PUSH:
			cout << "Push value: " << vmRegister[idX] << " from Register [" << idX <<
			     "] to stack at position [" << stackPointer << "]" << endl;
			vmStack[stackPointer] = vmRegister[idX];
			stackPointer++;
			progCounter++;
			break;
		case POP:
			stackPointer--;
			cout << "Pop value: " << vmStack[stackPointer] << " from stack at position [" << stackPointer <<
			     "] to Register [" << idX << "]" << endl;
			vmRegister[idX] = vmStack[stackPointer];
			progCounter++;
			break;
		case JMP:
			cout << "Jump to program position: " << (opCode >> 4) << endl;
			progCounter = (opCode >> 4);
			break;
		case JIZ:
			if (vmRegister[0] == 0) {
				cout << "vmRegister[0] = " << vmRegister[0] << " Jump to program position: " << (opCode >> 4) << endl;
				progCounter = (opCode >> 4);
			} else {
				progCounter++;
			}
			break;
		case JIH:
			if (vmRegister[0] > 0) {
				cout << "vmRegister[0] = " << vmRegister[0] << " Jump to program position: " << (opCode >> 4) << endl;
				progCounter = (opCode >> 4);
			} else {
				progCounter++;
			}
			break;
		case JSR:
			vmSubroutineStack[subroutineStackPointer] = progCounter;
			progCounter = (opCode >> 4);
			subroutineStackPointer++;
			cout << "Jump to subroutine on position: " << progCounter << endl;
			break;
		case RTS:
			subroutineStackPointer--;
			progCounter = vmSubroutineStack[subroutineStackPointer];
			progCounter++;
			cout << "Return from subroutine to position: " << progCounter << endl;
			break;
		default:
			cout << "Can not interpretate cmd" << endl;
		}
	}
	vmProfiler->printProfiler();
}
VM::~VM()
{
	delete[] vmMemory;
	delete[] vmRegister;
	delete[] vmStack;
	delete[] vmSubroutineStack;
	//cout << "Destruktor von VM aufgerufen." << endl;
}

