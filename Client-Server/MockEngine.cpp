#include "MockEngine.h"

namespace prl
{
	MockEngine::MockEngine()
		: m_Q(), m_Worker(*this, m_Q), m_Ptr(nullptr)
	{
	}

	void MockEngine::Init()
	{
		m_Ptr = new rando();
	}

	void MockEngine::DoFakeWork()
	{
		for (int i = 0; i < 50; i++)
		{
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
		m_Ptr->init();
	}

	void MockEngine::Cmd_Rando_sort()
	{
		m_Ptr->sort();
	}

	void MockEngine::Cmd_Rando_print()
	{
		m_Ptr->print();
	}
}