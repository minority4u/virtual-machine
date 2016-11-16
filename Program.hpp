#ifndef __PROGRAM_H__
#define __PROGRAM_H__

class Program{
    public:
        Program(unsigned short*, int);
        virtual ~Program();
        unsigned short* getOpcodes();
        int getNumberOfProgramLines();
    private:
        int numberOfProgramLines;
        unsigned short* opcodes;
};

#endif
