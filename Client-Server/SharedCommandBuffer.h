#pragma once
#include <functional>
#include <vector>

namespace parallel
{
	constexpr unsigned int kMaxCommandBuffers = 2;
	// 1. use double buffering - no need to worry about racing
	// 2. use lambdas
	// 3. use polymorphism 
	// 4. work with variables that are accecible from worker thread only
	class SharedCommandBuffer
	{
	public:
		SharedCommandBuffer(uint32_t ID, bool isThreaded);
		std::function<void()> GetCommand();

		// race condition because there's no sync
		//inline bool IsQueueEmpty() { return m_CommandQ.size() == 0; };
		inline uint32_t GetID() { return m_ID; }

		void WriteCommand(std::function<void()> command);
	private:
		uint32_t m_ID;
		std::vector<std::function<void()>> m_CommandBuffer;
		unsigned int m_CmdIdx;

		bool m_IsThreaded;
	};
}

