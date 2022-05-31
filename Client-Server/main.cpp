#include<iostream>
#include <chrono>
#include <random>
#include "ConsumerThread.h"
#include "Utils.h"

// TODO: use unique pointers to ensure resource liftime
// finish test and profile
//

struct rando
{
	
	void init()
	{
		for (auto& nr : numbers)
		{
			nr = rand();
		}
	}
private:
	int numbers[9999999];
};

int main()
{
	const int iterations = 10000;
	{

	}
	return 0;
}
