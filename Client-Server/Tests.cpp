#include "Tests.h"
#include "Utils.h"
#include "MockEngine.h"

void tests::SampleTest()
{
	Utils::AutoTimeLog start("SampleTest");
	start.StopAndPrint();
}

void tests::ProducerConsumerThreaded_AllWorkToConsumer()
{
	Utils::AutoTimeLog start("ProducerConsumerThreaded_AllWorkToConsumer");
	MockEngine engine;
	engine.Init();
	engine.AllWorkToConsumer();
	engine.ShutDown();
	start.StopAndPrint();
}

void tests::ProducerConsumerThreaded_SharedWork()
{
	Utils::AutoTimeLog start("ProducerConsumerThreaded_SharedWork");
	MockEngine engine;
	engine.Init();
	engine.SharedWork();
	engine.ShutDown();
	start.StopAndPrint();
}


