#pragma once
#include "ConsumerThread.h"
#include "WorkQ_ST.h"
#include <algorithm>
#include <array>

struct rando
{
	rando()
	{
		printf("Struct constructed!\n");
	}
	~rando()
	{
		printf("Struct destructed %d bytes!\n", sizeof(numbers));
	}

	void init()
	{
		for (auto& nr : numbers)
		{
			nr = rand();
		}
	}

	void _init()
	{
		for (auto& nr : _numbers)
		{
			nr = rand();
		}
	}

	void sort()
	{
		std::sort(numbers.begin(), numbers.end());
	}

	void _sort()
	{
		std::sort(_numbers.begin(), _numbers.end());
	}

	void print()
	{
		printf("First number %d, last number %d\n", numbers.front(), numbers.back());
	}

	void _print()
	{
		printf("_First number %d, last number %d\n", _numbers.front(), _numbers.back());
	}
private:
	// fake data to work on
	std::array<int, 9999999> numbers;
	std::array<int, 9999999> _numbers;
};

// fake example engine
class MockEngine
{
public:
	MockEngine();
	void Init(bool isMultithreaded);

	void AllWorkToConsumer();
	void SharedWork();
	void ShutDown();

private:
	prl::WorkQ<MockEngine>* m_Q;
	prl::ConsumerThread<MockEngine>* m_Worker;
	rando* m_Ptr;

	bool m_IsMultiThreaded;

	// Mock commands
	void Cmd_Rando_init();
	void Cmd_Rando_sort();
	void Cmd_Rando_print();
};
