#include "MockEngine.h"


MockEngine::MockEngine()
	: m_Q(nullptr), m_Worker(nullptr), m_Ptr(nullptr), m_IsMultiThreaded(false)
{
}

void MockEngine::Init(bool isMultithreaded)
{
	m_IsMultiThreaded = isMultithreaded;
	m_Ptr = new rando();
	if (m_IsMultiThreaded)
	{
		// if we're multi-threaded we need the parallel version of the work queue
		m_Q = new prl::WorkQ<MockEngine>();
		// and also we need the consumer thread
		m_Worker = new prl::ConsumerThread<MockEngine>(*this, *m_Q);
	}
	else
	{
		// single-threaded so we only need the single-threaded version of the queue that executes task on add.
		m_Q = new prl::WorkQ_ST<MockEngine>(*this);
	}
}


void MockEngine::AllWorkToConsumer()
{
	for (int i = 0; i < 50; i++)
	{
		// produce commands
		m_Q->add(std::mem_fn(&MockEngine::Cmd_Rando_init), std::make_shared<ExampleResource2>("Hello\n"));
		m_Q->add(std::mem_fn(&MockEngine::Cmd_Rando_sort), std::make_shared<ExampleResource1>(1));
		m_Q->add(std::mem_fn(&MockEngine::Cmd_Rando_print), std::make_shared<prl::CmdRsc>());
	}
}

void MockEngine::SharedWork()
{
	for (int i = 0; i < 25; i++)
	{
		// do some work and then produce commands
		// in this case share the fake work 50/50
		m_Ptr->init();
		m_Ptr->sort();
		m_Ptr->print();
		m_Q->add(std::mem_fn(&MockEngine::Cmd_Rando_init), std::make_shared<ExampleResource2>("Hello\n"));
		m_Q->add(std::mem_fn(&MockEngine::Cmd_Rando_sort), std::make_shared<ExampleResource1>(1));
		m_Q->add(std::mem_fn(&MockEngine::Cmd_Rando_print), std::make_shared<prl::CmdRsc>());
	}
}

void MockEngine::ShutDown()
{
	if (m_IsMultiThreaded)
	{
		m_Worker->End();
		m_Worker->Join();
		delete m_Worker;
	}
	delete m_Q;
	delete m_Ptr;
}

void MockEngine::Cmd_Rando_init(std::shared_ptr<prl::CmdRsc> rsc)
{
	auto* re = (ExampleResource2*)rsc.get();
	printf(re->msg.c_str());
	m_Ptr->_init();
}

void MockEngine::Cmd_Rando_sort(std::shared_ptr<prl::CmdRsc> rsc)
{
	auto* re = (ExampleResource1*)rsc.get();
	while(re->repeatTimes--)
		m_Ptr->_sort();
}

void MockEngine::Cmd_Rando_print(std::shared_ptr<prl::CmdRsc> rsc)
{
	m_Ptr->_print();
}