#include "Profiler.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Profiler::Profiler(string programPath) : programPath(programPath), programLength(2048), executionSum(0){
	executionForEachLine = new int[programLength];
	for(int i = 0; i < programLength; i++){
		executionForEachLine[i] = 0;
	}
}

void Profiler::incrementExecutionCounter(int i){
	executionForEachLine[i]++;
	executionSum++;
}

void Profiler::printProfiler(){
	fstream file(programPath, ios::in);
	ofstream outFile;
	outFile.open("Profiler.txt");
    string line = "";
    
    for(int i = 0; getline(file, line, '\n'); i++){
    	outFile << "(" << (100/executionSum* executionForEachLine[i]) << " \% " << executionForEachLine[i] << "x) " << line << endl;
    }
    outFile.close();

    file.close();
}