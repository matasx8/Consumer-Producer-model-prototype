#include<iostream>
#include <chrono>
#include <random>
#include "CommandBufferWorker.h"
#include "CommandBufferManager.h"
#include "Utils.h"

static int fib(int n)
{
	if (n <= 1)
		return n;
	return fib(n - 1) + fib(n - 2);
}

void WriteCommands(parallel::SharedCommandBuffer& cb) 
{
	for (int i = 0; i < 1000; i++)
	{
		cb.WriteCommand([]() {for (int j = 0; j < 10; j++) printf("Hey, here's some data: %d\n", fib(43)); });
	}
}

void Test() 
{
	parallel::CommandBufferManager man(2);
	parallel::CommandBufferWorker worker(man, true);
	Utils::AutoTimeLog start("Parallel test");
	worker.Start();

	for (int i = 0; i < 10; i++)
	{
		auto& cb = man.GetCommandBuffer();
		
		fib(43);
		WriteCommands(cb);// wont work yet, thread can starve if one thread keeps taking

		man.Submit(cb.GetID());
	}

	worker.End();
	worker.Join();
	start.StopAndPrint();
}

int main()
{
	const int iterations = 10000;
	{
		Test();
		/*SomeData data;
		auto start = std::chrono::steady_clock::now();

		parallel::SharedCommandBuffer cmb(true);
		parallel::CommandBufferWorker worker(cmb, true);
		worker.Start();

		cmb.WriteCommand([&]() {printf("Hey, here's some data: %d\n", data.index); });
		cmb.WriteCommand([&]() {data.index = 0; printf("Hey, here's some data: %d\n", data.index); });
		for (int i = 0; i < iterations; i++)
		{
			cmb.WriteCommand([&, i]() {for (int j = 0; j < 100000; j++) data.numbers[i % 9] * 123546; printf("Hey, here's some data: %d\n", data.index); });
		}
		cmb.WriteCommand([&]() {worker.End(); });

		worker.Join();
		auto end = std::chrono::steady_clock::now();

		std::cout	<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
			<< " ms" << std::endl;
	}*/
	}
	return 0;
}
