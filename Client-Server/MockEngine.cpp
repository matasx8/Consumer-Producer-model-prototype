#include "MockEngine.h"


MockEngine::MockEngine()
	: m_Q(), m_Worker(*this, m_Q), m_Ptr(nullptr)
{
	//prl::ConsumerThread<MockEngine> th()
}

void MockEngine::Init(bool isMultithreaded)
{
	m_Ptr = new rando();
	if (isMultithreaded)
	{
		// finish here
	}
	else
	{

	}
}

void MockEngine::AllWorkToConsumer()
{
	for (int i = 0; i < 50; i++)
	{
		m_Q.add(std::mem_fn(&MockEngine::Cmd_Rando_init));
		m_Q.add(std::mem_fn(&MockEngine::Cmd_Rando_sort));
		m_Q.add(std::mem_fn(&MockEngine::Cmd_Rando_print));
	}
}

void MockEngine::SharedWork()
{
	for (int i = 0; i < 25; i++)
	{
		m_Ptr->init();
		m_Ptr->sort();
		m_Ptr->print();
		m_Q.add(std::mem_fn(&MockEngine::Cmd_Rando_init));
		m_Q.add(std::mem_fn(&MockEngine::Cmd_Rando_sort));
		m_Q.add(std::mem_fn(&MockEngine::Cmd_Rando_print));
	}
}

void MockEngine::ShutDown()
{
	m_Worker.End();
	m_Worker.Join();
	delete m_Ptr;
}

void MockEngine::Cmd_Rando_init()
{
	m_Ptr->_init();
}

void MockEngine::Cmd_Rando_sort()
{
	m_Ptr->_sort();
}

void MockEngine::Cmd_Rando_print()
{
	m_Ptr->_print();
}