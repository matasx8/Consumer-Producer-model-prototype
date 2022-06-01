#include<iostream>
#include <chrono>
#include <random>
#include "ConsumerThread.h"
#include "MockEngine.h"
#include "Utils.h"
#include <memory>
#include <array>


int main()
{
	prl::MockEngine engine;
	engine.Init();
	engine.DoFakeWork();
	engine.ShutDown();
	return 0;
}

