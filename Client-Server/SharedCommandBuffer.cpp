#include "SharedCommandBuffer.h"

parallel::SharedCommandBuffer::SharedCommandBuffer(uint32_t ID, bool isThreaded)
	: m_ID(ID), m_CommandBuffer(), m_CmdIdx(0), m_IsThreaded(isThreaded)
{
}

std::function<void()> parallel::SharedCommandBuffer::GetCommand()
{
	auto cmd = m_CommandBuffer[m_CmdIdx++];
	return cmd;
}

// use clear because it no resize

// if single threaded - execute now
// else execute on worker thread
void parallel::SharedCommandBuffer::WriteCommand(std::function<void()> command)
{
	m_CommandBuffer.push(command);

	if (!m_IsThreaded)
		GetCommand()();
}
