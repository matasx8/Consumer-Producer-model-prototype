#pragma once
#include <functional>
#include <vector>
#include <mutex>

namespace parallel
{
	// 1. use double buffering - no need to worry about racing
	// 2. use lambdas
	// 3. use polymorphism 
	// 4. work with variables that are accecible from worker thread only
	class SharedCommandBuffer
	{
	public:
		SharedCommandBuffer();
		SharedCommandBuffer(uint32_t ID, bool isThreaded);
		std::function<void()> GetCommand();

		void Lock();
		void Unlock();

		void Clear();
		inline size_t GetSize() { return m_CommandBuffer.size(); }
		inline uint32_t GetID() { return m_ID; }

		void WriteCommand(std::function<void()> command);
	private:
		uint32_t m_ID;
		std::mutex m_Mutex;
		std::vector<std::function<void()>> m_CommandBuffer;
		unsigned int m_CmdIdx;

		bool m_IsThreaded;
	};
}

