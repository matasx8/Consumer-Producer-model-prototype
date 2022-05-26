#include "CommandBufferWorker.h"
#include "SharedCommandBuffer.h"

parallel::CommandBufferWorker::CommandBufferWorker(SharedCommandBuffer& cmbRef, bool isThreaded)
	: m_WorkerThread(), m_ScbRef(cmbRef), m_Alive(true), m_IsThreaded(isThreaded)
{
}

void parallel::CommandBufferWorker::Start()
{
	if(m_IsThreaded)
		m_WorkerThread = std::move(std::thread(&CommandBufferWorker::WorkLoop, this));
}

void parallel::CommandBufferWorker::End()
{
	m_Alive = false;
}

void parallel::CommandBufferWorker::Join()
{
	if(m_IsThreaded)
		m_WorkerThread.join();
}

void parallel::CommandBufferWorker::WorkLoop()
{
	while (m_Alive)
	{
		if (!m_ScbRef.IsQueueEmpty())
		{
			m_ScbRef.GetCommand()();
		}
	}
}
