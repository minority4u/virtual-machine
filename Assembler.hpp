#ifndef __ASSEMBLER_H__
#define __ASSEMBLER_H__

#include "Program.hpp"
#include <string>

using namespace std;

class Assembler{
    private:
        string fileURL;

        int countFileLines();
        unsigned short compileLineToOpcode(const string);
        int countCharInString(string, char);
    public:
        Assembler(string);
        virtual ~Assembler();
        Program* compile();
};

#endif
