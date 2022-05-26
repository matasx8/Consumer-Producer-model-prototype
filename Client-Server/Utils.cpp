#include "Utils.h"


Utils::AutoTimeLog::AutoTimeLog(std::string name)
	: testname(name), start(std::chrono::high_resolution_clock::now())
{
}

void Utils::AutoTimeLog::StopAndPrint()
{
	const auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> ms_double = t2 - start;
	printf("Test '%s' : %.2f ms\n", testname.c_str(), ms_double.count());
}
