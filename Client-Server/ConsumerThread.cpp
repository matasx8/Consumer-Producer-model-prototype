#include "ConsumerThread.h"

namespace prl
{
	ConsumerThread::ConsumerThread(WorkQ<std::function<void()>>& workQ)
		: m_Thread(&ConsumerThread::WorkLoop, this), m_Q(workQ), m_Alive(true)
	{
	}

	void ConsumerThread::End()
	{
		m_Alive = false;
	}

	void ConsumerThread::Join()
	{
		m_Thread.join();
	}

	void ConsumerThread::WorkLoop()
	{
		while (m_Alive)
		{
			auto func = m_Q.remove();
			func();
		}
	}
}
