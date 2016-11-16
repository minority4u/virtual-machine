#ifndef __COMPILER_H__
#define __COMPILER_H__

#include "Program.hpp"
#include <string>

using namespace std;

class Compiler{
    private:
        string fileURL;

        int countFileLines();
        unsigned short compileLineToOpcode(const string);
        int countCharInString(string, char);
    public:
        Compiler(string);
        virtual ~Compiler();
        Program* compile();
};

#endif
