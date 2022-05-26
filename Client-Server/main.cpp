#include<iostream>
#include <chrono>
#include <random>
#include "CommandBufferWorker.h"
#include "CommandBufferManager.h"

struct SomeData
{
	int index;
	int numbers[9];
};

void WriteCommands(parallel::SharedCommandBuffer& cb, SomeData& data) 
{
	cb.WriteCommand([&]() {printf("Hey, here's some data: %d\n", data.index); });
	cb.WriteCommand([&]() {data.index = 0; printf("Hey, here's some data: %d\n", data.index); });
	for (int i = 0; i < 1000; i++)
	{
		cb.WriteCommand([&, i]() {for (int j = 0; j < 100000; j++) data.numbers[i % 9] * 123546; printf("Hey, here's some data: %d\n", data.index); });
	}
	//cb.WriteCommand([&]() {worker.End(); });
}

void Test() 
{
	parallel::CommandBufferManager man(2);
	// give ref to worker and launch();

	SomeData data;
	for (int i = 0; i < 100; i++)
	{
		auto& cb = man.GetCommandBuffer();
		WriteCommands(cb, data);
		man.Submit(cb.GetID());
	}

}

int main()
{
	const int iterations = 10000;
	{
		Test();
		SomeData data;
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
	}
	return 0;
}
