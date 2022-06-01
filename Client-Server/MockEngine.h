#pragma once
#include "ConsumerThread.h"
#include <algorithm>
#include <array>

namespace prl
{
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

		void sort()
		{
			std::sort(numbers.begin(), numbers.end());
		}

		void print()
		{
			printf("First number %d, last number %d\n", numbers.front(), numbers.back());
		}
	private:
		std::array<int, 9999999> numbers;
	};

	class MockEngine
	{
	public:
		MockEngine();
		void Init();

		void DoFakeWork();
		void ShutDown();

	private:
		WorkQ<std::_Mem_fn<void (MockEngine::*)()>> m_Q; // How do I make this prettier?
		ConsumerThread<MockEngine> m_Worker;
		rando* m_Ptr;

		void Cmd_Rando_init();
		void Cmd_Rando_sort();
		void Cmd_Rando_print();
	};
}