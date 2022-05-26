#pragma once
#include <thread>
#include <vector>

namespace parallel
{
	// 1. need to be able to provide work
	// 2. need to be able to wait until not busy anymore
	// 3. need to use double-buffering
	class SharedCommandBuffer;

	class CommandBufferWorker
	{
	public:
		CommandBufferWorker(SharedCommandBuffer& cmbRef, bool IsThreaded);
		void Start();
		void End();
		void Join();

	private:
		void WorkLoop();

		std::thread m_WorkerThread;
		SharedCommandBuffer& m_ScbRef;
		bool m_Alive;
		bool m_IsThreaded;
	};
}

