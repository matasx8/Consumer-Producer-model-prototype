#pragma once
#include <thread>
#include <functional>
#include "WorkQ.h"

namespace prl
{
	class ConsumerThread
	{
	public:
		ConsumerThread(WorkQ<std::function<void()>>& workQ);
		void End();
		void Join();

	private:
		void WorkLoop();

		std::thread m_Thread;
		WorkQ<std::function<void()>>& m_Q;
		bool m_Alive;
	};
}

