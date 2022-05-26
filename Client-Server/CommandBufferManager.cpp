#include "CommandBufferManager.h"
#include "SharedCommandBuffer.h"

namespace parallel
{
	CommandBufferManager::CommandBufferManager()
		:m_CommandBuffers(), m_ActiveRecordingIdx(0), m_ActiveExecutionIdx(0)
	{

	}

	CommandBufferManager::CommandBufferManager(uint32_t numBuffers)
		:m_CommandBuffers(), m_ActiveRecordingIdx(0), m_ActiveExecutionIdx(0)
	{

	}

	SharedCommandBuffer& CommandBufferManager::GetCommandBuffer()
	{
		auto& cb = m_CommandBuffers[m_ActiveRecordingIdx];
		cb.Lock();
		return cb;
	}

	void CommandBufferManager::Submit(uint32_t CommandBufferID)
	{
		m_CommandBuffers[m_ActiveRecordingIdx++].Unlock();
		m_ActiveRecordingIdx %= m_CommandBuffers.size();
	}

	SharedCommandBuffer& CommandBufferManager::AcquireCommandBuffer()
	{
		auto& cb = m_CommandBuffers[m_ActiveExecutionIdx];
		cb.Lock();
		return cb;
	}

	void CommandBufferManager::ReturnCommandBuffer(uint32_t CommandBufferID)
	{
		m_CommandBuffers[m_ActiveExecutionIdx].Clear();
		m_CommandBuffers[m_ActiveExecutionIdx++].Unlock();
		m_ActiveExecutionIdx %= m_CommandBuffers.size();
	}
}
