#ifndef __PROGRAM_H__
#define __PROGRAM_H__
#include <string>

class Program{
    public:
        Program(std::string, unsigned short*, int);
        virtual ~Program();
        unsigned short* getOpcodes();
        int getNumberOfProgramLines();
        std::string getProgramPath();
    private:
        int numberOfProgramLines;
        unsigned short* opcodes;
        std::string programPath;
};

#endif
