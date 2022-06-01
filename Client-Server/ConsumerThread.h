#pragma once
#include <thread>
#include <functional>
#include "WorkQ.h"

namespace prl
{
	template <typename T> class ConsumerThread
	{
	public:
		inline ConsumerThread(T& functionOwner, WorkQ<std::_Mem_fn<void (T::*)()>>& workQ) 
			: m_FunctionOwner(functionOwner), m_Thread(&ConsumerThread::WorkLoop, this), m_Q(workQ), m_Alive(true)
		{}

		inline void End()
		{
			m_Alive = false;
		}

		void Join()
		{
			m_Thread.join();
		}

	private:
		inline void WorkLoop()
		{
			while (m_Alive || m_Q.size())
			{
				auto func = m_Q.remove();
				func(m_FunctionOwner);
			}
		}

		std::thread m_Thread;
		WorkQ<std::_Mem_fn<void (T::*)()>>& m_Q;
		T& m_FunctionOwner;
		bool m_Alive;
	};
}

