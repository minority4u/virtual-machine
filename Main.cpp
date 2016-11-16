#include "Compiler.hpp"
#include "VM.hpp"
#include <iostream>

using namespace std;

int main(int argc, char** arv){
	cout << "start VM" << endl;
	
    VM vm(Compiler("program.txt").compile());
    vm.run();

    cout << "end VN" << endl;

}
