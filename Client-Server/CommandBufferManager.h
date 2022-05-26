#pragma once
#include "SharedCommandBuffer.h"

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

		SharedCommandBuffer& GetCommandBuffer();

		void Submit(uint32_t CommandBufferID);
	private:
		std::vector<SharedCommandBuffer> m_CommandBuffers;
		uint32_t m_ActiveRecordingIdx;
	};
}
