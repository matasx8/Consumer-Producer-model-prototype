#include "CommandBufferWorker.h"
#include "CommandBufferManager.h"

namespace parallel
{
	CommandBufferWorker::CommandBufferWorker(CommandBufferManager& cmbRef, bool isThreaded)
		: m_WorkerThread(), m_CbmRef(cmbRef), m_Alive(true), m_IsThreaded(isThreaded)
	{
	}

	void CommandBufferWorker::Start()
	{
		if (m_IsThreaded)
			m_WorkerThread = std::move(std::thread(&CommandBufferWorker::WorkLoop, this));
	}

	void CommandBufferWorker::End()
	{
		m_Alive = false;
	}

	void CommandBufferWorker::Join()
	{
		if (m_IsThreaded)
			m_WorkerThread.join();
	}

	void CommandBufferWorker::WorkLoop()
	{
		while (m_Alive)
		{
			auto& cb = m_CbmRef.AcquireCommandBuffer();
			for (int i = 0; i < cb.GetSize(); i++)
			{
				auto cmd = cb.GetCommand();
				cmd();
			}
			m_CbmRef.ReturnCommandBuffer(cb.GetID());
		}
	}
}
