#pragma once
#include "SharedCommandBuffer.h"
#include <array>

namespace parallel
{
	// should be like a 'monitor'
	// take care of providing command buffers
	// have option of supplying immediate command buffers
	// TODO: make non copyable
	class CommandBufferManager
	{
	public:
		CommandBufferManager();
		CommandBufferManager(uint32_t numBuffers);

		// for client
		SharedCommandBuffer& GetCommandBuffer();
		void Submit(uint32_t CommandBufferID);

		// for worker
		SharedCommandBuffer& AcquireCommandBuffer();
		void ReturnCommandBuffer(uint32_t CommandBufferID);

	private:
		std::array<SharedCommandBuffer, 2> m_CommandBuffers;
		uint32_t m_ActiveRecordingIdx;
		uint32_t m_ActiveExecutionIdx;
	};
}
