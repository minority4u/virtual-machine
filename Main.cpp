#include "Assembler.hpp"
#include "VM.hpp"
#include <iostream>

using namespace std;

int main(int argc, char** arv){
	cout << "start VM" << endl;
	
    VM vm(Assembler("fib").compile());
    vm.run();

    cout << "end VM" << endl;

}
