#include<iostream>
#include <chrono>
#include <random>
#include "ConsumerThread.h"
#include "MockEngine.h"
#include "Utils.h"
#include <memory>
#include <array>
#include "Tests.h"


int main()
{
	tests::ProducerConsumerThreaded_AllWorkToConsumer();
	tests::ProducerConsumerThreaded_SharedWork();
	tests::ProducerConsumerNonThreaded_SharedWork();
	return 0;
}

