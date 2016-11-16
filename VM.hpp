#ifndef VM_H_
#define VM_H_
#include "Program.hpp"
#include "Profiler.hpp"

class VM
{
public:
	VM(Program*);
	// load programcode
	void run();
	virtual ~VM();

private:
	int programSegmentEnd;
	int programEnd;
	int progCounter;
	int stackPointer;
	int subroutineStackPointer;
	int vmMemorySize;
	int vmRegisterSize;
	int vmStackSize;
	int vmSubroutineStackSize;

	unsigned short *vmMemory;
	unsigned short *vmRegister;
	unsigned short *vmStack;
	int *vmSubroutineStack;
	Profiler *vmProfiler;

	unsigned short readNextFromMemory();


};
#endif