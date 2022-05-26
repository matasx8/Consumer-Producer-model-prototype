#pragma once
#include <thread>
#include <vector>

namespace parallel
{
	// 1. need to be able to provide work
	// 2. need to be able to wait until not busy anymore
	// 3. need to use double-buffering
	class CommandBufferManager;

	class CommandBufferWorker
	{
	public:
		CommandBufferWorker(CommandBufferManager& cmbRef, bool IsThreaded);
		void Start();
		void End();
		void Join();

	private:
		void WorkLoop();

		std::thread m_WorkerThread;
		CommandBufferManager& m_CbmRef;
		bool m_Alive;
		bool m_IsThreaded;
	};
}

