#include "SharedCommandBuffer.h"

parallel::SharedCommandBuffer::SharedCommandBuffer()
	: m_ID(0), m_Mutex(), m_CommandBuffer(), m_CmdIdx(0), m_IsThreaded(true)
{
}

parallel::SharedCommandBuffer::SharedCommandBuffer(uint32_t ID, bool isThreaded)
	: m_ID(ID), m_Mutex(), m_CommandBuffer(), m_CmdIdx(0), m_IsThreaded(isThreaded)
{
}

std::function<void()> parallel::SharedCommandBuffer::GetCommand()
{
	auto cmd = m_CommandBuffer[m_CmdIdx++];
	return cmd;
}

void parallel::SharedCommandBuffer::Lock()
{
	m_Mutex.lock();
}

void parallel::SharedCommandBuffer::Unlock()
{
	m_Mutex.unlock();
}

void parallel::SharedCommandBuffer::Clear()
{
	m_CommandBuffer.clear();
	m_CmdIdx = 0;
}

// if single threaded - execute now
// else execute on worker thread
void parallel::SharedCommandBuffer::WriteCommand(std::function<void()> command)
{
	m_CommandBuffer.push_back(command);

	if (!m_IsThreaded)
		GetCommand()();
}
