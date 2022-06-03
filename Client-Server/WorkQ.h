#pragma once
#include <functional>
#include <vector>
#include <list>
#include <mutex>

namespace prl
{
	template <typename T> class WorkQ
	{
	public:
		inline WorkQ() :m_Mutex(), m_CV(), m_Q()
		{
		}

		virtual inline void add(std::_Mem_fn<void (T::*)()> item) {
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_Q.push_back(item);
			m_CV.notify_one();
		}

		virtual inline std::_Mem_fn<void (T::*)()> remove() {
			std::unique_lock<std::mutex> lock(m_Mutex);
			if (m_Q.size() == 0)
				m_CV.wait(lock);

			std::_Mem_fn<void (T::*)()> item = m_Q.front();
			m_Q.pop_front();
			return item;
		}

		virtual inline size_t size() {
			std::unique_lock<std::mutex> lock(m_Mutex);
			return m_Q.size();
		}
	protected:
		std::mutex m_Mutex;
		std::condition_variable m_CV;
		std::list<std::_Mem_fn<void (T::*)()>> m_Q;
	};
}

