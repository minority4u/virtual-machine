#ifndef __PROFILER_H__
#define __PROFILER_H__
#include <string>

class Profiler
{
public:
	Profiler(std::string);
	~Profiler();
	void incrementExecutionCounter(int);
	void printProfiler();

private:
	const int programLength;
	int executionSum;
	int *executionForEachLine;
	std::string programPath;

};


#endif